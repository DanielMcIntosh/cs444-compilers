#pragma once

#include "ast/node.h"
#include <map>

namespace AST
{

class Modifier: public Node
{
public:
	Modifier(std::vector<Parser::ASTToken>& children);

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

};

} //namespace AST
