#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <memory>

#include "utility.h"

namespace Scan {
  
using namespace std;

const s32 NumLetters = 128;

template <typename T>
struct Edge {
  char letter;
  T *state;

  bool operator<(const Edge &other) const {
    return letter < other.letter;
  }

  bool operator==(const Edge &other) const {
    return letter == other.letter;
  }  
};  

struct NState;
struct Token;
  
struct NState {
  vector<Edge<NState>> letterTransition;
  vector<NState *> epsilonTransitions;

  s32 index;
  char stateSymbol;

  bool emit;
  Token *token;
};

struct Token {   
  NState *startingNState;
  NState *acceptingNState;

  s32 index;
  bool declared;
  bool emit;
  string name;
};

struct DState;

struct DState {
  vector<NState *> nstates;
  vector<Edge<DState>> transition;

  vector<string> tokenEmission;

  s32 index;
};

struct Scanner {
  unordered_map<string, Token *> tokenMap;

  vector<unique_ptr<Token>> tokens;
  vector<unique_ptr<NState>> nstates;
  vector<unique_ptr<DState>> dstates;

  multimap<s32, DState *> dstateMap;
};

void scannerRegularLanguageToNFA(Scanner *scanner, const char *text);
void scannerNFAtoDFA(Scanner *scanner);
void scannerDumpDFA(const Scanner *scanner);
 
} // namespace Scan
