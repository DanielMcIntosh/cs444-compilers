#include <stdio.h>
#include <string.h>

#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "utility.h"
#include "scanner.h"

namespace Scan {

void scannerCreateToken(Scanner *scanner, const string &tokenS) {
  ASSERT(!scanner->tokenMap.count(tokenS));
  Token *token = new Token;
  NState *start = new NState, *accept = new NState;

  start->index = scanner->nstates.size();  
  accept->index = scanner->nstates.size();

  token->startingNState = start;
  token->acceptingNState = accept;
  token->index = scanner->tokenMap.size();
  
  scanner->tokens.push_back(token);
  scanner->nstates.push_back(start);
  scanner->nstates.push_back(accept);
  
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

void scannerRules(Scanner *scanner, const char *text) {
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

    const char *delim = " ";
    char *token = strtok(line, delim);
    s32 tokenLen = strlen(token);
    if (isDef) { // token definition
      token[tokenLen - 1] = 0;
      string tokenS(token);
      curMajorToken = scannerFindOrCreateToken(scanner, tokenS);
      continue;
    }

    if (!strcmp(token, "v")) { // terminating letters
      token = strtok(0, delim);
      for (char s = *token; s; s = *++token) {
        auto &transitionArray = curMajorToken->startingNState->letterTransition;
        transitionArray.push_back({s, curMajorToken->acceptingNState});
      }
      continue;
    }

    // list of rules
    Token *rulePrevToken = 0;    
    while (token) {
      string tokenS(token);
      Token *thisToken = scannerFindOrCreateToken(scanner, tokenS);
      if (!rulePrevToken) { // beginning of a rule
        curMajorToken->startingNState->epsilonTransitions.push_back(thisToken->startingNState);
      } else { // concatenation
        rulePrevToken->acceptingNState->epsilonTransitions.push_back(thisToken->startingNState);
      }

      rulePrevToken = thisToken;
      token = strtok(0, delim);
    }

    rulePrevToken->acceptingNState->epsilonTransitions.push_back(curMajorToken->acceptingNState);
  }

  for (NState *nstate : scanner->nstates) {
    sort(nstate->letterTransition.begin(), nstate->letterTransition.end());
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
    DState *dstate = new DState;
    dstate->nstates = nstates;
    dstate->index = scanner->dstates.size();
    scanner->dstates.push_back(dstate);
    return dstate;
  }

  DState *scannerFindDStateFromNState(Scanner *scanner,
                                      const vector<NState *> &nstates) {
    for (DState *dstate: scanner->dstates) {
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
    sort(curNStates.begin(), curNStates.end(), greater<void *>());
    scannerCreateDStateFromNState(scanner, curNStates);

    for (size_t curDStateIndex = 0; curDStateIndex < scanner->dstates.size();
         ++curDStateIndex) {
      DState *curDState = scanner->dstates[curDStateIndex];      
      for (s32 letter = 0; letter < NumLetters; ++letter) {
        vector<NState *> nextNStates;
        
        for (NState* nstate: curDState->nstates) {
          auto &transitionArray = nstate->letterTransition;
          auto it = lower_bound(transitionArray.begin(), transitionArray.end(), Edge<NState>{letter, 0});
          if (it == transitionArray.end() || it->letter != letter)
            continue;

          nextNStates.push_back(nstate);
        }

        if (nextNStates.empty())
          continue;
        
        nextNStates = epsilonClosure(nextNStates);
        sort(nextNStates.begin(), nextNStates.end(), greater<void *>());
        DState *nextDState = scannerFindDStateFromNState(scanner, nextNStates);
        if (!nextDState) {
          nextDState = scannerCreateDStateFromNState(scanner, nextNStates);
        }

        curDState->transition.push_back({letter, nextDState});        
      }
    }    
  }

  void scannerDumpDFA(const Scanner *scanner) {
    for (const DState *dstate : scanner->dstates) {
      vector<vector<bool>> transitionMap(scanner->dstates.size(),
                                         vector<bool>(NumLetters));
      for (const Edge<DState> &edge : dstate->transition) {        
        transitionMap[edge.state->index][edge.letter] = true;
      }

      LOGR("State %d: \n  ", dstate->index);

      for (size_t dstateIndex = 0; dstateIndex < transitionMap.size();
           ++dstateIndex) {
        const vector<bool> &bitmap = transitionMap[dstateIndex];
        bool hasAny = false;
        for (s32 j = 0; j < NumLetters; ++j) {
          if (bitmap[j]) {
            hasAny = true;
            fputc(j, stderr);
          }
        }
        if (hasAny)
          fprintf(stderr, " : %ld\n  ", dstateIndex);
      }
    }
  }

} // namespace Scan
