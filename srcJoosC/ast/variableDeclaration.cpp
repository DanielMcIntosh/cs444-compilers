#include "ast/variableDeclaration.h"
#include "ast/variableDeclarator.h"
#include "ast/expression.h"
#include "ast/type.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<VariableDeclaration> VariableDeclaration::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::FormalParameter:
		return std::make_unique<VariableDeclaration>(static_cast<const Parse::TFormalParameter*>(ptNode));
	case Parse::NonTerminalType::LocalVariableDeclaration:
		return std::make_unique<VariableDeclaration>(static_cast<const Parse::TLocalVariableDeclaration*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for VariableDeclaration: " + std::to_string((int)ptNode->type));
	}
}
VariableDeclaration::VariableDeclaration(const Parse::TFormalParameter *ptNode)
{
}
VariableDeclaration::VariableDeclaration(const Parse::TLocalVariableDeclaration *ptNode)
{
}

} //namespace AST
