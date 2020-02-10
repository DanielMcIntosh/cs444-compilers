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
	static std::unique_ptr<MethodDeclaration> create(const Parse::Tree *ptNode);
	MethodDeclaration(const Parse::TMethodDeclaration *ptNode);
	MethodDeclaration(const Parse::TAbstractMethodDeclaration *ptNode);

	std::shared_ptr<Type> returnType;
	std::vector<std::shared_ptr<VariableDeclaration>> parameters;
	// nullable
	std::shared_ptr<Block> body;

	std::string toCode() override { return "[MethodDeclaration]"; }
};

} //namespace AST
