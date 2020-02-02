#include "grammar.h"
#include <string>
#include <vector>
#include <map>
#include <istream>
#include <fstream>
#include "utility.h"

namespace Parser {

void CFG::buildSymbolMap(std::istream& inStream)
{
	inStream >> nTerminals;
	for (int i = 0; i < nTerminals; ++i)
	{
		std::string symStr;
		inStream >> symStr;
		symbolMap[symStr] = i;
	}

	inStream >> nNonTerminals;
	// skip ~0 for now, we want to reserve that for the start symbol
	for (int i = 1; i < nNonTerminals; ++i)
	{
		std::string symStr;
		inStream >> symStr;
		symbolMap[symStr] = ~i; //-i - 1;
	}

	std::string temp;
	std::string startSymbol;
	// read the last non-terminal symbol (since we started at ~1, we haven't read it yet)
	inStream >> temp;
	inStream >> startSymbol;

	if (temp == startSymbol)
	{
		symbolMap[startSymbol] = ~0;
	}
	else
	{
		symbolMap[temp] = symbolMap[startSymbol];
		symbolMap[startSymbol] = ~0;
	}
}

Symbol CFG::readSymbol(std::istream& inStream)
{
	std::string symStr;
	inStream >> symStr;
	return symbolMap[symStr];
}

void CFG::buildRuleset(std::istream& inStream)
{
	int nRules;
	inStream >> nRules;
	rules.reserve(nRules);

	for (int i = 0; i < nRules; ++i)
	{
		NonTermSymbol lhs = readSymbol(inStream);
		inStream.get();
		std::vector<Symbol> rhs;
		while (inStream.peek() != '\n')
		{
			rhs.push_back(readSymbol(inStream));
		}
		rules.push_back(Rule{lhs, rhs});
	}
}

CFG::CFG(std::istream& inStream)
{
	buildSymbolMap(inStream);
	buildRuleset(inStream);
}

Grammar::Grammar(std::istream& inStream) : cfg(inStream)
{
	int nStates, nActions;
	inStream >> nStates;
	inStream >> nActions;

	//construct a default initialized 2d vector of size nStates by nSymbols
	actions.resize(nStates);
	for (auto &cur : actions)
	{
		cur.resize(cfg.nTerminals + cfg.nNonTerminals);
	}

	for (int i = 0; i < nActions; ++i)
	{
		State state;
		inStream >> state;

		Symbol sym = cfg.readSymbol(inStream);

		//TODO: move this part into an overload of >> for the Action class?
		std::string actType;
		inStream >> actType;
		if (actType == "shift")
		{
			State state2;
			inStream >> state2;
			actions[state][sym] = std::unique_ptr<Action>(new Action(state2, false));
		}
		else
		{
			ASSERT(actType == "reduce");
			int rule;
			inStream >> rule;
			actions[state][sym] = std::unique_ptr<Action>(new Action(rule, true));
		}
	}
}

Grammar readLR1File(const char *path)
{
	std::ifstream inStream(path);
	return Grammar(inStream);
}

} // namespace Parser
