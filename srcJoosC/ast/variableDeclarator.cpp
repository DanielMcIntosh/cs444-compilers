#include "ast/variableDeclarator.h"
#include "ast/node.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<VariableDeclarator> VariableDeclarator::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::VariableDeclarator:
		return std::make_unique<VariableDeclarator>(static_cast<const Parse::TVariableDeclarator*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for VariableDeclarator: " + std::to_string((int)ptNode->type));
	}
}
VariableDeclarator::VariableDeclarator(const Parse::TVariableDeclarator *ptNode)
{
}


} //namespace AST
