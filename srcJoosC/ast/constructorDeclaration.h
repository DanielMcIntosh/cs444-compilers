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
	static std::unique_ptr<ConstructorDeclaration> create(const Parse::Tree *ptNode);
	ConstructorDeclaration(const Parse::TConstructorDeclaration *ptNode);

	std::vector<std::unique_ptr<VariableDeclaration>> parameters;
	std::unique_ptr<Block> body;

	std::string toCode() override { return "[ConstructorDeclaration]"; }
};

} //namespace AST
