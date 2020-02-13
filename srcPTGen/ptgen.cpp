#include <array>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

void lineHelper(char *buffer, const char **textPtr);
void strAppend(std::string *str, const char *fmt, ...);
void strFlushFILE(std::string *output, FILE *file);
std::unique_ptr<char[]> readEntireFile(const char *path, int *size);
const char *newLines = "\r\n";
const char *Spaces = " ";
constexpr int TWO_TO_EIGHT = 256;

namespace PTGen {

using namespace std;

struct TerminalInfo {
  string originalName;
  string alphabeticalName;
};

struct NonTerminalRule {
  int ruleId;
  string serial;
  string lhs;
  vector<string> rhs;
  vector<int> captureIndices;
  bool singleNonTermChild;
};

struct NonTerminalInfo {
  vector<NonTerminalRule *> rules;
};

const int MaxNumRule = 256;

struct PTGen {
  map<string, TerminalInfo> terminalMap;
  map<string, NonTerminalInfo> nonTerminalMap;
  array<NonTerminalRule *, MaxNumRule> ruleById;
  int numRules;

  vector<unique_ptr<NonTerminalRule>> ruleList;
};

struct ExtraFieldInfo {
  string typeName;
  string fieldName;
};

bool isTerminalCapture(const string &originalName);
const vector<ExtraFieldInfo> &getExtraFieldForTree(const string &name);
string getAlphabeticalName(const string &terminal);

void ptgenReadLR1(PTGen *ptgen, const char *lr1Text) {
  const char *textPtr = lr1Text;

  char line[256];
  lineHelper(line, &textPtr);
  int numTerminal = atoi(line);
  for (int i = 0; i < numTerminal; ++i) {
    lineHelper(line, &textPtr);
    string name(line);

    assert(!ptgen->terminalMap.count(name));
    auto result = ptgen->terminalMap.insert(make_pair(name, TerminalInfo()));
    TerminalInfo *info = &result.first->second;
    info->originalName = name;
    info->alphabeticalName = getAlphabeticalName(name);

    if (isTerminalCapture(name))
      ptgen->nonTerminalMap.insert(make_pair(name, NonTerminalInfo()));
  }
  lineHelper(line, &textPtr);

  int numNonTerminal = atoi(line);
  for (int i = 0; i < numNonTerminal; ++i) {
    lineHelper(line, &textPtr);
    string name(line);

    assert(!ptgen->terminalMap.count(name));
    assert(!ptgen->nonTerminalMap.count(name));
    ptgen->nonTerminalMap.insert(make_pair(name, NonTerminalInfo()));
  }
  lineHelper(line, &textPtr);

  string startingSymbol(line);
  lineHelper(line, &textPtr);

  int numRules = atoi(line);
  assert(MaxNumRule >= numRules);
  ptgen->numRules = numRules;
  for (int i = 0; i < numRules; ++i) {
    lineHelper(line, &textPtr);
    char *token = strtok(line, Spaces);
    string lhs(token);

    assert(!ptgen->terminalMap.count(lhs));
    assert(ptgen->nonTerminalMap.count(lhs));

    auto nit = ptgen->nonTerminalMap.find(lhs);
    NonTerminalInfo *info = &nit->second;

    auto newRule = make_unique<NonTerminalRule>();
    newRule->ruleId = i;
    newRule->lhs = lhs;

    int index = 0;
    while ((token = strtok(nullptr, Spaces))) {
      string rhs(token);
      string representation;
      auto it = ptgen->terminalMap.find(rhs);
      if (it != ptgen->terminalMap.end()) {
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
    if (newRule->rhs.size() == 1 && newRule->captureIndices.size() == 1 &&
        !isTerminalCapture(newRule->rhs[0])) {
      newRule->singleNonTermChild = true;
    } else {
      newRule->singleNonTermChild = false;
    }
    info->rules.push_back(newRule.get());
    ptgen->ruleById[i] = newRule.get();
    ptgen->ruleList.push_back(move(newRule));
  }
}

void ptgenOutputHeaders(PTGen *ptgen) {
  // Output begin

  FILE *parserNodeHdr = fopen("srcJoosC/parse/parseTreeNode.h", "w");

  { // header
    string _output, *output = &_output;
    output->append("#pragma once\n");
    output->append("namespace Parse { \n");
    strFlushFILE(output, parserNodeHdr);
  }

  { // Terminal Type
    string _output, *output = &_output;
    const int width = 25;

    output->append("enum class TerminalType {\n");
    for (const auto &[name, info]: ptgen->terminalMap) {
      int padding = width - info.alphabeticalName.length();
      strAppend(output,
                "  %s,  %*s %s \n", info.alphabeticalName.c_str(), padding, "//", info.originalName.c_str());
    }
    output->append("  Max,\n};\n\n");
    strFlushFILE(output, parserNodeHdr);
  }

  { // Non Terminal Type
    string _output, *output = &_output;

    output->append("enum class NonTerminalType {\n");
    for (const auto &[name, info]: ptgen->nonTerminalMap) {
      strAppend(output, "  %s, \n", name.c_str());
    }

    output->append("  Max,\n};\n\n");
    strFlushFILE(output, parserNodeHdr);
  }

  { // Forward declarations
    string _output, *output = &_output;

    for (const auto &[name, info]: ptgen->nonTerminalMap) {
      strAppend(output, "struct T%s;\n", name.c_str());
    }
    output->append("\n");
    strFlushFILE(output, parserNodeHdr);
  }

  { // footer
    string _output, *output = &_output;
    output->append("} // namespace Parse \n");
    strFlushFILE(output, parserNodeHdr);
  }
  fclose(parserNodeHdr);

  FILE *parserASTHdr = fopen("srcJoosC/parse/parseTree.h", "w");

  { // header
    string _output, *output = &_output;
    output->append("#pragma once\n");
    output->append("#include \"parseTreeBase.h\"\n");
    output->append("namespace Parse { \n");
    strFlushFILE(output, parserASTHdr);
  }

  { // Tree subclasses and variants
    string _output, *output = &_output;
    size_t maxChildren = 0;

    for (const auto &[name, info]: ptgen->nonTerminalMap) {
      // enum class NT*Variants
      strAppend(output,
                "enum class T%sV {\n", name.c_str());
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

      // Tree subclass T*
      strAppend(output,
                "struct T%s: public Tree {\n", name.c_str());

      strAppend(output, "  enum T%sV v;\n", name.c_str());

      { // Figure out all non terminal children as well as terminals that
        // need capturing, and emit fields for them.
        unordered_map<string, int> captureOccr;
        for (const NonTerminalRule *rule: info.rules) {
          unordered_map<string, int> ruleOccr;
          for (const string &rhs: rule->rhs) {
            if (!ptgen->nonTerminalMap.count(rhs))
              continue;
            ruleOccr[rhs]++;
          }
          for (const auto &[name, occr]: ruleOccr) {
            captureOccr[name] = max(captureOccr[name], ruleOccr[name]);
          }
        }
        maxChildren = max(captureOccr.size(), maxChildren);

        for (const auto &[name, times]: captureOccr) {
          string memberName = name;
          // want lower case member name
          memberName[0] += 'a' - 'A';
          string timeStr;
          for (int i = 0; i < times; ++i) {
            if (i >= 1)
              timeStr = to_string(i + 1);
            strAppend(output,
                      "  T%s* %s%s;\n", name.c_str(), memberName.c_str(),
                      timeStr.c_str());            
          }
        }

        // For Tree*Literals and Identifiers, emit additional fields for values they hold.
        const vector<ExtraFieldInfo> &extraFieldInfo = getExtraFieldForTree(name);
        for (const ExtraFieldInfo &fieldInfo : extraFieldInfo) {
          strAppend(output, "  %s %s;\n", fieldInfo.typeName.c_str(), fieldInfo.fieldName.c_str());
        }

        // default constructor
        output->append("\n");
        strAppend(output,
                  "  T%s(): Tree(NonTerminalType::%s), v(T%sV::Max)",
                  name.c_str(), name.c_str(), name.c_str());
        if (!captureOccr.empty()) {
          // generate initializer list for members
          for (const auto &[name, times] : captureOccr) {
            string memberName = name;
            // want lower case member name
            memberName[0] += 'a' - 'A';
            string timeStr;
            for (int i = 0; i < times; ++i) {
              if (i >= 1)
                timeStr = to_string(i + 1);
              strAppend(output,
                        ", %s%s(nullptr)", memberName.c_str(), timeStr.c_str());
            }            
          }
        }
        output->append("{\n\n  }\n");
      }

      output->append("};\n\n");

      strFlushFILE(output, parserASTHdr);
    } // for each non terminal

    //assert(maxChildren <= TreeMaxChild);
  }

  { // footer
    string _output, *output = &_output;
    output->append("} // namespace Parse \n");
    strFlushFILE(output, parserASTHdr);
  }

  fclose(parserASTHdr);

  FILE *parserASTImpl = fopen("srcJoosC/parse/parseTreeImpl.cpp", "w");

  { // header
    string _output, *output = &_output;
    output->append("#include \"parseTreeBase.h\"\n");
    output->append("#include \"parseTree.h\"\n");
    output->append("#include \"parseTreeNode.h\"\n\n");
    output->append("namespace Parse { \n\n");
    output->append("using namespace std;\n\n");
    strFlushFILE(output, parserASTImpl);
  }

  { // functions
    string _output, *output = &_output;
    for (const auto &rule : ptgen->ruleList) {
      const char *lhsName = rule->lhs.c_str();
      strAppend(output, "// %s -> ", lhsName);
      for (const string &rhs: rule->rhs) {
        output->append(rhs);
        output->append(" ");
      }
      output->append("\n");
      strAppend(output, "void pt%s_%s(%s) {\n", lhsName,
                rule->serial.c_str(),
                "vector<Tree *> *stack");
      size_t captureSize = rule->captureIndices.size();
      unordered_map<string, int> captureOccr;
      if (rule->rhs.empty())
        goto FuncGenEnd;

      // int n = stack->size();
      output->append("  int n = stack->size();\n");
      // assert(n >= *);
      strAppend(output, "  assert(n >= %ld);\n", captureSize);

      for (size_t i = 0; i < captureSize; ++i) {
        int index = rule->captureIndices[i];
        //   assert((*stack)[n - *]->type == NonTerminalType::*);
        strAppend(output, "  assert((*stack)[n - %ld]->type == NonTerminalType::%s);\n",
                  captureSize - i, rule->rhs[index].c_str());
      }

      // auto t = new Tree*;
      strAppend(output, "  auto t = new T%s;\n", lhsName);
      // parserASTSetTopParents(stack, *, t);
      strAppend(output, "  ptSetTopParents(stack, %ld, t);\n", captureSize);
      // ptPopulateChildrenList(t, stack, *);
      strAppend(output, "  ptPopulateChildrenList(t, *stack, %ld);\n", captureSize);

      // t->variant = NT*::*;
      strAppend(output, "  t->v = T%sV::%s;\n", lhsName, rule->serial.c_str());
      // t->oneNt = *;
      strAppend(output, "  t->oneNt = %s;\n",
                rule->singleNonTermChild ? "true" : "false");
      
      for (size_t i = 0; i < captureSize; ++i) {
        int index = rule->captureIndices[i];
        string memberName = rule->rhs[index];
        int numOccr = ++captureOccr[memberName];
        string timeStr;
        if (numOccr >= 2)
          timeStr = to_string(numOccr);
        // want lower case member name
        memberName[0] += 'a' - 'A';
        // t->* = dynamic_cast<Tree* *>((*stack)[n - *]);
        strAppend(output,
                  "  t->%s%s = dynamic_cast<T%s *>((*stack)[n - %ld]);\n",
                  memberName.c_str(), timeStr.c_str(), rule->rhs[index].c_str(),
                  captureSize - i);
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
    output->append("void ptDispatcher(vector<Tree *> *stack, int ruleID) {\n");
    output->append("  static const ptFunc table[] = {\n");
    for (int i = 0; i < ptgen->numRules; ++i) {
      strAppend(output,
                "    pt%s_%s, \n",
                ptgen->ruleById[i]->lhs.c_str(),
                ptgen->ruleById[i]->serial.c_str());
    }
    strAppend(output, "  };\n  table[ruleID](stack);\n}\n\n");
    strFlushFILE(output, parserASTImpl);
  }

  { // footer
    string _output, *output = &_output;
    output->append("} // namespace Parse \n");
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
          {"IntegerLiteral", {{"unsigned int", "value"}}}, // nmed to be able to store 1<<31
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

} // namespace PTGen

void lineHelper(char *buffer, const char **textPtr) {
  int len = strcspn(*textPtr, newLines);
  snprintf(buffer, len + 1, "%s", *textPtr);
  *textPtr += len;
  *textPtr += strspn(*textPtr, newLines);
}

void strAppend(std::string *str, const char *fmt, ...) {
  char buffer[TWO_TO_EIGHT];
	va_list arg;
	va_start(arg, fmt);
	vsnprintf(buffer, TWO_TO_EIGHT, fmt, arg);
	va_end(arg);

  str->append(buffer);
}

void strFlushFILE(std::string *output, FILE *file) {
  fwrite(output->data(), output->length(), 1, file);
  output->clear();
}

std::unique_ptr<char[]> readEntireFile(const char *path, int *size) {
	*size = 0;

	FILE *file = fopen(path, "rb");
	if (!file)
		return nullptr;

	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	std::unique_ptr<char[]> filePtr(new char[fileSize + 1]);

	fread(filePtr.get(), fileSize, 1, file);
	filePtr[fileSize] = '\0';

	*size = fileSize;
	return filePtr;
}

int main() {
  int size;
  auto fileContent = readEntireFile("joos.lr1", &size);
  if (!fileContent)
    return 1;

  PTGen::PTGen gen;
  PTGen::ptgenReadLR1(&gen, fileContent.get());
  PTGen::ptgenOutputHeaders(&gen);
}
