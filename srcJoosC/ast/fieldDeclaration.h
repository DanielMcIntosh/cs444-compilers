#pragma once

#include "ast/memberDeclaration.h"
#include "ast/type.h"
#include "ast/expression.h"
#include <memory>

namespace AST
{

class FieldDeclaration: public MemberDeclaration
{
public:
	static std::unique_ptr<FieldDeclaration> create(const Parse::Tree *ptNode);
	FieldDeclaration(const Parse::TFieldDeclaration *ptNode);

	std::shared_ptr<Type> type;
	// nullable
	std::shared_ptr<Expression> initializer;

	std::string toCode() override { return "[FieldDeclaration]"; }
};

} //namespace AST
