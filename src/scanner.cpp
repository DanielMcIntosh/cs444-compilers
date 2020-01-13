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
  state->emit = false;
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
      curMajorToken->emit = true;
      continue;
    }

    if (!strcmp(token, "w")) { // build a chain of states from a word
      token = strtok(0, delim);

      NState * intermediateState = scannerCreateNState(scanner);
      curMajorToken->startingNState->epsilonTransitions.push_back(intermediateState);
      for (char c = *token; c; c = *++token) {
        NState *nextNState = scannerCreateNState(scanner);
        intermediateState->letterTransition.push_back({c, nextNState});
        intermediateState->stateSymbol = c;
        intermediateState = nextNState;
      }
      intermediateState->epsilonTransitions.push_back(curMajorToken->acceptingNState);

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

        NState *nextState = scannerCreateNState(scanner);
        if (!prevAcceptingState) {
          NState *ruleBeginState = scannerCreateNState(scanner);
          curMajorToken->startingNState->epsilonTransitions.push_back(ruleBeginState);
          prevAcceptingState = ruleBeginState;
        }

        prevAcceptingState->letterTransition.push_back({(char)value, nextState});
        prevAcceptingState = nextState;

        token = strtok(0, delim);
        continue;
      }

      string tokenS(token);
      Token *thisToken = scannerFindOrCreateToken(scanner, tokenS);
      if (!prevAcceptingState) { // beginning of a rule
        curMajorToken->startingNState->epsilonTransitions.push_back(thisToken->startingNState);
      } else { // concatenation
        prevAcceptingState->epsilonTransitions.push_back(thisToken->startingNState);
      }

      prevAcceptingState = thisToken->acceptingNState;
      token = strtok(0, delim);
    }

    prevAcceptingState->epsilonTransitions.push_back(curMajorToken->acceptingNState);
  }

  for (auto &nstate : scanner->nstates) {
    sort(nstate->letterTransition.begin(), nstate->letterTransition.end());
  }

  for (auto &statePair: scanner->tokenMap) {
    Token *token = statePair.second;
    ASSERT(token->declared);
    token->acceptingNState->emit = token->emit;
    token->acceptingNState->token = token;
  }
}

  vector<NState *> epsilonClosure(const vector<NState *> &base) {
    unordered_set<NState *> seen;
    vector<NState *> frontier;
    vector<NState *> result = base;

    for (NState *state: base) {
      seen.insert(state);
      frontier.push_back(state);
    }

    while (!frontier.empty()) {
      NState *state = frontier.back();
      frontier.pop_back();

      for (NState *epsilonNext: state->epsilonTransitions) {
        if (seen.count(epsilonNext))
          continue;

        seen.insert(epsilonNext);
        frontier.push_back(epsilonNext);
        result.push_back(epsilonNext);
      }
    }

    return result;
  }

  DState *scannerCreateDStateFromNState(Scanner *scanner,
                                        const vector<NState *> &nstates) {
    scanner->dstates.push_back(make_unique<DState>());

    DState *dstate = scanner->dstates.back().get();
    dstate->nstates = nstates;
    dstate->index = scanner->dstates.size() - 1;

    for (const NState* nstate: nstates) {
      if (nstate->emit) {
        dstate->tokenEmission.push_back(nstate->token->name);
      }
    }

    scanner->dstateMap.insert(make_pair(nstates.size(), dstate));
    
    return dstate;
  }

  DState *scannerFindDStateFromNStateFast(Scanner *scanner,
                                      const vector<NState *> &nstates) {
    auto itPair = scanner->dstateMap.equal_range(nstates.size());
    for (auto it = itPair.first; it != itPair.second; ++it) {
      DState *dstate = it->second;
      if (equal(dstate->nstates.begin(), dstate->nstates.end(),
                nstates.begin()))
        return dstate;
    }
    return 0;
  }

  void scannerNFAtoDFA(Scanner *scanner) {
    Token *goal = scanner->tokenMap["Goal"];
    
    vector<NState *> curNStates {goal->startingNState};
    curNStates = epsilonClosure(curNStates);
    sort(curNStates.begin(), curNStates.end());
    scannerCreateDStateFromNState(scanner, curNStates);

    for (size_t curDStateIndex = 0; curDStateIndex < scanner->dstates.size();
         ++curDStateIndex) {
      DState *curDState = scanner->dstates[curDStateIndex].get();
      for (s32 letter = 0; letter < NumLetters; ++letter) {
        vector<NState *> nextNStates;
        
        for (NState* nstate: curDState->nstates) {
          const vector<Edge<NState>> &transitionArray =
                  nstate->letterTransition;
          auto it = lower_bound(transitionArray.begin(), transitionArray.end(),
                                Edge<NState>{(char)letter, 0});
          if (it == transitionArray.end() || it->letter != letter)
            continue;

          nextNStates.push_back(it->state);
        }

        if (nextNStates.empty())
          continue;
        
        nextNStates = epsilonClosure(nextNStates);
        sort(nextNStates.begin(), nextNStates.end());
        DState *nextDState = scannerFindDStateFromNStateFast(scanner, nextNStates);
        if (!nextDState) {
          nextDState = scannerCreateDStateFromNState(scanner, nextNStates);
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
      /*
      for (const NState *nstate: dstate->nstates) {
        fprintf(file, "%d ", nstate->index);
      }
      */

      for (const string &tokenName: dstate->tokenEmission) {
        fprintf(file, "%s ", tokenName.c_str());
      }
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
  }

} // namespace Scan
