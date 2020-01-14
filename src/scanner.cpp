#include <stdio.h>
#include <string.h>

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#include "utility.h"
#include "scanner.h"

namespace Scan {

NState *scannerCreateNState(Scanner *scanner) {
  scanner->nstates.push_back(make_unique<NState>());

  NState *state = scanner->nstates.back().get();
  state->index = scanner->nstates.size() - 1;
  state->stateSymbol = 0;
  state->token = 0;
  return state;
}

void scannerCreateToken(Scanner *scanner, const string &tokenS) {
  ASSERT(!scanner->tokenMap.count(tokenS));

  scanner->tokens.push_back(make_unique<Token>());
  Token *token = scanner->tokens.back().get();

  token->startingNState = scannerCreateNState(scanner);
  token->acceptingNState = scannerCreateNState(scanner);
  token->index = scanner->tokenMap.size() - 1;
  token->declared = false;
  token->emit = false;
  token->priority = 0;
  token->name = tokenS;

  scanner->tokenMap[tokenS] = token;
}

Token *scannerFindOrCreateToken(Scanner *scanner, const string &tokenS) {
  auto it = scanner->tokenMap.find(tokenS);
  if (it == scanner->tokenMap.end()) {
    scannerCreateToken(scanner, tokenS);
    it = scanner->tokenMap.find(tokenS);
  }
  return it->second;
}

void scannerRegularLanguageToNFA(Scanner *scanner, const char *text) {
  const char *textPtr = text;

  Token *curMajorToken = 0;
  while (*textPtr) {
    const char *newline = "\r\n";
    s32 lineLen = strcspn(textPtr, newline);

    char line[TWO_TO_EIGHT];
    snprintf(line, lineLen + 1, "%s", textPtr);
    line[lineLen] = 0;
    textPtr += lineLen;
    textPtr += strspn(textPtr, newline);

    bool isDef = (*line != ' ');

    const char *delim = " \t";
    char *token = strtok(line, delim);
    if (!token)
      continue;

    s32 tokenLen = strlen(token);
    if (isDef) { // token definition
      token[tokenLen - 1] = 0;
      string tokenS(token);
      curMajorToken = scannerFindOrCreateToken(scanner, tokenS);
      curMajorToken->declared = true;
      continue;
    }

    if (!strcmp(token, "v")) { // terminating letters
      token = strtok(0, delim);
      for (char c = *token; c; c = *++token) {
        vector<Edge<NState>> *transitionArray =
                &curMajorToken->startingNState->letterTransition;
        transitionArray->push_back({c, curMajorToken->acceptingNState});
      }
      continue;
    }

    if (!strcmp(token, "e")) { // actually emit a token
      token = strtok(0, delim);
      curMajorToken->priority = atoi(token);
      curMajorToken->emit = true;
      continue;
    }

    if (!strcmp(token, "w")) { // build a chain of states from a word
      token = strtok(0, delim);
      s32 wordLen = strlen(token);

      NState * intermediateState = scannerCreateNState(scanner);
      curMajorToken->startingNState->epsilonTransitions.push_back(intermediateState);
      for (s32 i = 0; i < wordLen; ++i) {
        char c = token[i];
        NState *nextNState;
        if (i == wordLen - 1) { // end of a rule
          nextNState = curMajorToken->acceptingNState;
        } else {
          nextNState = scannerCreateNState(scanner);
        }
        intermediateState->letterTransition.push_back({c, nextNState});
        intermediateState->stateSymbol = c;
        intermediateState = nextNState;
      }

      continue;
    }

    // a single rule
    NState *prevAcceptingState = 0;
    while (token) {
      if (!strcmp(token, "c")) { // single character follows
        token = strtok(0, delim);
        s32 value = atoi(token);
        if (!value)
          value = token[0];

        token = strtok(0, delim);
        NState *nextState;
        if (!token) { // end of a rule
          nextState = curMajorToken->acceptingNState;
        } else {
          nextState = scannerCreateNState(scanner);
        }

        if (!prevAcceptingState) {
          NState *ruleBeginState = scannerCreateNState(scanner);
          curMajorToken->startingNState->epsilonTransitions.push_back(ruleBeginState);
          prevAcceptingState = ruleBeginState;
        }

        prevAcceptingState->letterTransition.push_back({(char)value, nextState});
        prevAcceptingState = nextState;
        continue;
      }

      string tokenS(token);
      token = strtok(0, delim);

      Token *thisToken = scannerFindOrCreateToken(scanner, tokenS);
      if (!prevAcceptingState) { // beginning of a rule
        curMajorToken->startingNState->epsilonTransitions.push_back(thisToken->startingNState);
      } else { // concatenation
        prevAcceptingState->epsilonTransitions.push_back(thisToken->startingNState);
      }

      if (!token) // end of a rule
        thisToken->acceptingNState->epsilonTransitions.push_back
                (curMajorToken->acceptingNState);
      prevAcceptingState = thisToken->acceptingNState;
    }
  }

  for (auto &nstate : scanner->nstates) {
    sort(nstate->letterTransition.begin(), nstate->letterTransition.end());
  }

  for (auto &statePair: scanner->tokenMap) {
    Token *token = statePair.second;
    ASSERT(token->declared);
    token->acceptingNState->token = token;
  }
}

template<size_t size>
void arrayBitFieldSet(array<u64, size> *arr, s32 position) {
  s32 index = position / 64;
  s32 internalPosition = 63 - position % 64;
  (*arr)[index] |= (1ULL << (u32)internalPosition);
}

template<size_t size>
void arrayBitFieldClear(array<u64, size> *arr, s32 position) {
  s32 index = position / 64;
  s32 internalPosition = 63 - position % 64;
  (*arr)[index] &= ~(1ULL << (u32)internalPosition);
}

template<size_t size>
bool arrayBitFieldIsSet(const array<u64, size> &arr, s32 position) {
  s32 index = position / 64;
  s32 internalPosition = 63 - position % 64;
  return arr[index] & (1ULL << (u32)internalPosition);
}

template<size_t size>
void arrayBitFieldUnion(array<u64, size> *a, const array<u64, size> &b) {
  for (size_t i = 0; i < size; ++i) {
    (*a)[i] |= b[i];
  }
}

template<size_t size>
s32 arrayBitFieldNextNonZeroIndexWithClear(array<u64, size> *a, s32 *state) {
  s32 result = -1;
  while (*state < (s32)size && !(*a)[*state]) {
    ++*state;
  }
  if (*state >= (s32)size)
    return result;
  s32 internalIndex = __builtin_clzll((*a)[*state]);
  result = *state * 64 + internalIndex;
  arrayBitFieldClear(a, result);
  return result;
}

template<size_t size>
u64 arrayHash(const array<u64, size> &a) {
  u64 result = 0xcafebabebaadf00d;
  for (const u64 value: a) {
    result ^= std::hash<u64>()(value);
  }
  return result;
}

void arrayBitFieldTest() {
  NStateBitField bitfield{0};

  u64 sum = 0;
  for (s32 i = 0; i < NStateFieldLen * 64; ++i) {
    arrayBitFieldSet(&bitfield, i);
  }
  bitfield[2] = 0;
  bitfield[3] = 0;
  bitfield[7] = 0;

  s32 state = 0;
  for (s32 val = arrayBitFieldNextNonZeroIndexWithClear(&bitfield, &state);
       state < NStateFieldLen; val = arrayBitFieldNextNonZeroIndexWithClear(
          &bitfield, &state)) {
    LOGR("%d", val);
  }
}

void epsilonClosureFast(const NState *nstate, NStateBitField* bitfield) {
  NStateBitField seenField{0};

  arrayBitFieldSet(&seenField, nstate->index);

  vector<const NState *> frontier{nstate};

  while (!frontier.empty()) {
    const NState *theState = frontier.back();
    frontier.pop_back();

    for (NState *epsilonNext: theState->epsilonTransitions) {
      if (arrayBitFieldIsSet(seenField, epsilonNext->index))
        continue;

      arrayBitFieldSet(&seenField, epsilonNext->index);
      frontier.push_back(epsilonNext);
    }
  }

  *bitfield = seenField;
}

DState *scannerCreateDStateFromNState(Scanner *scanner,
                                      const NStateBitField &nstates) {
  scanner->dstates.push_back(make_unique<DState>());

  DState *dstate = scanner->dstates.back().get();
  dstate->index = scanner->dstates.size() - 1;
  dstate->nstatesField = nstates;

  u64 hashValue = arrayHash(nstates);
  scanner->dstateMap.insert(make_pair(hashValue, dstate));
  return dstate;
}

DState *scannerFindDStateFromNState(Scanner *scanner, const NStateBitField &nstates) {
  u64 hashValue = arrayHash(nstates);
  auto itPair = scanner->dstateMap.equal_range(hashValue);
  s64 compares = 0;
  DState *state = 0;
  for (auto it = itPair.first; it != itPair.second; ++it) {
    ++compares;
    if (it->second->nstatesField == nstates) {
      state = it->second;
      break;
    }
  }
  scanner->ndfaStat.add(compares);
  return state;
}

void scannerNFAtoDFA(Scanner *scanner) {
  ASSERT(scanner->nstates.size() <= NStateFieldLen * 64);

  scanner->epsilonClosureCache = vector<NStateBitField>(scanner->nstates.size(), {0});
  for (size_t i = 0; i < scanner->nstates.size(); ++i) {
    epsilonClosureFast(scanner->nstates[i].get(), &scanner->epsilonClosureCache[i]);
  }

  Token *goal = scanner->tokenMap["Goal"];

  NStateBitField curNStates = scanner->epsilonClosureCache[goal->startingNState->index];
  scannerCreateDStateFromNState(scanner, curNStates);

  for (size_t curDStateIndex = 0; curDStateIndex < scanner->dstates.size();
       ++curDStateIndex) {
    DState *curDState = scanner->dstates[curDStateIndex].get();
    for (s32 letter = 0; letter < NumLetters; ++letter) {
      NStateBitField nextNStates{0};
      curNStates = curDState->nstatesField;

      bool hasAny = false;
      s32 state = 0;
      vector<Token *>tokenEmission;
      for (s32 nstateIndex = arrayBitFieldNextNonZeroIndexWithClear(&curNStates, &state);
           state < NStateFieldLen;
           nstateIndex = arrayBitFieldNextNonZeroIndexWithClear(&curNStates, &state)) {
        const vector<Edge<NState>> &transitionArray =
                scanner->nstates[nstateIndex]->letterTransition;
        auto it = lower_bound(transitionArray.begin(), transitionArray.end(),
                              Edge<NState>{(char)letter, 0});
        if (it == transitionArray.end() || it->letter != letter)
          continue;

        NState *nextNState = it->state;
        if (nextNState->token && nextNState->token->emit) {
          tokenEmission.push_back(nextNState->token);
        }
        arrayBitFieldUnion(&nextNStates, scanner->epsilonClosureCache[nextNState->index]);
        hasAny = true;
      }

      if (!hasAny)
        continue;

      DState *nextDState = scannerFindDStateFromNState(scanner, nextNStates);
      if (!nextDState) {
        nextDState = scannerCreateDStateFromNState(scanner, nextNStates);
        nextDState->tokenEmission = tokenEmission;
      }

      curDState->transition.push_back({(char)letter, nextDState});
    }
  }
}

void scannerDumpDFA(const Scanner *scanner) {
  FILE *file;
  if (scanner->dstates.size() > 100)
    file = fopen("dfa.txt", "w");
  else
    file = stderr;

  for (const auto &dstate : scanner->dstates) {
    vector<vector<bool>> transitionMap(scanner->dstates.size(),
                                       vector<bool>(NumLetters));
    for (const Edge<DState> &edge : dstate->transition) {
      transitionMap[edge.state->index][edge.letter] = true;
    }

    fprintf(file, "\nState %d: ", dstate->index);
    for (const Token *token: dstate->tokenEmission)
      fprintf(file, "%s ", token->name.c_str());
    fprintf(file, "\n  ");

    for (size_t dstateIndex = 0; dstateIndex < transitionMap.size();
         ++dstateIndex) {
      const vector<bool> &bitmap = transitionMap[dstateIndex];
      bool hasAny = false;
      for (s32 j = 0; j < NumLetters; ++j) {
        if (bitmap[j]) {
          hasAny = true;
          if (j <= ' ') {
            fprintf(file, "\\x%x", j);
          } else {
            fputc(j, file);
          }
        }
      }
      if (hasAny)
        fprintf(file, " -> %ld\n  ", dstateIndex);
    }
  }

  scanner->ndfaStat.report();
  scanner->dfsStat.report();
}

ScanResult scannerProcessFile(const Scanner *scanner, const char *text) {
  DState *startState = scanner->dstates[0].get();
  ScanResult result;

  DState *curState = startState;
  string curLexeme;
  const char *textPtr = text;
  for (char c = *textPtr; c; c = *++textPtr) {
    const vector<Edge<DState>> &transitionArray = curState->transition;
    auto it = lower_bound(transitionArray.begin(), transitionArray.end(),
            Edge<DState>{c, 0});
    if (it == transitionArray.end() || it->letter != c) { // invalid transition
      result.valid = false;
      result.errorPosition = textPtr - text;
      goto out;
    }

    DState *nextState = it->state;
    curState = nextState;
/*
    if (!curState->tokenEmission)
      fprintf(stdout, "%c ---\n", c);
    else
      fprintf(stdout, "%c %s\n", c, curState->tokenEmission->name.c_str());
*/
  }
  result.valid = true;
  result.errorPosition = -1;

  out:
  return result;
}

void scannerLoadJoosRule(Scanner *scanner) {
  char *fileContents;
  s32 fileSize;
  readEntireFile("lex.txt", &fileContents, &fileSize);
  if (!fileContents)
    return;
  scannerRegularLanguageToNFA(scanner, fileContents);
  scannerNFAtoDFA(scanner);
  free(fileContents);
}

} // namespace Scan
