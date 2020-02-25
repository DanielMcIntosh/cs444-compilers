#pragma once

#include "ast/node.h"
#include <vector>
#include <memory>

namespace AST
{

class Type;
class Modifier;
class VariableDeclaration;
class MethodDeclarator;

class MethodHeader: public Node
{
public:
	static std::unique_ptr<MethodHeader> create(const Parse::Tree *ptNode);
	explicit MethodHeader(const Parse::TMethodHeader *ptNode);

	std::vector<std::unique_ptr<Modifier>> modifiers;
	std::unique_ptr<Type> returnType;
	std::string id;
	std::vector<std::unique_ptr<VariableDeclaration>> parameterList;

	std::string toCode() const override;
private:
	MethodHeader(std::vector<std::unique_ptr<Modifier>> mods, std::unique_ptr<Type> ret, MethodDeclarator&& declarator);
};

} //namespace AST
