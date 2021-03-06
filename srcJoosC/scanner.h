#pragma once

#include <algorithm>
#include <array>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "frontend.h"
#include "utility.h"

namespace Scan {

using namespace std;

const s32 NumLetters = 128;

template <typename T>
struct Edge {
  char letter;
  T* state;

  bool operator<(const Edge& other) const { return letter < other.letter; }

  bool operator==(const Edge& other) const { return letter == other.letter; }
};

struct NState;
struct Token;

struct NState {
  vector<Edge<NState>> letterTransition;
  vector<NState*> epsilonTransitions;

  s32 index;
  char stateSymbol;

  Token* token;
};

struct Token {
  NState* startingNState;
  NState* acceptingNState;

  s32 index;
  bool declared;
  bool emit;
  s32 priority;
  string name;
};

struct DState;

const s32 NStateFieldLen = 9;

typedef array<u64, NStateFieldLen> NStateBitField;

struct DState {
  NStateBitField nstatesField;
  unordered_map<int, DState*> transition;

  s32 index;
  Token* tokenEmission;
  vector<Token*> allTokens;
};

struct Statistic {
  s64 sum = 0;
  s64 min = 0;
  s64 max = 0;
  s64 numElement = 0;

  void add(s64 value);
  void report() const;
};

struct Scanner {
  unordered_map<string, Token*> tokenMap;

  vector<unique_ptr<Token>> tokens;
  vector<unique_ptr<NState>> nstates;
  vector<unique_ptr<DState>> dstates;

  vector<NStateBitField> epsilonClosureCache;
  multimap<u64, DState*> dstateMap;

  vector<Token*> silentTokens;

  Statistic ndfaStat;
  Statistic dfsStat;
};

EXPORT void scannerRegularLanguageToNFA(Scanner* scanner, const char* text);
EXPORT void scannerNFAtoDFA(Scanner* scanner);
EXPORT void scannerDumpDFA(const Scanner* scanner);
EXPORT void scannerLoadJoosRule(Scanner* scanner);
EXPORT ScanResult scannerProcessText(const Scanner* scanner, const char* text);
EXPORT void scannerDumpDebugInfo(const ScanResult& result, const char* baseOutputPath);

}  // namespace Scan
