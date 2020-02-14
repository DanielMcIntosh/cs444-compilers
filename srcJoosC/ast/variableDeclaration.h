#pragma once

#include "ast/expression.h"
#include "ast/type.h"
#include <memory>
#include <string>

namespace AST
{

class VariableDeclaration: public Node
{
public:
	static std::unique_ptr<VariableDeclaration> create(const Parse::Tree *ptNode);
	explicit VariableDeclaration(const Parse::TFormalParameter *ptNode);
	explicit VariableDeclaration(const Parse::TLocalVariableDeclaration *ptNode);

	std::unique_ptr<Type> type;
	std::string identifier;
	// nullable
	std::unique_ptr<Expression> initializer;

	std::string toCode() override;
};

} //namespace AST
