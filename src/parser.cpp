#include <memory>
#include <array>
#include <unordered_set>
#include <unordered_map>

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

  bool can_parse(const vector<string>& input, const vector<rule>& rules, const dfa& joos_dfa) {
    vector<int> state_stack;
    vector<string> token_stack;
    state_stack.push_back(0);
    for (auto token : input) {
      while (true) {
        if (joos_dfa.at(state_stack.back()).count(token) == 0) {
          // invalid token at this state
          return false;
        }
        transition next_rule = joos_dfa.at(state_stack.back()).at(token);
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

    // Auto generation template
    // For use in the actual compiler

    enum class TerminalType
    {
      Max,
    };

    enum class NonTerminalType
    {
      Max,
    };

    enum class NodeType
    {
      NonTerminal,
      Terminal,
      Max
    };

    struct NodeTerminal {
      enum NodeType nodeType;
      enum TerminalType terminalType;
    };

    struct Tree;
    
    struct NodeNonTerminal {
      enum NodeType nodeType;
      Tree *tree;
    };
    
    union Node {
      NodeType nodeType;
      NodeTerminal terminal;
      NodeNonTerminal nonTerminal;
    };

    const int TreeMaxChild = 12;

    struct Tree {
      enum NonTerminalType type;

      array<Node, TreeMaxChild> children;
    };

    // For use in this program

    struct TerminalInfo {
      string originalName;
      string alphabeticalName;
    };

    struct NonTerminalRule {
      string serial;
      vector<string> rhs;
    };

    struct NonTerminalInfo {
      string originalName;

      vector<NonTerminalRule> rules;
    };

    struct AutoAST {
      unordered_map<string, TerminalInfo> terminalMap;
      unordered_map<string, NonTerminalInfo> nonTerminalMap;
    };

    string getAlphabeticalName(const char *terminal) {
      return string(terminal);
    }

    void autoASTGenerate(AutoAST *autoast, const char *lr1Text) {
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
        info->alphabeticalName = getAlphabeticalName(name.c_str());
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

        NonTerminalRule newRule;
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

          newRule.serial.append(representation);
          newRule.rhs.push_back(representation);
        }
        info->rules.push_back(newRule);
      }

      {
        string output;
        char lineBuffer[512];

        output.append("enum class TerminalType {");
        for (const auto &[name, info]: autoast->terminalMap) {
          snprintf(lineBuffer, 512, "  %s, \n", info.alphabeticalName.c_str());
          output.append(string(lineBuffer));
        }
        output.append("};");
      }

      {
        string output;
        char lineBuffer[512];

        output.append("enum class NonTerminalType {");
        for (const auto &[name, info]: autoast->nonTerminalMap) {
          snprintf(lineBuffer, 512, "  %s, \n", name.c_str());
          output.append(string(lineBuffer));
        }
        output.append("};");
      }
    }     
  } // namespace AutoAST
} // namespace Parse
