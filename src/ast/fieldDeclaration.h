#pragma once

#include <ast/memberDeclaration.h>
#include <ast/type.h>
#include <ast/modifier.h>
#include <memory>

namespace AST
{

class FieldDeclaration: public MemberDeclaration
{
public:
	FieldDeclaration(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Type> type;
	// nullable
	std::shared_ptr<Expression> initializer;
};

} //namespace AST
