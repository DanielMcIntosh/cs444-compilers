#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <array>
#include <unordered_map>
#include <memory>

#include "utility.h"
#include "scanParse.h"

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

	Token *token;
};

struct Token {
	NState *startingNState;
	NState *acceptingNState;

	s32 index;
	bool declared;
	bool emit;
	s32 priority;
	string name;
};

struct DState;

const s32 NStateFieldLen = 16;

typedef array<u64, NStateFieldLen> NStateBitField;

struct DState {
	NStateBitField nstatesField;
	vector<Edge<DState>> transition;

	s32 index;
	Token *tokenEmission;
	vector<Token *> allTokens;
};

struct Statistic {
	s64 sum = 0;
	s64 min = 0;
	s64 max = 0;
	s64 numElement = 0;

	void add(s64 value) {
		this->min = std::min(value, this->min);
		this->max = std::max(value, this->max);
		this->numElement++;
		this->sum += value;
	}

	void report() const {
		LOGR("Data points %ld, min %ld, max %ld, avg %f",
				 this->numElement, this->min, this->max, (f64)sum/(f64)numElement);
	}
};

struct Scanner {
	unordered_map<string, Token *> tokenMap;

	vector<unique_ptr<Token>> tokens;
	vector<unique_ptr<NState>> nstates;
	vector<unique_ptr<DState>> dstates;

	vector<NStateBitField> epsilonClosureCache;
	multimap<u64, DState *> dstateMap;

	vector<Token *> silentTokens;

	Statistic ndfaStat;
	Statistic dfsStat;
};

void scannerRegularLanguageToNFA(Scanner *scanner, const char *text);
void scannerNFAtoDFA(Scanner *scanner);
void scannerDumpDFA(const Scanner *scanner);
void scannerLoadJoosRule(Scanner *scanner);
void scannerTest();
ScanResult scannerProcessText(const Scanner *scanner, const char *text);

} // namespace Scan
