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
	explicit Name(const Parse::TName *ptNode);
	Name() = default;

	std::vector<std::string> prefix;
	std::string id;

	std::string toCode() override;
};

class NameType: public Type
{
public:
	std::vector<std::string> prefix;
	std::string id;

	explicit NameType(Name&& other);

	std::string toCode() override;
};

class NameExpression: public Expression
{
public:
	std::vector<std::string> prefix;
	std::string id;

	explicit NameExpression(Name&& other);

	std::string toCode() override;
};

} //namespace AST
