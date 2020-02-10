#pragma once

#include "ast/expression.h"
#include "ast/type.h"
#include <memory>
#include <vector>
#include <string>

namespace AST
{

class Name: public Node
{
public:
	static std::unique_ptr<Name> create(const Parse::Tree *ptNode);
	Name(const Parse::TName *ptNode);

	std::vector<std::string> prefix;
	std::string id;

	std::string toCode() override { return "[Name]"; }
};

class NameType: public Type
{
public:
	std::vector<std::string> prefix;
	std::string id;

	NameType(Name&& other);

	std::string toCode() override { return "[NameType]"; }
};

class NameExpression: public Expression
{
public:
	std::vector<std::string> prefix;
	std::string id;

	NameExpression(Name&& other);

	std::string toCode() override { return "[NameExpression]"; }
};

} //namespace AST
