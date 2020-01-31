#include "parser.h"

#include <memory>

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
    if (!fileSize)
      return;

    parserReadLR1(parser, text.get());
  }

  ParseResult parserParse(Parser *parser, const vector<Scan::LexToken> &tokens) {
    ParseResult result;
    result.valid = false;

    return result;
  }

  void parserTest(const Parser *parser) {
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
      auto result = can_parse(input, parser->rules, parser->joos_dfa);
      printf("expect: %d got: %d %s\n", expected, result, expected == result ? "" : "failed");
    }  
  }
  
}
