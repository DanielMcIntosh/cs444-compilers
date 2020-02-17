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
	explicit MethodInvocation(const Parse::TMethodInvocation *ptNode);

	//TODO: clean this up a bit, not sure if it really reflects the structure we care about
	// nullable
	std::unique_ptr<Expression> obj;
	std::variant<std::unique_ptr<Name>, std::string> identifier;
	std::vector<std::unique_ptr<Expression>> args;

	std::string toCode() override;
};

} //namespace AST
