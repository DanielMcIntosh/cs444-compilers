#pragma once

#include "ast/memberDeclaration.h"
#include "ast/variableDeclaration.h"
#include "ast/block.h"
#include <memory>

namespace AST
{

class ConstructorDeclaration: public MemberDeclaration
{
public:
	ConstructorDeclaration(std::vector<Parser::ASTToken>& children);

<<<<<<< HEAD
	//std::vector<std::shared_ptr<FormalParameter>> parameters;
=======
	std::vector<std::shared_ptr<FormalParameter>> parameters;
>>>>>>> added AST classes
	std::shared_ptr<Block> body;
};

} //namespace AST
