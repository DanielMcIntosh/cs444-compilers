#include <iostream>
#include <vector>
#include <optional>
#include <stack>
#include <unordered_map>
#include <map>
#include <string>
#include <cassert>

#include <stdlib.h>
#include <string.h>

using namespace std;

enum action {
    SHIFT,
    REDUCE
};
using transition = pair<action, int>; // (SHIFT, state_id) or (REDUCE, rule_id)
using dfa = unordered_map<int, unordered_map<string, transition>>;

struct rule {
    string lhs;
    vector<string> rhs;
};

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
    bool accepted = true;
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

            for (int i = 0; i < rules[rule_id].rhs.size(); ++i) {
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

int main()
{
    string buffer;
    while (true) {
        char buf[256];
        char *res = fgets(buf, 256, stdin);
        if (!res)
            break;
        buffer.append(string(res));
    }
    
    const char *text = buffer.data();
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
    vector<rule> rules;
    for (int i = 0; i < numRules; ++i) {
        lineHelper(line, &textPtr);        
        char *token = strtok(line, Spaces);
        string lhs(token);        
        vector<string> rhses;        
        while ((token = strtok(0, Spaces))) {
            string rhs(token);
            rhses.push_back(rhs);
        }
        rules.push_back({lhs, rhses});        
    }    
    lineHelper(line, &textPtr);    
    int numDFAStates = atoi(line);    
    lineHelper(line, &textPtr);    
    int numTransitions = atoi(line);    
    dfa joos_dfa;
    for (int i = 0; i < numTransitions; ++i) {
        lineHelper(line, &textPtr);        
        int stateNum = atoi(strtok(line, Spaces));        
        string symbol(strtok(0, Spaces));        
        string action(strtok(0, Spaces));        
        int stateOrRuleNumber = atoi(strtok(0, Spaces));        
        joos_dfa[stateNum][symbol] = {action == "shift" ? SHIFT : REDUCE, stateOrRuleNumber};
    }

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
        auto result = can_parse(input, rules, joos_dfa);
        printf("expect: %d got: %d %s\n", expected, result, expected == result ? "" : "failed");
    }
}
