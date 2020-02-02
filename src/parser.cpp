#include "parser.h"
#include "grammar.h"
#include "astToken.h"

namespace Parser
{

void parseTokens(std::vector<Scan::LexToken> const &inputTokens, Grammar const& grammar)
{
	std::vector<State> stateStack;
	std::vector<ASTToken> tokenStack;
	stateStack.emplace_back(0);

	for (const auto& nextToken : inputTokens)
	{
		Symbol nextSymbol = grammar.cfg.symbolMap.at(nextToken.name);
		tokenStack.push_back(ASTToken(nextSymbol, nextToken.lexeme));
		// have to use a pointer instead of a reference because we would need to re-bind the reference in the for loop increment
		const std::unique_ptr<Action> *action = &(grammar.actions[stateStack.back()][tokenStack.back().sym]);
		for (; (*action) && (*action)->isReduction;
			action = &(grammar.actions[stateStack.back()][tokenStack.back().sym]))
		{
			CFG::Rule reduction = grammar.cfg.rules[(*action)->ruleNum];

			// generate the list of child tokens for constructing the next ASTToken
			std::vector<ASTToken> children;
			for (auto it = tokenStack.end() - reduction.rhs.size(); it != tokenStack.end(); it++)
			{
				children.push_back(std::move(*it));
			}

			// pop all the children from the token stack and
			// change our state back to what it was before we inserted any of the children
			for (uint i = 0; i < reduction.rhs.size(); ++i)
			{
				tokenStack.pop_back();
				stateStack.pop_back();
			}

			tokenStack.emplace_back(reduction.lhs, children);
		}

		if ((*action))
		{
			stateStack.push_back((*action)->outState);
		}
	}
}

} //namespace Parser
