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
	static std::unique_ptr<VariableDeclaration> create(const Parse::Tree *ptNode);
	VariableDeclaration(const Parse::TFormalParameter *ptNode);
	VariableDeclaration(const Parse::TLocalVariableDeclaration *ptNode);

	std::shared_ptr<Type> type;
	std::string identifier;
	// nullable
	std::shared_ptr<Expression> initializer;

	std::string toCode() override { return "[VariableDeclaration]"; }
};

} //namespace AST
