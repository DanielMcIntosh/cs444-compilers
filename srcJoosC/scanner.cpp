#include "scanner.h"

#include <stdio.h>
#include <string.h>

#include "platform.h"
#include "profiler.h"
#include "utility.h"

namespace Scan {

static NState* scannerCreateNState(Scanner* scanner) {
  scanner->nstates.push_back(make_unique<NState>());

  NState* state = scanner->nstates.back().get();
  state->index = scanner->nstates.size() - 1;
  state->stateSymbol = 0;
  state->token = nullptr;
  return state;
}

static void scannerCreateToken(Scanner* scanner, const string& tokenS) {
  ASSERT(!scanner->tokenMap.count(tokenS));

  scanner->tokens.push_back(make_unique<Token>());
  Token* token = scanner->tokens.back().get();

  token->startingNState = scannerCreateNState(scanner);
  token->acceptingNState = scannerCreateNState(scanner);
  token->index = scanner->tokenMap.size() - 1;
  token->declared = false;
  token->emit = false;
  token->priority = 0;
  token->name = tokenS;

  scanner->tokenMap[tokenS] = token;
}

static Token* scannerFindOrCreateToken(Scanner* scanner, const string& tokenS) {
  auto it = scanner->tokenMap.find(tokenS);
  if (it == scanner->tokenMap.end()) {
    scannerCreateToken(scanner, tokenS);
    it = scanner->tokenMap.find(tokenS);
  }
  return it->second;
}

void scannerRegularLanguageToNFA(Scanner* scanner, const char* text) {
  profileSection("reg to NFA");
  const char* textPtr = text;

  Token* curMajorToken = nullptr;
  while (*textPtr) {
    const char* newline = "\r\n";
    s32 lineLen = strcspn(textPtr, newline);

    char line[TWO_TO_EIGHT];
    snprintf(line, lineLen + 1, "%s", textPtr);
    line[lineLen] = '\0';
    textPtr += lineLen;
    textPtr += strspn(textPtr, newline);

    bool isDef = (*line != ' ');

    const char* delim = " \t";
    char* token = strtok(line, delim);
    if (!token)
      continue;

    s32 tokenLen = strlen(token);
    if (isDef) {  // token definition
      token[tokenLen - 1] = '\0';
      string tokenS(token);
      curMajorToken = scannerFindOrCreateToken(scanner, tokenS);
      curMajorToken->declared = true;
      continue;
    }

    if (!strcmp(token, "any")) {  // terminating letters
      token = strtok(nullptr, delim);
      for (char c = *token; c; c = *++token) {
        vector<Edge<NState>>* transitionArray =
            &curMajorToken->startingNState->letterTransition;
        transitionArray->push_back({c, curMajorToken->acceptingNState});
      }
      continue;
    }

    if (!strcmp(token, "inputchar")) {  // default input character with
      // exceptions
      token = strtok(nullptr, delim);  // exclude these characters
      for (s32 c = 1; c < NumLetters; ++c) {
        if (token && strchr(token, c))
          continue;
        if (c == 0xa || c == 0xd)  // not LF or CR
          continue;
        vector<Edge<NState>>* transitionArray =
            &curMajorToken->startingNState->letterTransition;
        transitionArray->push_back({(char)c, curMajorToken->acceptingNState});
      }

      continue;
    }

    if (!strcmp(token, "emit")) {  // accepting state
      token = strtok(nullptr, delim);
      curMajorToken->priority = atoi(token);
      curMajorToken->emit = true;
      continue;
    }

    if (!strcmp(token, "silent")) {  // an accepting state that doesn't emit
      // anything
      scanner->silentTokens.push_back(curMajorToken);
      continue;
    }

    if (!strcmp(token, "word")) {  // build a chain of states from a word
      token = strtok(nullptr, delim);
      s32 wordLen = strlen(token);

      NState* intermediateState = scannerCreateNState(scanner);
      curMajorToken->startingNState->epsilonTransitions.push_back(
          intermediateState);
      for (s32 i = 0; i < wordLen; ++i) {
        char c = token[i];
        NState* nextNState;
        if (i == wordLen - 1) {  // end of a Rule
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

    // a single Rule
    NState* prevAcceptingState = nullptr;
    while (token) {
      if (!strcmp(token, "char")) {  // single character follows
        token = strtok(nullptr, delim);
        s32 value = atoi(token);
        if (!value)
          value = token[0];

        token = strtok(nullptr, delim);
        NState* nextState;
        if (!token) {  // end of a Rule
          nextState = curMajorToken->acceptingNState;
        } else {
          nextState = scannerCreateNState(scanner);
        }

        if (!prevAcceptingState) {
          NState* ruleBeginState = scannerCreateNState(scanner);
          curMajorToken->startingNState->epsilonTransitions.push_back(
              ruleBeginState);
          prevAcceptingState = ruleBeginState;
        }

        prevAcceptingState->letterTransition.push_back(
            {(char)value, nextState});
        prevAcceptingState = nextState;
        continue;
      } else if (!strcmp(token, "copy")) {
        token = strtok(nullptr, delim);
        string tokenS(token);

        token = strtok(nullptr, delim);

        ASSERT(scanner->tokenMap.find(tokenS) !=
               scanner->tokenMap.end());  // must declare before use
        Token* toCopy = scanner->tokenMap[tokenS];
        ASSERT(toCopy->startingNState->epsilonTransitions
                   .empty());  // prune non trivial cases
        ASSERT(toCopy->acceptingNState->epsilonTransitions.empty());

        NState* n1 = scannerCreateNState(scanner);
        NState* n2 = scannerCreateNState(scanner);

        for (const Edge<NState>& edge :
             toCopy->startingNState->letterTransition) {
          ASSERT(edge.state ==
                 toCopy->acceptingNState);  // only support simple graph for now
          n1->letterTransition.push_back({edge.letter, n2});
        }

        if (!prevAcceptingState)
          prevAcceptingState = curMajorToken->startingNState;
        prevAcceptingState->epsilonTransitions.push_back(n1);
        if (!token)
          n2->epsilonTransitions.push_back(curMajorToken->acceptingNState);
        prevAcceptingState = n2;
      } else {
        string tokenS(token);
        token = strtok(nullptr, delim);

        Token* thisToken = scannerFindOrCreateToken(scanner, tokenS);
        if (!prevAcceptingState)
          prevAcceptingState = curMajorToken->startingNState;
        prevAcceptingState->epsilonTransitions.push_back(
            thisToken->startingNState);

        if (!token)  // end of a Rule
          thisToken->acceptingNState->epsilonTransitions.push_back(
              curMajorToken->acceptingNState);
        prevAcceptingState = thisToken->acceptingNState;
      }
    }
  }

  for (auto& nstate : scanner->nstates) {
    sort(nstate->letterTransition.begin(), nstate->letterTransition.end());
  }

  for (auto& statePair : scanner->tokenMap) {
    Token* token = statePair.second;
    ASSERT(token->declared);
    token->acceptingNState->token = token;
  }
}

template <size_t size>
void arrayBitFieldSet(array<u64, size>* arr, s32 position) {
  s32 index = position / 64;
  s32 internalPosition = 63 - position % 64;
  (*arr)[index] |= (1ULL << (u32)internalPosition);
}

template <size_t size>
void arrayBitFieldClear(array<u64, size>* arr, s32 position) {
  s32 index = position / 64;
  s32 internalPosition = 63 - position % 64;
  (*arr)[index] &= ~(1ULL << (u32)internalPosition);
}

template <size_t size>
bool arrayBitFieldIsSet(const array<u64, size>& arr, s32 position) {
  s32 index = position / 64;
  s32 internalPosition = 63 - position % 64;
  return arr[index] & (1ULL << (u32)internalPosition);
}

template <size_t size>
void arrayBitFieldUnion(array<u64, size>* a, const array<u64, size>& b) {
  for (size_t i = 0; i < size; ++i) {
    (*a)[i] |= b[i];
  }
}

template <size_t size>
struct arrayBitFieldIterator {
  array<u64, size> value;
  s32 state;
  s32 index;

  s32 operator*() const { return index; }

  void operator++() {
    while (state < (s32)size && !value[state]) {
      ++state;
    }
    if (state >= (s32)size) {
      index = -1;
      return;
    }
    s32 internalIndex = getLeadingZeros(value[state]);
    index = state * 64 + internalIndex;
    arrayBitFieldClear(&value, index);
  }
};

template <size_t size>
arrayBitFieldIterator<size> arrayBitFieldBegin(const array<u64, size>& array) {
  arrayBitFieldIterator<size> iterator;
  iterator.value = array;
  iterator.state = 0;
  iterator.index = 0;
  ++iterator;
  return iterator;
}

template <size_t size>
u64 arrayHash(const array<u64, size>& a) {
  u64 result = 0xcafebabebaadf00d;
  for (const u64 value : a) {
    result ^= std::hash<u64>()(value);
  }
  return result;
}

static void epsilonClosureFast(const NState* nstate, NStateBitField* bitfield) {
  NStateBitField seenField{0};

  arrayBitFieldSet(&seenField, nstate->index);

  vector<const NState*> frontier{nstate};

  while (!frontier.empty()) {
    const NState* theState = frontier.back();
    frontier.pop_back();

    for (NState* epsilonNext : theState->epsilonTransitions) {
      if (arrayBitFieldIsSet(seenField, epsilonNext->index))
        continue;

      arrayBitFieldSet(&seenField, epsilonNext->index);
      frontier.push_back(epsilonNext);
    }
  }

  *bitfield = seenField;
}

static DState* scannerCreateDStateFromNState(Scanner* scanner,
                                      const NStateBitField& nstates) {
  scanner->dstates.push_back(make_unique<DState>());

  DState* dstate = scanner->dstates.back().get();
  dstate->index = scanner->dstates.size() - 1;
  dstate->nstatesField = nstates;

  s32 curPriority = numeric_limits<s32>::max();
  Token* curToken = nullptr;
  for (auto it = arrayBitFieldBegin(nstates); *it != -1; ++it) {
    const NState* nstate = scanner->nstates[*it].get();
    if (nstate->token && nstate->token->emit)
      dstate->allTokens.push_back(nstate->token);
    if (nstate->token && nstate->token->emit &&
        nstate->token->priority < curPriority) {
      curToken = nstate->token;
      curPriority = curToken->priority;
    }
  }
  dstate->tokenEmission = curToken;

  u64 hashValue = arrayHash(nstates);
  scanner->dstateMap.insert(make_pair(hashValue, dstate));
  return dstate;
}

static DState* scannerFindDStateFromNState(Scanner* scanner,
                                    const NStateBitField& nstates) {
  u64 hashValue = arrayHash(nstates);
  auto itPair = scanner->dstateMap.equal_range(hashValue);
  s64 compares = 0;
  DState* state = nullptr;
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

void scannerNFAtoDFA(Scanner* scanner) {
  ASSERT(scanner->nstates.size() <= NStateFieldLen * 64);

  scanner->epsilonClosureCache =
      vector<NStateBitField>(scanner->nstates.size(), {0});
  for (size_t i = 0; i < scanner->nstates.size(); ++i) {
    epsilonClosureFast(scanner->nstates[i].get(),
                       &scanner->epsilonClosureCache[i]);
  }

  Token* goal = scanner->tokenMap["Goal"];

  NStateBitField curNStates =
      scanner->epsilonClosureCache[goal->startingNState->index];
  scannerCreateDStateFromNState(scanner, curNStates);

  for (size_t curDStateIndex = 0; curDStateIndex < scanner->dstates.size();
       ++curDStateIndex) {
    DState* curDState = scanner->dstates[curDStateIndex].get();
    for (s32 letter = 0; letter < NumLetters; ++letter) {
      NStateBitField nextNStates{0};
      curNStates = curDState->nstatesField;

      bool hasAny = false;
      for (auto val = arrayBitFieldBegin(curNStates); *val != -1; ++val) {
        const vector<Edge<NState>>& transitionArray =
            scanner->nstates[*val]->letterTransition;
        auto it = lower_bound(transitionArray.begin(), transitionArray.end(),
                              Edge<NState>{(char)letter, nullptr});
        if (it == transitionArray.end() || it->letter != letter)
          continue;

        arrayBitFieldUnion(&nextNStates,
                           scanner->epsilonClosureCache[it->state->index]);
        hasAny = true;
      }

      if (!hasAny)
        continue;

      DState* nextDState = scannerFindDStateFromNState(scanner, nextNStates);
      if (!nextDState) {
        nextDState = scannerCreateDStateFromNState(scanner, nextNStates);
      }

      curDState->transition[letter] = nextDState;
    }
  }
}

void scannerDumpDFA(const Scanner* scanner) {
  FILE* file = fopen("DFA.txt", "w");
  for (const auto& dstate : scanner->dstates) {
    vector<vector<bool>> transitionMap(scanner->dstates.size(),
                                       vector<bool>(NumLetters));
    // for (const Edge<DState> &edge : dstate->transition) {
    // transitionMap[edge.state->index][edge.letter] = true;
    //}

    fprintf(file, "\nState %d: ", dstate->index);
    // for (auto val = arrayBitFieldBegin(dstate->nstatesField); *val != -1;
    // ++val) fprintf(file, "%d ", *val);
    for (const Token* token : dstate->allTokens) {
      fprintf(file, "%s ", token->name.c_str());
    }
    if (dstate->tokenEmission)
      fprintf(file, "(%s)", dstate->tokenEmission->name.c_str());
    fprintf(file, "\n  ");

    for (size_t dstateIndex = 0; dstateIndex < transitionMap.size();
         ++dstateIndex) {
      const vector<bool>& bitmap = transitionMap[dstateIndex];
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
  fclose(file);
}

ScanResult scannerProcessText(const Scanner* scanner, const char* text) {
  profileSection("process text");
  DState* startState = scanner->dstates[0].get();
  ScanResult result;
  result.valid = false;
  result.errorPosition = -1;

  result.tokens.push_back({"BOF", "BOF"});

  DState* curState = startState;
  string curLexeme;
  const char* textPtr = text;
  for (char c = *textPtr;; c = *++textPtr) {
    auto it = curState->transition.find(c);
    bool isInvalid = it == curState->transition.end();
    Token* theToken = curState->tokenEmission;
    if (isInvalid) {  // invalid Transition
      bool doEmit = theToken && find(scanner->silentTokens.begin(),
                                     scanner->silentTokens.end(),
                                     theToken) == scanner->silentTokens.end();
      if (!theToken) {
        result.valid = false;
        result.errorPosition = textPtr - text;
        return result;
      }

      if (doEmit)
        result.tokens.push_back({theToken->name, curLexeme});

      textPtr--;
      curState = startState;
      curLexeme.clear();
    } else {
      curState = it->second;
      curLexeme.push_back(c);
    }

    if (false) {  // debug output
      strdecl32(theChar, "%c", c);
      if (c <= ' ')
        snprintf(theChar, 32, "\\x%x", c);

      const char* stateName =
          curState->tokenEmission ? curState->tokenEmission->name.c_str() : "-";
      strdecl256(step, "%s %s %d %c\r\n", theChar, stateName, curState->index,
                 isInvalid ? 'X' : 'V');
      result.detailedStep.append(string(step));
    }

    if (!c)
      break;
  }

  result.tokens.push_back({"EOF", "EOF"});
  result.valid = true;
  result.errorPosition = -1;
  return result;
}

void scannerLoadJoosRule(Scanner* scanner) {
  s32 fileSize;
  std::unique_ptr<char[]> fileContents = readEntireFile("joos.txt", &fileSize);
  if (!fileContents)
    return;
  scannerRegularLanguageToNFA(scanner, fileContents.get());
  scannerNFAtoDFA(scanner);
}

void scannerDumpDebugInfo(const ScanResult& result,
                          const char* baseOutputPath) {
  {  // scanner debug output
    strdecl512(scannerOutputPath, "%s.tokens.txt", baseOutputPath);
    FILE* scannerDump = fopen(scannerOutputPath, "w");
    s32 curLineLen = 0;
    s32 index = 0;
    for (const Scan::LexToken& token : result.tokens) {
      curLineLen += token.name.length();
      curLineLen += 2;
      curLineLen += 3;

      fprintf(scannerDump, "%s(%d, %2s) ", token.lexeme.c_str(), index,
              token.name.c_str());
      if (curLineLen > 70) {
        fprintf(scannerDump, "\r\n");
        curLineLen = 0;
      }
      ++index;
    }
    fclose(scannerDump);

    snprintf(scannerOutputPath, 512, "%s.scanner.txt", baseOutputPath);
    scannerDump = fopen(scannerOutputPath, "w");
    fwrite(result.detailedStep.c_str(), result.detailedStep.size(), 1,
           scannerDump);
    fclose(scannerDump);
  }
}

void Statistic::add(s64 value) {
	this->min = std::min(value, this->min);
	this->max = std::max(value, this->max);
	this->numElement++;
	this->sum += value;
}

void Statistic::report() const {
	LOGR("Data points %ld, min %ld, max %ld, avg %f", this->numElement,
	     this->min, this->max, (f64)sum / (f64)numElement);
}

}  // namespace Scan
