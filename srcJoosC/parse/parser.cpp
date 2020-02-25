#include "parser.h"

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../profiler.h"
#include "parseTree.h"
#include "parseTreeBase.h"

namespace Parse {

const char* newLines = "\r\n";
const char* Spaces = " ";

static bool can_parse(const vector<string>& input,
               const vector<Rule>& rules,
               const DFA& joos_dfa) {
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
        assert(false);  // this can never happen
      }
    }
  }
  return true;
}

static void lineHelper(char* buffer, const char** textPtr) {
  profileSection("line helper");
  int len = strcspn(*textPtr, newLines);
  snprintf(buffer, len + 1, "%s", *textPtr);
  *textPtr += len;
  *textPtr += strspn(*textPtr, newLines);
}

static void lineHelperFast(char** textPtr, char** state) {
  profileSection("line helper fast");

  *textPtr = *state;

  char* n = *state;
  while (*n != '\n')
    ++n;

  *n = 0;
  *state = n + 1;
}

void parserReadLR1(Parser* parser, const char* text) {
  char* textPtr = const_cast<char*>(text);
  char* state = textPtr;

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
    char *tokState;
    for (int i = 0; i < numRules; ++i) {
      lineHelperFast(&textPtr, &state);
      char* token = strtok_r(textPtr, Spaces, &tokState);
      string lhs(token);
      int rhsSize = 0;
      while ((token = strtok_r(nullptr, Spaces, &tokState))) {
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
    char *tokState;
    for (int i = 0; i < numTransitions; ++i) {
      lineHelperFast(&textPtr, &state);
      int stateNum = atoi(strtok_r(textPtr, Spaces, &tokState));
      string symbol(strtok_r(nullptr, Spaces, &tokState));
      string action(strtok_r(nullptr, Spaces, &tokState));
      int stateOrRuleNumber = atoi(strtok_r(nullptr, Spaces, &tokState));
      parser->joos_dfa[stateNum][symbol] = {action == "shift" ? SHIFT : REDUCE,
                                            stateOrRuleNumber};
    }
  }
}

void parserReadJoosLR1(Parser* parser) {
  s32 fileSize;
  unique_ptr<char[]> text = readEntireFile("joos.lr1", &fileSize);
  if (!text)
    return;

  parserReadLR1(parser, text.get());
}

static const string& lexTokenTranslate(const Scan::LexToken& lexToken) {
  static const unordered_set<string> gNameSet = {"IntegerLiteral",
                                                 "BooleanLiteral",
                                                 "CharacterLiteral",
                                                 "StringLiteral",
                                                 "NullLiteral",
                                                 "Identifier",
                                                 "BOF",
                                                 "EOF"};
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

static string expandEscapeSequence(const string& str) {
  string result;

  string octBuffer;
  bool octActive = false;
  size_t octMax = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (octActive) {
      if (str[i] > '7' || str[i] < '0' || octBuffer.size() == octMax) {
        unsigned char value = 0;
        size_t octLen = octBuffer.length();
        value |= ((unsigned char)(octBuffer[octLen - 1] - '0')) & 7;
        if (octLen > 1)
          value |= ((unsigned char)(octBuffer[octLen - 2] - '0') & 7) << 3;
        if (octLen > 2)
          value |= ((unsigned char)(octBuffer[octLen - 3] - '0') & 7) << 6;
        result.push_back(value & 0x7f);

        octBuffer.clear();
        octActive = false;
        octMax = 0;
        --i;
      } else {
        octBuffer.push_back(str[i]);
      }
      continue;
    }

    if (str[i] != '\\') {
      result.push_back(str[i]);
      continue;
    }

    char value = 0;
    switch (str[i + 1]) {
      case 'b':
        value = 0x8;
        break;
      case 't':
        value = 0x9;
        break;
      case 'n':
        value = 0xa;
        break;
      case 'f':
        value = 0xc;
        break;
      case 'r':
        value = 0xd;
        break;
      case '"':
        value = 0x22;
        break;
      case '\'':
        value = 0x27;
        break;
      case '\\':
        value = 0x5c;
        break;
      default:
        break;
    }

    if (!value) {
      if (str[i + 1] < '4')
        octMax = 3;
      else
        octMax = 2;
      octActive = true;
    } else {
      result.push_back(value);
      ++i;
    }
  }
  return result;
}

static bool treeStackShiftTerminal(vector<Tree*>* stack, const Scan::LexToken& token) {
  if (token.name == "Identifier") {
    auto t = new TIdentifier;
    t->value = token.lexeme;
    stack->push_back(t);
    return true;
  }

  if (token.name == "IntegerLiteral") {
    auto t = new TIntegerLiteral;
    t->value = strtoul(token.lexeme.c_str(), nullptr, 10);
    stack->push_back(t);
    // reject values larger than 1<<31, to check if 1<<31 is actually a negated
    // literal in weeder
    return t->value <= (1u << 31);
  }

  if (token.name == "BooleanLiteral") {
    auto t = new TBooleanLiteral;
    if (token.lexeme == "true") {
      t->value = true;
    } else if (token.lexeme == "false") {
      t->value = false;
    } else {
      ASSERT(false);
    }
    stack->push_back(t);
    return true;
  }

  if (token.name == "StringLiteral") {
    auto t = new TStringLiteral;
    string newTok = token.lexeme.substr(1, token.lexeme.length() - 2);
    string expanded = expandEscapeSequence(newTok);
    t->value = expanded;
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
    string newTok = token.lexeme.substr(1, token.lexeme.length() - 2);
    string expanded = expandEscapeSequence(newTok);
    t->value = expanded[0];
    stack->push_back(t);
    return true;
  }
  return true;
}

ParseResult parserParse(Parser* parser, const vector<Scan::LexToken>& tokens) {
  vector<int> state_stack;
  vector<string> token_stack;
  vector<Tree*> tree_stack;

  ParseResult result;
  result.treeRoot = nullptr;
  result.errorLexTokenIndex = -1;
  result.valid = false;

  state_stack.push_back(0);
  s32 tokenIndex = 0;
  for (const auto& token : tokens) {
    const string& canonicalTokenName = lexTokenTranslate(token);

    while (true) {
      if (parser->joos_dfa.at(state_stack.back()).count(canonicalTokenName) ==
          0) {
        // invalid token at this state
        ptDeleteStack(&tree_stack);
        result.errorLexTokenIndex = tokenIndex;
        return result;
      }
      Transition next_rule =
          parser->joos_dfa.at(state_stack.back()).at(canonicalTokenName);
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

      if (parser->joos_dfa.at(state_stack.back()).count(token_stack.back()) ==
          0) {
        ptDeleteStack(&tree_stack);
        result.errorLexTokenIndex = tokenIndex;
        return result;
      }

      auto r = parser->joos_dfa.at(state_stack.back()).at(token_stack.back());
      if (r.first == SHIFT) {
        state_stack.push_back(r.second);
      } else {
        ASSERT(false);  // this can never happen
      }
    }

    ++tokenIndex;
  }

  result.treeRoot = tree_stack.front();
  result.errorLexTokenIndex = -1;
  result.valid = true;
  return result;
}

void parserDumpDebugInfo(const ParseResult& result,
                         const char* baseOutputPath) {
  strdecl512(filePath, "%s.parser.txt", baseOutputPath);
  FILE* dump = fopen(filePath, "w");
  fprintf(dump, "error at index %d\n", result.errorLexTokenIndex);
  fclose(dump);
}

static void parserTest() {
  Parser parser;
  s32 fileSize;
  unique_ptr<char[]> fileContents =
      readEntireFile("experimental/sample.lr1", &fileSize);
  if (!fileContents)
    return;

  parserReadLR1(&parser, fileContents.get());

  vector<pair<bool, vector<string>>> tests = {
      {true, {"BOF", "id", "-", "(", "id", "-", "id", ")", "EOF"}},
      {true, {"BOF", "id", "EOF"}},
      {true,
       {"BOF", "(", "id", "-", "id", ")", "-", "(", "id", "-", "id", ")",
        "EOF"}},
      {true, {"BOF", "(", "id", "-", "id", ")", "-", "id", "EOF"}},
      {true, {"BOF", "id", "-", "id", "EOF"}},
      {true,
       {"BOF", "(", "(", "id", "-", "id", ")", "-", "id", ")", "-", "id",
        "EOF"}},
      {true,
       {"BOF", "(", "id", "-", "(",  "id", "-", "(", "id", "-", "(",  "id",
        "-",   "(", "id", "-", "id", ")",  ")", ")", ")",  ")", "EOF"}},
      {true, {"BOF", "(",  "(", "(",  "(",  "(", "(",  "id", "-",  "id", ")",
              "-",   "id", ")", "-",  "id", ")", "-",  "(",  "id", "-",  "(",
              "id",  "-",  "(", "id", "-",  "(", "id", "-",  "(",  "id", "-",
              "id",  ")",  ")", ")",  ")",  ")", ")",  ")",  ")",  "EOF"}},
      {false,
       {"BOF", "id"}},  // BUG: accepts valid prefix if EOF marker is missing
      {false, {"BOF", "(", "EOF"}},
      {false, {"BOF", "(", ")", "EOF"}},
      {false, {"BOF", "id", "id", "EOF"}},
  };

  for (auto [expected, input] : tests) {
    auto result = can_parse(input, parser.rules, parser.joos_dfa);
    printf("expect: %d got: %d %s\n", expected, result,
           expected == result ? "" : "failed");
  }
}

}  // namespace Parse
