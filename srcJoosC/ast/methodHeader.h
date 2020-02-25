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

class EXPORT MethodHeader: public Node
{
public:

	EXPORT static std::unique_ptr<MethodHeader> create(const Parse::Tree *ptNode);
	EXPORT explicit MethodHeader(const Parse::TMethodHeader *ptNode);
	EXPORT std::string toCode() const override;
protected:
	std::vector<std::unique_ptr<Modifier>> modifiers;
	std::unique_ptr<Type> returnType;
	std::string id;
	std::vector<std::unique_ptr<VariableDeclaration>> parameterList;
	friend class MethodDeclaration;
private:
	EXPORT MethodHeader(std::vector<std::unique_ptr<Modifier>> mods, std::unique_ptr<Type> ret, MethodDeclarator&& declarator);
};

} //namespace AST
