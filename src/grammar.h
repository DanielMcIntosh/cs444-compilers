#pragma once

#include <vector>
#include <map>
#include <istream>
#include <memory>

#include "scanParse.h"

namespace Parser {

using State = int;

struct Action
{
	Action(int val, bool reduction): isReduction(reduction), ruleNum(val) {}

	bool isReduction;
	union{
		State outState;
		int ruleNum;
	};
};


using Symbol = int;
using TermSymbol = int;
using NonTermSymbol = int;

// still not decided on this organization of a CFG and a Grammar
// might move stuff around later
struct CFG {
	CFG(std::istream& inStream);

	struct Rule {
		NonTermSymbol lhs;
		std::vector<Symbol> rhs;
	};

	void buildSymbolMap(std::istream& inStream);
	void buildRuleset(std::istream& inStream);
	Symbol readSymbol(std::istream& inStream);

	int nTerminals;
	int nNonTerminals;
	std::map<std::string, Symbol> symbolMap;
	std::vector<Rule> rules;
};

struct Grammar
{
	Grammar(std::istream& inStream);
	CFG cfg;
	// indexed by the state first, then symbol
	std::vector<std::vector<std::unique_ptr<Action>>> actions;
};

Grammar readLR1File(const char *path);

} // namespace Parser
