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

	std::vector<std::shared_ptr<Modifier>> modifiers;
	std::shared_ptr<Type> returnType;
	std::shared_ptr<MethodDeclarator> declerator;

	std::string toCode() override { return "[MethodHeader]"; }
};

} //namespace AST
