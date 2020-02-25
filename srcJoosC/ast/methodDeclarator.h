#pragma once

#include "ast/node.h"
#include <vector>
#include <memory>
#include <string>

namespace AST
{

class VariableDeclaration;

class MethodDeclarator: public Node
{
public:
	static std::unique_ptr<MethodDeclarator> create(const Parse::Tree *ptNode);
	explicit MethodDeclarator(const Parse::TConstructorDeclarator *ptNode);
	explicit MethodDeclarator(const Parse::TMethodDeclarator *ptNode);
	std::string toCode() const override;
protected:
	std::string id;
	std::vector<std::unique_ptr<VariableDeclaration>> parameterList;
	friend class MethodHeader;
	friend class ConstructorDeclaration;
};

} //namespace AST
