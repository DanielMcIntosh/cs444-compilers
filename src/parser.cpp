#include <memory>
#include <array>
#include <unordered_set>
#include <unordered_map>

#include "parserASTBase.h"
#include "parserAST.h"
#include "parser.h"

namespace Parse {

const char *newLines = "\r\n";
const char *Spaces = " ";

void lineHelper(char *buffer, const char **textPtr) {
  int len = strcspn(*textPtr, newLines);
  snprintf(buffer, len + 1, "%s", *textPtr);
  *textPtr += len;
  *textPtr += strspn(*textPtr, newLines);
}

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

      for (size_t i = 0; i < rules[rule_id].rhs.size(); ++i) {
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

void parserReadLR1(Parser *parser, const char *text) {
  const char *textPtr = text;

  char line[256];
  lineHelper(line, &textPtr);
  int numTerminal = atoi(line);
  for (int i = 0; i < numTerminal; ++i) {
    lineHelper(line, &textPtr);
  }

  lineHelper(line, &textPtr);

  int numNonTerminal = atoi(line);
  for (int i = 0; i < numNonTerminal; ++i) {
    lineHelper(line, &textPtr);
  }
  lineHelper(line, &textPtr);

  string startingSymbol(line);

  lineHelper(line, &textPtr);

  int numRules = atoi(line);
  for (int i = 0; i < numRules; ++i) {
    lineHelper(line, &textPtr);
    char *token = strtok(line, Spaces);
    string lhs(token);
    vector<string> rhses;
    while ((token = strtok(nullptr, Spaces))) {
      string rhs(token);
      rhses.push_back(rhs);
    }
    parser->rules.push_back({lhs, rhses});
  }
  lineHelper(line, &textPtr);

  int numDFAStates = atoi(line);
  (void)numDFAStates;

  lineHelper(line, &textPtr);
  int numTransitions = atoi(line);
  for (int i = 0; i < numTransitions; ++i) {
    lineHelper(line, &textPtr);
    int stateNum = atoi(strtok(line, Spaces));
    string symbol(strtok(nullptr, Spaces));
    string action(strtok(nullptr, Spaces));
    int stateOrRuleNumber = atoi(strtok(nullptr, Spaces));
    parser->joos_dfa[stateNum][symbol] = {action == "shift" ? SHIFT : REDUCE, stateOrRuleNumber};
  }

}

void parserReadJoosLR1(Parser *parser) {
  s32 fileSize;
  unique_ptr<char[]> text = readEntireFile("joos.lr1", &fileSize);
  if (!text)
    return;

  parserReadLR1(parser, text.get());
}

ParseResult parserParse(Parser *parser, const vector<Scan::LexToken> &tokens) {
  (void)parser;
  (void)tokens;
  ParseResult result;
  result.valid = false;

  return result;
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

namespace AutoAST {

struct TerminalInfo {
  string originalName;
  string alphabeticalName;

  bool needCapture;
};

struct NonTerminalRule {
  s32 ruleId;
  string serial;
  string lhs;
  vector<string> rhs;
};

struct NonTerminalInfo {
  string originalName;

  vector<NonTerminalRule *> rules;
};

struct AutoAST {
  unordered_map<string, TerminalInfo> terminalMap;
  unordered_map<string, NonTerminalInfo> nonTerminalMap;
  unordered_map<s32, NonTerminalRule *> ruleIdMap;

  vector<unique_ptr<NonTerminalRule>> ruleList;
};

void autoASTShiftCapturedTerminal(AutoAST *autoast) {

}

void autoASTApplyRule(AutoAST *autoast, s32 ruleId) {
  
}

bool isTerminalCapture(const string &originalName);
string getAlphabeticalName(const string &terminal);

void autoASTJoosInit(AutoAST *autoast) {
  
}

void autoASTReadLR1(AutoAST *autoast, const char *lr1Text) {
  const char *textPtr = lr1Text;

  char line[256];
  lineHelper(line, &textPtr);
  int numTerminal = atoi(line);
  for (int i = 0; i < numTerminal; ++i) {
    lineHelper(line, &textPtr);
    string name(line);

    ASSERT(!autoast->terminalMap.count(name));
    auto result = autoast->terminalMap.insert(make_pair(name, TerminalInfo()));
    TerminalInfo *info = &result.first->second;
    info->originalName = name;
    info->alphabeticalName = getAlphabeticalName(name);
    info->needCapture = isTerminalCapture(name);
  }
  lineHelper(line, &textPtr);

  int numNonTerminal = atoi(line);
  for (int i = 0; i < numNonTerminal; ++i) {
    lineHelper(line, &textPtr);
    string name(line);

    ASSERT(!autoast->terminalMap.count(name));
    ASSERT(!autoast->nonTerminalMap.count(name));
    auto result = autoast->nonTerminalMap.insert(make_pair(name, NonTerminalInfo()));
    NonTerminalInfo *info = &result.first->second;
    info->originalName = name;
  }
  lineHelper(line, &textPtr);

  string startingSymbol(line);
  lineHelper(line, &textPtr);

  int numRules = atoi(line);
  for (int i = 0; i < numRules; ++i) {
    lineHelper(line, &textPtr);
    char *token = strtok(line, Spaces);
    string lhs(token);

    ASSERT(!autoast->terminalMap.count(lhs));
    ASSERT(autoast->nonTerminalMap.count(lhs));

    auto nit = autoast->nonTerminalMap.find(lhs);
    NonTerminalInfo *info = &nit->second;

    auto newRule = make_unique<NonTerminalRule>();
    newRule->ruleId = i;
    newRule->lhs = lhs;
    while ((token = strtok(nullptr, Spaces))) {
      string rhs(token);
      string representation;
      auto it = autoast->terminalMap.find(rhs);
      if (it != autoast->terminalMap.end()) {
        // Terminal symbol
        representation = it->second.alphabeticalName;
      } else {
        // Non terminal
        representation = rhs;
      }

      newRule->serial.append(representation);
      newRule->rhs.push_back(rhs);
    }
    info->rules.push_back(newRule.get());
    autoast->ruleIdMap.insert(make_pair(i, newRule.get()));
    autoast->ruleList.push_back(move(newRule));
  }
}

void autoASTOutputHeaders(AutoAST *autoast) {
  // Output begin

  FILE *parserNodeHdr = fopen("src/parserNode.h", "w");

  { // header
    string _output, *output = &_output;
    output->append("#pragma once\n");
    output->append("namespace Parse { \n");
    fwrite(output->data(), output->length(), 1, parserNodeHdr);
  }

  { // Terminal Type
    string _output, *output = &_output;
    const s32 width = 25;

    output->append("enum class TerminalType {\n");
    for (const auto &[name, info]: autoast->terminalMap) {
      s32 padding = width - info.alphabeticalName.length();
      strAppend(output,
                "  %s,  %*s %s \n", info.alphabeticalName.c_str(), padding, "//", info.originalName.c_str());
    }
    output->append("  Max,\n};\n\n");
    fwrite(output->data(), output->length(), 1, parserNodeHdr);
  }

  { // Non Terminal Type
    string _output, *output = &_output;

    output->append("enum class NonTerminalType {\n");
    for (const auto &[name, info]: autoast->nonTerminalMap) {
      strAppend(output, "  %s, \n", name.c_str());
    }
    output->append("  Max,\n};\n\n");
    fwrite(output->data(), output->length(), 1, parserNodeHdr);
  }

  { // Forward declarations
    string _output, *output = &_output;

    for (const auto &[name, info] : autoast->terminalMap) {
      if (info.needCapture)
        strAppend(output, "struct Tree%s;\n", name.c_str());
    }

    for (const auto &[name, info]: autoast->nonTerminalMap) {
      strAppend(output, "struct Tree%s;\n", name.c_str());
    }
    output->append("\n");
    fwrite(output->data(), output->length(), 1, parserNodeHdr);
  }

  { // footer
    string _output, *output = &_output;
    output->append("} // namespace Parse \n");
    fwrite(output->data(), output->length(), 1, parserNodeHdr);
  }
  fclose(parserNodeHdr);

  FILE *parserASTHdr = fopen("src/parserAST.h", "w");

  { // header
    string _output, *output = &_output;
    output->append("#pragma once\n");
    output->append("#include \"parserASTBase.h\"\n");
    output->append("namespace Parse { \n");
    fwrite(output->data(), output->length(), 1, parserASTHdr);
  }

  { // Tree subclasses and variants
    string _output, *output = &_output;
    size_t maxChildren = 0;

    for (const auto &[name, info]: autoast->nonTerminalMap) {
      // enum class NT*Variants
      strAppend(output,
                "enum class NT%sVariants {\n", name.c_str());
      for (const NonTerminalRule *rule: info.rules) {
        if (rule->serial.empty())
          continue;
        
        strAppend(output, "  %s,  // ", rule->serial.c_str());

        for (const string &rhs: rule->rhs) {
          output->append(rhs);
          output->append(" ");
        }
        output->append("\n");
      }

      output->append("  Max,\n};\n\n");

      // Tree subclass
      strAppend(output,
                "struct Tree%s: public Tree {\n", name.c_str());

      strAppend(output, "  enum NT%sVariants variant;\n", name.c_str());

      { // Figure out all non terminal children as well as terminals that
        // need capturing, and emit fields for them.
        unordered_set<string> capturingChildren;
        for (const NonTerminalRule *rule: info.rules) {
          for (const string &rhs: rule->rhs) {
            if (autoast->nonTerminalMap.count(rhs)) {
              // always emit field for non terminals
              capturingChildren.insert(rhs);
            } else {
              auto it = autoast->terminalMap.find(rhs);
              ASSERT(it != autoast->terminalMap.end());
              if (it->second.needCapture)
                capturingChildren.insert(it->second.alphabeticalName);
            }
          }
        }
        maxChildren = max(capturingChildren.size(), maxChildren);

        for (const string &child: capturingChildren) {
          strAppend(output,
                    "  Tree%s* %s;\n", child.c_str(), child.c_str());
        }
      }

      output->append("};\n\n");

      fwrite(output->data(), output->length(), 1, parserASTHdr);
      output->clear();
    } // for each non terminal

    ASSERT(maxChildren <= TreeMaxChild);
  }

  { // footer
    string _output, *output = &_output;
    output->append("} // namespace Parse \n");
    fwrite(output->data(), output->length(), 1, parserASTHdr);
  }

  fclose(parserASTHdr);  
}

string getAlphabeticalName(const string &terminal) {
  static const unordered_map<string, string> gTerminalToStrMap = {
          {"(", "LPar"},
          {")", "RPar"},
          {"{", "LCBr"},
          {"}", "RCBr"},
          {"[", "LSBr"},
          {"]", "RSBr"},
          {";", "SCol"},
          {",", "Com"},
          {".", "Dot"},
          {"=", "Eq"},
          {">", "Gr"},
          {"<", "Le"},
          {"!", "Bang"},
          {"~", "Til"},
          {"?", "Q"},
          {"&", "Amp"},
          {":", "Col"},
          {"+", "Plus"},
          {"-", "Minus"},
          {"*", "Star"},
          {"/", "RSlash"},
          {"%", "Perc"},
          {"^", "Up"},
          {"|", "Or"},
          {"while", "While"},
          {"this", "This"},
          {"void", "Void"},
          {"short", "Short"},
          {"new", "New"},
          {"char", "Char"},
          {"static", "Static"},
          {"class", "Class"},
          {"else", "Else"},
          {"for", "For"},
          {"if", "If"},
          {"int", "Int"},
          {"protected", "Protected"},
          {"public", "Public"},
          {"return", "Return"},
          {"EOF", "Eof"}
  };

  {
    auto it = gTerminalToStrMap.find(terminal);
    if (it != gTerminalToStrMap.end())
      return it->second;
  }

  string result;
  for (char c : terminal) {
    string s{c};
    auto it = gTerminalToStrMap.find(s);
    if (it != gTerminalToStrMap.end())
      result.append(it->second);
    else
      result.push_back(c);
  }

  return result;
}

bool isTerminalCapture(const string &originalName) {
  static const unordered_set<string> gCaptureTerminal = {
          "IntegerLiteral",
          "BooleanLiteral",
          "CharacterLiteral",
          "StringLiteral",
          "NullLiteral",
          "Identifier",
  };

  return gCaptureTerminal.count(originalName);
}

AutoAST *autoASTCreate() {
  return new AutoAST;
}

void autoASTDestory(AutoAST *ast) {
  delete ast;
}

} // namespace AutoAST
} // namespace Parse
