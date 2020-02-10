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
	static std::unique_ptr<MethodInvocation> create(const Parse::Tree *ptNode);
	MethodInvocation(const Parse::TMethodInvocation *ptNode);

	// nullable
	std::shared_ptr<Expression> obj;
	//TODO: clean this up a bit, it doesn't really reflect the structure we care about
	std::variant<std::shared_ptr<Name>, std::string> identifier;
	std::vector<std::shared_ptr<Expression>> args;

	std::string toCode() override { return "[MethodInvocation]"; }
};

} //namespace AST
