#include <memory>
#include <array>
#include <unordered_set>
#include <unordered_map>

#include "parserAutoAST.h"
#include "parserASTBase.h"

#ifndef PARSERAST_DISABLED
#include "parserAST.h"
#endif

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

void lineHelper(char *buffer, const char **textPtr) {
  int len = strcspn(*textPtr, newLines);
  snprintf(buffer, len + 1, "%s", *textPtr);
  *textPtr += len;
  *textPtr += strspn(*textPtr, newLines);
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

void treeStackShiftTerminal(vector<Tree *> *stack, const Scan::LexToken &token) {
  if (token.name == "Identifier") {
    auto t = new TreeIdentifier;
    t->value = token.lexeme;
    stack->push_back(t);
    return;
  }

  if (token.name == "IntegerLiteral") {
    auto t = new TreeIntegerLiteral;
    t->value = atoi(token.lexeme.c_str());
    stack->push_back(t);
    return;
  }

  if (token.name == "BooleanLiteral") {
    auto t = new TreeBooleanLiteral;
    /* TODO */
    stack->push_back(t);
    return;
  }

  if (token.name == "StringLiteral") {
    auto t = new TreeStringLiteral;
    t->value = token.lexeme;
    stack->push_back(t);
    return;
  }

  if (token.name == "NullLiteral") {
    auto t = new TreeNullLiteral;
    t->value = false;
    stack->push_back(t);
    return;
  }

  if (token.name == "CharacterLiteral") {
    auto t = new TreeCharacterLiteral;
    t->value = token.lexeme[0];
    stack->push_back(t);
    return;
  }
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
        parserASTDeleteStack(&tree_stack);
        result.errorLexTokenIndex = tokenIndex;
        return result;
      }
      Transition next_rule = parser->joos_dfa.at(state_stack.back()).at(canonicalTokenName);
      auto [action, rule_id] = next_rule;
      if (action == SHIFT) {
        auto next_state = rule_id;
        token_stack.push_back(canonicalTokenName);
        state_stack.push_back(next_state);
        treeStackShiftTerminal(&tree_stack, token);
        break;
      }

      parserASTDispatcher(&tree_stack, rule_id);
      for (size_t i = 0; i < parser->rules[rule_id].rhs.size(); ++i) {
        token_stack.pop_back();
        state_stack.pop_back();
      }
      token_stack.push_back(parser->rules[rule_id].lhs);

      if (parser->joos_dfa.at(state_stack.back()).count(token_stack.back()) == 0) {
        parserASTDeleteStack(&tree_stack);
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

namespace AutoAST {

struct TerminalInfo {
  string originalName;
  string alphabeticalName;
};

struct NonTerminalRule {
  s32 ruleId;
  string serial;
  string lhs;
  vector<string> rhs;
  vector<s32> captureIndices;  
};

struct NonTerminalInfo {
  vector<NonTerminalRule *> rules;
};

const int MaxNumRule = 256;

struct AutoAST {
  unordered_map<string, TerminalInfo> terminalMap;
  unordered_map<string, NonTerminalInfo> nonTerminalMap;
  array<NonTerminalRule *, MaxNumRule> ruleById;
  s32 numRules;
  
  vector<unique_ptr<NonTerminalRule>> ruleList;
};

struct ExtraFieldInfo {
  string typeName;
  string fieldName;
};

bool isTerminalCapture(const string &originalName);
const vector<ExtraFieldInfo> &getExtraFieldForTree(const string &name);
string getAlphabeticalName(const string &terminal);

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

    if (isTerminalCapture(name))
      autoast->nonTerminalMap.insert(make_pair(name, NonTerminalInfo()));          
  }
  lineHelper(line, &textPtr);

  int numNonTerminal = atoi(line);
  for (int i = 0; i < numNonTerminal; ++i) {
    lineHelper(line, &textPtr);
    string name(line);

    ASSERT(!autoast->terminalMap.count(name));
    ASSERT(!autoast->nonTerminalMap.count(name));
    autoast->nonTerminalMap.insert(make_pair(name, NonTerminalInfo()));
  }
  lineHelper(line, &textPtr);

  string startingSymbol(line);
  lineHelper(line, &textPtr);

  int numRules = atoi(line);
  ASSERT(MaxNumRule >= numRules);
  autoast->numRules = numRules;
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

    s32 index = 0;
    while ((token = strtok(nullptr, Spaces))) {
      string rhs(token);
      string representation;
      auto it = autoast->terminalMap.find(rhs);
      if (it != autoast->terminalMap.end()) {
        // Terminal symbol
        representation = it->second.alphabeticalName;
        if (isTerminalCapture(rhs)) {
          newRule->captureIndices.push_back(index);
        }
      } else {
        // Non terminal
        representation = rhs;

        newRule->captureIndices.push_back(index);
      }

      newRule->serial.append(representation);
      newRule->rhs.push_back(rhs);

      ++index;
    }
    info->rules.push_back(newRule.get());
    autoast->ruleById[i] = newRule.get();
    autoast->ruleList.push_back(move(newRule));
  }
}

