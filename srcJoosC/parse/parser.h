#pragma once

#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <map>
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "../frontend.h"

namespace Parse {

using namespace std;

enum action { SHIFT, REDUCE };

using Transition = pair<action, int>;  // (SHIFT, state_id) or (REDUCE, rule_id)
using DFA = unordered_map<int, unordered_map<string, Transition>>;

struct Rule {
  string lhs;
  int rhsSize;
};

struct Parser {
  DFA joos_dfa;
  vector<Rule> rules;
};

void parserReadLR1(Parser* parser, const char* text);
void parserReadJoosLR1(Parser* parser);
void parserTest();
ParseResult parserParse(Parser* parser, const vector<Scan::LexToken>& tokens);
void parserDumpDebugInfo(const ParseResult& result, const char* baseOutputPath);

}  // namespace Parse
