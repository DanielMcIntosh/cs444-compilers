#include <memory>
#include <array>
#include <unordered_set>
#include <unordered_map>
#include <string>

#include "parser.h"
#include "parseTreeBase.h"
#include "parseTree.h"

#include "../grammar.h"
#include "../astToken.h"
#include "../profiler.h"

namespace Parse {

const char *newLines = "\r\n";
const char *Spaces = " ";

bool can_parse(const vector<string>& input, const vector<Rule>& rules, const DFA& joos_dfa) {
  vector<int> state_stack;
  vector<string> token_stack;
  state_stack.push_back(0);
  for (auto token : input) {
    while (true) {
      if (joos_dfa.at(state_stack.back()).count(token) == 0) {
        // invalid token at this state
        return false;
      }
      Transition next_rule = joos_dfa.at(state_stack.back()).at(token);
      auto [action, rule_id] = next_rule;
      if (action == SHIFT) {
        auto next_state = rule_id;
        token_stack.push_back(token);
        state_stack.push_back(next_state);
        break;
      }

      for (int i = 0; i < rules[rule_id].rhsSize; ++i) {
        token_stack.pop_back();
        state_stack.pop_back();
      }
      token_stack.push_back(rules[rule_id].lhs);

      if (joos_dfa.at(state_stack.back()).count(token_stack.back()) == 0) {
        return false;
      }

      auto r = joos_dfa.at(state_stack.back()).at(token_stack.back());
      if (r.first == SHIFT) {
        state_stack.push_back(r.second);
      } else {
        assert(false); // this can never happen
      }
    }
  }
  return true;
}

void lineHelper(char *buffer, const char **textPtr) {
  profileSection("line helper");
  int len = strcspn(*textPtr, newLines);
  snprintf(buffer, len + 1, "%s", *textPtr);
  *textPtr += len;
  *textPtr += strspn(*textPtr, newLines);
}

void lineHelperFast(char **textPtr, char **state) {
  profileSection("line helper fast");

  *textPtr = *state;

  char *n = *state;
  while (*n != '\n')
    ++n;

  *n = 0;
  *state = n + 1;
}

void parserReadLR1(Parser *parser, const char *text) {
  char *textPtr = const_cast<char *>(text);
  char *state = textPtr;

  lineHelperFast(&textPtr, &state);
  
  int numTerminal = atoi(textPtr);
  for (int i = 0; i < numTerminal; ++i) {
    lineHelperFast(&textPtr, &state);
  }

  lineHelperFast(&textPtr, &state);

  int numNonTerminal = atoi(textPtr);
  for (int i = 0; i < numNonTerminal; ++i) {
    lineHelperFast(&textPtr, &state);
  }
  lineHelperFast(&textPtr, &state);
  string startingSymbol(textPtr);
  lineHelperFast(&textPtr, &state);
  {
    profileSection("load rules");
    int numRules = atoi(textPtr);
    for (int i = 0; i < numRules; ++i) {
      lineHelperFast(&textPtr, &state);
      char *token = strtok(textPtr, Spaces);
      string lhs(token);
      int rhsSize = 0;
      while ((token = strtok(nullptr, Spaces))) {
        ++rhsSize;
      }
      parser->rules.push_back({lhs, rhsSize});
    }
    lineHelperFast(&textPtr, &state);    
  }

  int numDFAStates = atoi(textPtr);
  (void)numDFAStates;

  {
    profileSection("load transitions");
    lineHelperFast(&textPtr, &state);
    int numTransitions = atoi(textPtr);
    for (int i = 0; i < numTransitions; ++i) {
      lineHelperFast(&textPtr, &state);
      int stateNum = atoi(strtok(textPtr, Spaces));
      string symbol(strtok(nullptr, Spaces));
      string action(strtok(nullptr, Spaces));
      int stateOrRuleNumber = atoi(strtok(nullptr, Spaces));
      parser->joos_dfa[stateNum][symbol] = {action == "shift" ? SHIFT : REDUCE, stateOrRuleNumber};
    }
  }
}

void parserReadJoosLR1(Parser *parser) {
  s32 fileSize;
  unique_ptr<char[]> text = readEntireFile("joos.lr1", &fileSize);
  if (!text)
    return;

  parserReadLR1(parser, text.get());
}

const string &lexTokenTranslate(const Scan::LexToken &lexToken) {
  static const unordered_set<string> gNameSet = {
          "IntegerLiteral",
          "BooleanLiteral",
          "CharacterLiteral",
          "StringLiteral",
          "NullLiteral",
          "Identifier",
          "BOF",
          "EOF"
  };
  static const unordered_set<string> gLexemeSet = {
          "Keyword",
          "Separator",
          "Operator",
  };
  static const string gError = "ERROR";
  if (gNameSet.count(lexToken.name))
    return lexToken.name;
  if (gLexemeSet.count(lexToken.name))
    return lexToken.lexeme;
  ASSERT(false);
  return gError;
}

bool treeStackShiftTerminal(vector<Tree *> *stack, const Scan::LexToken &token) {
  if (token.name == "Identifier") {
    auto t = new TIdentifier;
    t->value = token.lexeme;
    stack->push_back(t);
    return true;
  }

  if (token.name == "IntegerLiteral") {
    auto t = new TIntegerLiteral;
    try {
      t->value = stoul(token.lexeme);
    } catch (std::out_of_range &error) {
      // push anyway or we will leak t
      stack->push_back(t);
      return false;
    }
    stack->push_back(t);
    // reject values larger than 1<<31, to check if 1<<31 is actually a negated literal in weeder
    return t->value <= (1u<<31);
  }

  if (token.name == "BooleanLiteral") {
    auto t = new TBooleanLiteral;
    /* TODO */
    stack->push_back(t);
    return true;
  }

  if (token.name == "StringLiteral") {
    auto t = new TStringLiteral;
    t->value = token.lexeme;
    stack->push_back(t);
    return true;
  }

  if (token.name == "NullLiteral") {
    auto t = new TNullLiteral;
    t->value = false;
    stack->push_back(t);
    return true;
  }

  if (token.name == "CharacterLiteral") {
    auto t = new TCharacterLiteral;
    t->value = token.lexeme[0];
    stack->push_back(t);
    return true;
  }
  return true;
}

ParseResult parserParse(Parser *parser, const vector<Scan::LexToken> &tokens) {
  vector<int> state_stack;
  vector<string> token_stack;
  vector<Tree *> tree_stack;

  ParseResult result;
  result.treeRoot = nullptr;
  result.errorLexTokenIndex = -1;
  result.valid = false;

  state_stack.push_back(0);
  s32 tokenIndex = 0;
  for (const auto &token : tokens) {
    const string &canonicalTokenName = lexTokenTranslate(token);

    while (true) {
      if (parser->joos_dfa.at(state_stack.back()).count(canonicalTokenName) == 0) {
        // invalid token at this state
        ptDeleteStack(&tree_stack);
        result.errorLexTokenIndex = tokenIndex;
        return result;
      }
      Transition next_rule = parser->joos_dfa.at(state_stack.back()).at(canonicalTokenName);
      auto [action, rule_id] = next_rule;
      if (action == SHIFT) {
        auto next_state = rule_id;
        token_stack.push_back(canonicalTokenName);
        state_stack.push_back(next_state);
        if (!treeStackShiftTerminal(&tree_stack, token)) {
          ptDeleteStack(&tree_stack);
          result.errorLexTokenIndex = tokenIndex;
          return result;
        }
        break;
      }

      ptDispatcher(&tree_stack, rule_id);
      for (int i = 0; i < parser->rules[rule_id].rhsSize; ++i) {
        token_stack.pop_back();
        state_stack.pop_back();
      }
      token_stack.push_back(parser->rules[rule_id].lhs);

      if (parser->joos_dfa.at(state_stack.back()).count(token_stack.back()) == 0) {
        ptDeleteStack(&tree_stack);
        result.errorLexTokenIndex = tokenIndex;
        return result;
      }

      auto r = parser->joos_dfa.at(state_stack.back()).at(token_stack.back());
      if (r.first == SHIFT) {
        state_stack.push_back(r.second);
      } else {
        ASSERT(false); // this can never happen
      }
    }

    ++tokenIndex;
  }

  result.treeRoot = tree_stack.front();
  result.errorLexTokenIndex = -1;
  result.valid = true;
  return result;
}

void parserDumpDebugInfo(const ParseResult& result, const char *baseOutputPath) {
  strdecl512(filePath, "%s.parser.txt", baseOutputPath);
  FILE *dump = fopen(filePath, "w");
  fprintf(dump, "error at index %d\n", result.errorLexTokenIndex);
  fclose(dump);
}

void parserTest() {
  Parser parser;
  s32 fileSize;
  unique_ptr<char[]> fileContents = readEntireFile("experimental/sample.lr1", &fileSize);
  if (!fileContents)
    return;

  parserReadLR1(&parser, fileContents.get());

  vector<pair<bool,vector<string>>> tests = {
          {true, {"BOF", "id", "-", "(", "id", "-", "id", ")", "EOF"}},
          {true, {"BOF", "id", "EOF"}},
          {true, {"BOF", "(", "id", "-", "id", ")", "-", "(", "id", "-", "id", ")", "EOF"}},
          {true, {"BOF", "(", "id", "-", "id", ")", "-", "id", "EOF"}},
          {true, {"BOF", "id", "-", "id", "EOF"}},
          {true, {"BOF", "(", "(", "id", "-", "id", ")", "-", "id", ")", "-", "id", "EOF"}},
          {true, {"BOF", "(", "id", "-", "(", "id", "-", "(", "id", "-", "(", "id", "-", "(", "id", "-", "id", ")", ")", ")", ")", ")", "EOF"}},
          {true, {"BOF", "(", "(", "(", "(", "(", "(", "id", "-", "id", ")", "-", "id", ")", "-", "id", ")", "-", "(", "id", "-", "(", "id", "-", "(", "id", "-", "(", "id", "-", "(", "id", "-", "id", ")", ")", ")", ")", ")", ")", ")", ")", "EOF"}},
          {false, {"BOF", "id"}}, // BUG: accepts valid prefix if EOF marker is missing
          {false, {"BOF", "(", "EOF"}},
          {false, {"BOF", "(", ")", "EOF"}},
          {false, {"BOF", "id", "id", "EOF"}},
  };

  for (auto [expected, input] : tests) {
    auto result = can_parse(input, parser.rules, parser.joos_dfa);
    printf("expect: %d got: %d %s\n", expected, result, expected == result ? "" : "failed");
  }
}

} // namespace Parse