void autoASTOutputHeaders(AutoAST *autoast) {
  // Output begin

  FILE *parserNodeHdr = fopen("src/parserNode.h", "w");

  { // header
    string _output, *output = &_output;
    output->append("#pragma once\n");
    output->append("#ifndef PARSERAST_DISABLED\n");
    output->append("namespace Parse { \n");
    strFlushFILE(output, parserNodeHdr);
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
    strFlushFILE(output, parserNodeHdr);
  }

  { // Non Terminal Type
    string _output, *output = &_output;

    output->append("enum class NonTerminalType {\n");
    for (const auto &[name, info]: autoast->nonTerminalMap) {
      strAppend(output, "  %s, \n", name.c_str());
    }
    
    output->append("  Max,\n};\n\n");
    strFlushFILE(output, parserNodeHdr);    
  }

  { // Forward declarations
    string _output, *output = &_output;

    for (const auto &[name, info]: autoast->nonTerminalMap) {
      strAppend(output, "struct Tree%s;\n", name.c_str());
    }
    output->append("\n");
    strFlushFILE(output, parserNodeHdr);        
  }

  { // footer
    string _output, *output = &_output;
    output->append("} // namespace Parse \n");
    output->append("#endif // PARSERAST_DISABLED\n");    
    strFlushFILE(output, parserNodeHdr);            
  }
  fclose(parserNodeHdr);

  FILE *parserASTHdr = fopen("src/parserAST.h", "w");

  { // header
    string _output, *output = &_output;
    output->append("#pragma once\n");
    output->append("#include \"parserASTBase.h\"\n");
    output->append("#ifndef PARSERAST_DISABLED\n");    
    output->append("namespace Parse { \n");
    strFlushFILE(output, parserASTHdr);
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

      // Tree subclass Tree*
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
            }
          }
        }
        maxChildren = max(capturingChildren.size(), maxChildren);

        for (const string &child: capturingChildren) {
          string memberName = child;
          // want lower case member name
          memberName[0] += 'a' - 'A';
          strAppend(output,
                    "  Tree%s* %s;\n", child.c_str(), memberName.c_str());
        }

        // For Tree*Literals and Identifiers, emit additional fields for values they hold.
        const vector<ExtraFieldInfo> &extraFieldInfo = getExtraFieldForTree(name);
        for (const ExtraFieldInfo &fieldInfo : extraFieldInfo) {
          strAppend(output, "  %s %s;\n", fieldInfo.typeName.c_str(), fieldInfo.fieldName.c_str());
        }

        // default constructor
        output->append("\n");
        strAppend(output,
                  "  Tree%s(): Tree(NonTerminalType::%s), variant(NT%sVariants::Max)",
                  name.c_str(), name.c_str(), name.c_str());
        if (!capturingChildren.empty()) {
          // generate initializer list for members
          for (const string &child : capturingChildren) {
            string memberName = child;
            // want lower case member name
            memberName[0] += 'a' - 'A';            
            strAppend(output, ", %s(nullptr) ", memberName.c_str());
          }
        }
        output->append("{\n\n  }\n");
      }

      output->append("};\n\n");

      strFlushFILE(output, parserASTHdr);
    } // for each non terminal

    ASSERT(maxChildren <= TreeMaxChild);
  }

  { // footer
    string _output, *output = &_output;
    output->append("} // namespace Parse \n");
    output->append("#endif // PARSERAST_DISABLED\n");        
    strFlushFILE(output, parserASTHdr);
  }

  fclose(parserASTHdr);

  FILE *parserASTImpl = fopen("src/parserASTImpl.cpp", "w");

  { // header
    string _output, *output = &_output;
    output->append("#include \"parserASTBase.h\"\n");
    output->append("#ifndef PARSERAST_DISABLED\n");    
    output->append("#include \"parserAST.h\"\n");    
    output->append("#include \"parserNode.h\"\n\n");
    output->append("namespace Parse { \n\n");
    output->append("using namespace std;\n\n");
    strFlushFILE(output, parserASTImpl);
  }  

  { // functions
    string _output, *output = &_output;    
    for (const auto &rule : autoast->ruleList) {
      const char *lhsName = rule->lhs.c_str();
      strAppend(output, "// %s -> ", lhsName);
      for (const string &rhs: rule->rhs) {
        output->append(rhs);
        output->append(" ");
      }
      output->append("\n");      
      strAppend(output, "void parserAST%s_%s(%s) {\n", lhsName,
                rule->serial.c_str(),
                "vector<Tree *> *stack");
      size_t captureSize = rule->captureIndices.size();
      
      if (rule->rhs.empty())
        goto FuncGenEnd;

      // int n = stack->size();
      output->append("  int n = stack->size();\n");
      // assert(n >= *);  
      strAppend(output, "  assert(n >= %ld);\n", captureSize);
      
      for (size_t i = 0; i < captureSize; ++i) {
        s32 index = rule->captureIndices[i];
        //   assert((*stack)[n - *]->type == NonTerminalType::*);
        strAppend(output, "  assert((*stack)[n - %ld]->type == NonTerminalType::%s);\n",
                  captureSize - i, rule->rhs[index].c_str());
      }

      // auto t = new Tree*;
      strAppend(output, "  auto t = new Tree%s;\n", lhsName);
      // parserASTSetTopParents(stack, *, t);
      strAppend(output, "  parserASTSetTopParents(stack, %ld, t);\n", captureSize);

      strAppend(output, "  parserASTPopulateChildrenList(t, *stack, %ld);\n", captureSize);

      // t->variant = NT*::*;
      strAppend(output, "  t->variant = NT%sVariants::%s;\n", lhsName, rule->serial.c_str());
      for (size_t i = 0; i < captureSize; ++i) {
        s32 index = rule->captureIndices[i];
        string memberName = rule->rhs[index];
        // want lower case member name
        memberName[0] += 'a' - 'A';
        // t->* = dynamic_cast<Tree* *>((*stack)[n - *]);
        strAppend(output,
                  "  t->%s = dynamic_cast<Tree%s *>((*stack)[n - %ld]);\n",
                  memberName.c_str(), rule->rhs[index].c_str(), captureSize - i);
        // assert(t->*);
        strAppend(output, "  assert(t->%s);\n", memberName.c_str());
      }

      for (size_t i = 0; i < captureSize; ++i) {
        // stack->pop_back();
        strAppend(output, "  stack->pop_back();\n");
      }

      // stack->push_back(t);
      strAppend(output, "  stack->push_back(t);\n");
    FuncGenEnd:
      strAppend(output, "}\n\n");
    }
    strFlushFILE(output, parserASTImpl);
  }

  { // dispatch table
    string _output, *output = &_output;    
    output->append("void parserASTDispatcher(vector<Tree *> *stack, int ruleID) {\n");
    output->append("  static const parserASTFunc table[] = {\n");
    for (s32 i = 0; i < autoast->numRules; ++i) {
      strAppend(output,
                "    parserAST%s_%s, \n",
                autoast->ruleById[i]->lhs.c_str(),
                autoast->ruleById[i]->serial.c_str());
    }
    strAppend(output, "  };\n  table[ruleID](stack);\n}\n\n");
    strFlushFILE(output, parserASTImpl);
  }

  { // footer
    string _output, *output = &_output;
    output->append("} // namespace Parse \n");
    output->append("#endif // PARSERAST_DISABLED\n");        
    strFlushFILE(output, parserASTImpl);
  }  

  fclose(parserASTImpl);  
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
          {"this", "This2"},
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

const vector<ExtraFieldInfo> &getExtraFieldForTree(const string &name) {
  static const unordered_map<string, vector<ExtraFieldInfo>> gExtraFieldMap = {
          {"CharacterLiteral", {{"char", "value"}}},
          {"IntegerLiteral", {{"int", "value"}}},
          {"StringLiteral", {{"string", "value"}}},
          {"BooleanLiteral", {{"bool", "value"}}},
          {"NullLiteral", {{"bool", "value"}}},
          {"Identifier", {{"string", "value"}}},
  };
  static const vector<ExtraFieldInfo> gNullExtraField;
  if (!gExtraFieldMap.count(name))
    return gNullExtraField;
  return gExtraFieldMap.find(name)->second;
}

AutoAST *autoASTCreate() {
  return new AutoAST;
}

void autoASTDestory(AutoAST *ast) {
  delete ast;
}

} // namespace AutoAST
} // namespace Parse
