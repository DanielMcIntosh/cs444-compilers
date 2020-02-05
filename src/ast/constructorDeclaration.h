#pragma once

#include <ast/memberDeclaration.h>
//#include <ast/formalParameter.h>
#include <ast/block.h>
#include <memory>

namespace AST
{

class ConstructorDeclaration: public MemberDeclaration
{
public:
	ConstructorDeclaration(std::vector<Parser::ASTToken>& children);

	//std::vector<std::shared_ptr<FormalParameter>> parameters;
	std::shared_ptr<Block> body;
};

} //namespace AST