namespace Parser
{

void parseTokens(std::vector<Scan::LexToken> const &inputTokens, Grammar const& grammar)
{
	std::vector<State> stateStack;
	std::vector<ASTToken> tokenStack;
	stateStack.emplace_back(0);

	for (const auto& nextToken : inputTokens)
	{
		Symbol nextSymbol = grammar.cfg.symbolMap.at(nextToken.name);
		tokenStack.push_back(ASTToken(nextSymbol, nextToken.lexeme));
		// have to use a pointer instead of a reference because we would need to re-bind the reference in the for loop increment
		const std::unique_ptr<Action> *action = &(grammar.actions[stateStack.back()][tokenStack.back().sym]);
		for (; (*action) && (*action)->isReduction;
			action = &(grammar.actions[stateStack.back()][tokenStack.back().sym]))
		{
			CFG::Rule reduction = grammar.cfg.rules[(*action)->ruleNum];

			// generate the list of child tokens for constructing the next ASTToken
			std::vector<ASTToken> children;
			for (auto it = tokenStack.end() - reduction.rhs.size(); it != tokenStack.end(); it++)
			{
				children.push_back(std::move(*it));
			}

			// pop all the children from the token stack and
			// change our state back to what it was before we inserted any of the children
			for (size_t i = 0; i < reduction.rhs.size(); ++i)
			{
				tokenStack.pop_back();
				stateStack.pop_back();
			}

			tokenStack.emplace_back(reduction.lhs, children);
		}

		if ((*action))
		{
			stateStack.push_back((*action)->outState);
		}
	}
}

} //namespace Parser
