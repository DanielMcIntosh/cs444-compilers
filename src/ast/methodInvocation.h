#pragma once

#include "ast/primary.h"
#include "ast/name.h"
#include "ast/expression.h"
#include <memory>
#include <vector>
#include <string>
#include <variant>

namespace AST
{

class MethodInvocation: public Primary
{
public:
	MethodInvocation(std::vector<Parser::ASTToken>& children);

	// nullable
	std::shared_ptr<Primary> obj;
	//TODO: clean this up a bit, it doesn't really reflect the structure we care about
	std::variant<std::shared_ptr<Name>, std::string> identifier;
	std::vector<std::shared_ptr<Expression>> args;
};

} //namespace AST
