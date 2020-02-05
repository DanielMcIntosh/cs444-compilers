#pragma once

#include "ast/expression.h"
#include "ast/type.h"
#include <memory>
#include <string>

namespace AST
{

class VariableDeclaration: public Expression
{
public:
	VariableDeclaration(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Type> type;
	std::string identifier;
	// nullable
	std::shared_ptr<Expression> initializer;
};

} //namespace AST
