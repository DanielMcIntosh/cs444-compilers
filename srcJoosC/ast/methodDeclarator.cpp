#include "ast/methodDeclarator.h"
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
	if (ptNode->oneNt)
	{
		return MethodDeclarator::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ConstructorDeclarator:
		return std::make_unique<MethodDeclarator>(static_cast<const Parse::TConstructorDeclarator*>(ptNode));
	case Parse::NonTerminalType::MethodDeclarator:
		return std::make_unique<MethodDeclarator>(static_cast<const Parse::TMethodDeclarator*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for MethodDeclarator: " + std::to_string((int)ptNode->type));
	}
}
MethodDeclarator::MethodDeclarator(const Parse::TConstructorDeclarator *ptNode)
{
}
MethodDeclarator::MethodDeclarator(const Parse::TMethodDeclarator *ptNode)
{
}

} //namespace AST
