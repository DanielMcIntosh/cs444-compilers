#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <unordered_map>

#include "utility.h"

namespace Scan {
  
using namespace std;

const s32 NumLetters = 128;

template <typename T>
struct Edge {
  char letter;
  T *state;

  bool operator<(const Edge &other) {
    return letter < other.letter;
  }

  bool operator==(const Edge &other) {
    return letter == other.letter;
  }  
};  

struct NState;
  
struct NState {
  vector<Edge<NState>> letterTransition;
  vector<NState *> epsilonTransitions;

  s32 index;
};

struct Token {   
  NState *startingNState;
  NState *acceptingNState;

  s32 index;
};

struct DState;

struct DState {
  vector<NState *> nstates;
  vector<Edge<DState>> transition;

  s32 index;
};

struct Scanner {
  unordered_map<string, Token *> tokenMap;

  vector<Token *> tokens;
  vector<NState *> nstates;
  vector<DState *> dstates;
};

void scannerRules(Scanner *scanner, const char *text);
void scannerNFAtoDFA(Scanner *scanner);
void scannerDumpDFA(const Scanner *scanner);
 
} // namespace Scan
