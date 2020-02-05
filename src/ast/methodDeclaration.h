#pragma once

#include <ast/memberDeclaration.h>
//#include <ast/methodHeader.h>
#include <ast/statement.h>
#include <memory>

namespace AST
{

class MethodDeclaration: public MemberDeclaration
{
public:
	MethodDeclaration(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Type> returnType;
	//std::vector<std::shared_ptr<FormalParameter>> parameters;
	// nullable
	std::shared_ptr<Block> body;
};

} //namespace AST
