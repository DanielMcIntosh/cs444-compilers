#pragma once

#include "ast/node.h"
#include "ast/modifier.h"
#include "ast/methodDeclarator.h"
#include <vector>
#include <memory>

namespace AST
{

class MethodHeader: public Node
{
public:
	static std::unique_ptr<MethodHeader> create(const Parse::Tree *ptNode);
	MethodHeader(const Parse::TMethodHeader *ptNode);

	std::vector<std::unique_ptr<Modifier>> modifiers;
	std::unique_ptr<Type> returnType;
	std::string id;
	std::vector<std::unique_ptr<VariableDeclaration>> parameterList;

	std::string toCode() override;
private:
	MethodHeader(std::vector<std::unique_ptr<Modifier>> mods, std::unique_ptr<Type> ret, MethodDeclarator&& declarator);
};

} //namespace AST
