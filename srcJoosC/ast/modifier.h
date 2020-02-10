#pragma once

#include "ast/node.h"
#include <map>

namespace AST
{

class Modifier: public Node
{
public:
	static std::unique_ptr<Modifier> create(const Parse::Tree *ptNode);
	Modifier(const Parse::TModifier *ptNode);

	enum class Value
	{
		Public,
		Protected,
		Static,
		Abstract,
		Final,
		Native,
	};

	Value modType;

	static const std::map<std::string, Value> modTypeLookup;

	std::string toCode() override { return "[Modifier]"; }
};

} //namespace AST
