#include <iostream>
#include <vector>
#include <optional>
#include <stack>
#include <unordered_map>
#include <map>
#include <string>
#include <string.h>

#include <stdlib.h>
using namespace std;

enum action {
    SHIFT,
    REDUCE
};
using state = int;
using transition = pair<action, int>; // (SHIFT, state) or (REDUCE, rule_id)
using dfa = unordered_map<state, unordered_map<string, transition>>;

struct rule {
    string lhs;
    vector<string> rhs;
};

vector<rule> rules;
stack<state> state_stack;
stack<string> token_stack;
dfa joos_dfa;

const char *newLines = "\r\n";
const char *Spaces = " ";

optional<state> follow(const state s, const string t, const vector<rule>& rules,
        stack<state>& state_stack, stack<string>& token_stack, const dfa& d) {
    printf("state %d, token %s\n", s, t.c_str());
    if (d.at(s).count(t) == 0) return nullopt;
    auto [action, id] = d.at(s).at(t);
    if (action == SHIFT) {
        printf("SHIFT\n");
        token_stack.push(t);
        state_stack.push(id);
    } else {
        printf("REDUCE\n");
        for (int i = 0; i < rules[id].rhs.size(); ++i) {
            token_stack.pop();
            state_stack.pop();
        }
        token_stack.push(rules[id].lhs);
    }
    return state_stack.top();
}


void lineHelper(char *buffer, const char **textPtr) {
    int len = strcspn(*textPtr, newLines);
    snprintf(buffer, len + 1, "%s", *textPtr);
    *textPtr += len;
    *textPtr += strspn(*textPtr, newLines);
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
    /*
    *
    * Number of Terminals
    *
    */
    int numTerminal = atoi(line);
    
    printf("Terminals: %d\n", numTerminal);
    
    for (int i = 0; i < numTerminal; ++i) {
        lineHelper(line, &textPtr);
        
        printf("%s\n", line);
    }
    
    lineHelper(line, &textPtr);
    
    /*
    *
    * Number of Non terminals
    *
    */
    int numNonTerminal = atoi(line);
    
    printf("Non terminals: %d\n", numNonTerminal);
    
    for (int i = 0; i < numNonTerminal; ++i) {
        lineHelper(line, &textPtr);
        printf("%s\n", line);
    }
    
    lineHelper(line, &textPtr);
    
    /*
    *
    * Starting symbol
    *
    */
    
    string startingSymbol(line);
    
    printf("Starting symbol: %s\n", startingSymbol.c_str());
    
    lineHelper(line, &textPtr);
    
    /*
    *
    * Number of rules
    *
    */
    
    int numRules = atoi(line);
    
    printf("Productions rules: %d\n", numRules);
    
    for (int i = 0; i < numRules; ++i) {
        lineHelper(line, &textPtr);
        
        char *token = strtok(line, Spaces);
        string lhs(token);
        
        printf("%s -> ", lhs.c_str());

        vector<string> rhses;
        
        while ((token = strtok(0, Spaces))) {
            string rhs(token);
            printf("%s ", rhs.c_str());
            rhses.push_back(rhs);
        }

        rules.push_back({lhs, rhses});
        
        printf("\n");
    }
    
    lineHelper(line, &textPtr);
    
    /*
    *
    * Number of DFA States
    *
    */
    
    int numDFAStates = atoi(line);
    
    lineHelper(line, &textPtr);
    
    /*
    *
    * Number of transitions
    *
    */
    
    int numTransitions = atoi(line);
    
    printf("%d DFA States, %d transitions\n", numDFAStates, numTransitions);
    
    for (int i = 0; i < numTransitions; ++i) {
        lineHelper(line, &textPtr);
        
        int stateNum = atoi(strtok(line, Spaces));
        
        string symbol(strtok(0, Spaces));
        
        string action(strtok(0, Spaces));
        
        int stateOrRuleNumber = atoi(strtok(0, Spaces));
        
        printf("Action: %s, %d -> %s -> %d\n", action.c_str(), stateNum, symbol.c_str(), stateOrRuleNumber);

        joos_dfa[stateNum][symbol] = {action == "shift" ? SHIFT : REDUCE, stateOrRuleNumber};
    }

    vector<string> test{"BOF", "id", "-", "(", "id", "-", "id", ")", "EOF"};
    state current_state = 0;
    bool accepted = true;
    for (auto token : test) {
        auto result = follow(current_state, token, rules, state_stack, token_stack, joos_dfa);
        if (result) {
            current_state = *result;
        } else {
            accepted = false;
            break;
        }
    }
    if (accepted) {
        printf("accepted\n");
    } else {
        printf("rejected\n");
    }
}
