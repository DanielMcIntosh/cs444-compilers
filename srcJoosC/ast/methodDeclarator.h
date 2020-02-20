#pragma once

#include "ast/node.h"
#include "ast/name.h"
#include "ast/variableDeclaration.h"
#include <vector>
#include <memory>
#include <string>

namespace AST
{

class MethodDeclarator: public Node
{
public:
	static std::unique_ptr<MethodDeclarator> create(const Parse::Tree *ptNode);
	explicit MethodDeclarator(const Parse::TConstructorDeclarator *ptNode);
	explicit MethodDeclarator(const Parse::TMethodDeclarator *ptNode);

	std::string id;
	std::vector<std::unique_ptr<VariableDeclaration>> parameterList;

	std::string toCode() const override;
};

} //namespace AST
