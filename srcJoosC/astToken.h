#pragma once

#include "grammar.h"
//#include "ast/node.h"

namespace Parser {

struct ASTToken
{
	// create a new AST node by reducing using the rule s -> [children]
	ASTToken(Symbol s, std::vector<ASTToken>& children);
	ASTToken(TermSymbol s, std::string lexeme);

	Symbol sym;
//	std::shared_ptr<AST::Node> astNode;
};

} //namespace Parser
