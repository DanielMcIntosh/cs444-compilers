#pragma once

#include "ast/memberDeclaration.h"
#include "ast/type.h"
#include "ast/variableDeclaration.h"
#include "ast/block.h"
#include <memory>

namespace AST
{

class MethodDeclaration: public MemberDeclaration
{
public:
	MethodDeclaration(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Type> returnType;
	std::vector<std::shared_ptr<VariableDeclaration>> parameters;
	// nullable
	std::shared_ptr<Block> body;
};

} //namespace AST
