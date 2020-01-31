#pragma once

#include <iostream>
#include <vector>
#include <optional>
#include <stack>
#include <unordered_map>
#include <map>
#include <string>

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "scanParse.h"

namespace Parse {

  using namespace std;

  enum action
  {
   SHIFT,
   REDUCE
  };
  
  using transition = pair<action, int>; // (SHIFT, state_id) or (REDUCE, rule_id)
  using dfa = unordered_map<int, unordered_map<string, transition>>;

  struct rule {
    string lhs;
    vector<string> rhs;
  };

  struct Parser {
    dfa joos_dfa;
    vector<rule> rules;
  };

  void parserReadLR1(Parser *parser, const char *text);
  void parserReadJoosLR1(Parser *parser);
  ParseResult parserParse(Parser *parser, const vector<Scan::LexToken> &tokens);
}
