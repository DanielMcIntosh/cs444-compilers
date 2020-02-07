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
	Name(std::vector<Parser::ASTToken>& children);
	// TODO: define NameExpression class, which inherits from Expression?
	operator Expression();
	// TODO: define NameType class, which inherits from Type?
	operator Type();

	std::vector<std::string> prefix;
	std::string id;
};

} //namespace AST
