#pragma once

#include "ast/expression.h"
#include "ast/name.h"
#include <memory>
#include <vector>
#include <string>
#include <variant>

namespace AST
{

class MethodInvocation: public Expression
{
public:
	MethodInvocation(std::vector<Parser::ASTToken>& children);

	// nullable
	std::shared_ptr<Expression> obj;
	//TODO: clean this up a bit, it doesn't really reflect the structure we care about
	std::variant<std::shared_ptr<Name>, std::string> identifier;
	std::vector<std::shared_ptr<Expression>> args;
};

} //namespace AST
