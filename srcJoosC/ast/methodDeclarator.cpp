#include "ast/methodDeclarator.h"
#include "ast/nodeList.h"
#include "ast/variableDeclaration.h"
#include "ast/type.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>
#include <vector>

namespace AST
{

// static
std::unique_ptr<MethodDeclarator> MethodDeclarator::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ConstructorDeclarator:
		return std::make_unique<MethodDeclarator>(static_cast<const Parse::TConstructorDeclarator*>(ptNode));
	case Parse::NonTerminalType::MethodDeclarator:
		return std::make_unique<MethodDeclarator>(static_cast<const Parse::TMethodDeclarator*>(ptNode));
	default:
		FAILED("inappropriate PT type for MethodDeclarator: " + std::to_string((int)ptNode->type));
	}
}
MethodDeclarator::MethodDeclarator(const Parse::TConstructorDeclarator *ptNode)
  : id(ptNode->identifier->value),
	parameterList(std::move(NodeList<VariableDeclaration>(ptNode->formalParameterList).list))
{
	nodeType = NodeType::MethodDeclarator;
}
MethodDeclarator::MethodDeclarator(const Parse::TMethodDeclarator *ptNode)
  : id(ptNode->identifier->value),
	parameterList(std::move(NodeList<VariableDeclaration>(ptNode->formalParameterList).list))
{
	nodeType = NodeType::MethodDeclarator;
}

std::string MethodDeclarator::toCode() const
{
	// we're a PseudoAST node, so this shouldn't be called
	// therefore, we'll print something which is useful for debugging, but doesn't look like actual code
	std::string str = "[MethodDeclarator: id=" + id + " parameterList=";
	for (auto &param : parameterList)
	{
		str += param->toCode();
		str += ",";
	}
	str += "]";
	return str;
}

} //namespace AST
