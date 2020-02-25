#pragma once

#include "ast/node.h"
#include <vector>
#include <memory>
#include <string>

namespace AST
{

class VariableDeclaration;

class EXPORT MethodDeclarator: public Node
{
public:
	EXPORT static std::unique_ptr<MethodDeclarator> create(const Parse::Tree *ptNode);
	EXPORT explicit MethodDeclarator(const Parse::TConstructorDeclarator *ptNode);
	EXPORT explicit MethodDeclarator(const Parse::TMethodDeclarator *ptNode);
	EXPORT std::string toCode() const override;
protected:
	std::string id;
	std::vector<std::unique_ptr<VariableDeclaration>> parameterList;
	friend class MethodHeader;
	friend class ConstructorDeclaration;
};

} //namespace AST
