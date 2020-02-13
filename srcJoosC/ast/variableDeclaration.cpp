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
	: type(Type::create(ptNode->type)),
	identifier(ptNode->identifier->value)
{

}
VariableDeclaration::VariableDeclaration(const Parse::TLocalVariableDeclaration *ptNode)
	: type(Type::create(ptNode->type)),
	identifier(ptNode->variableDeclarator->identifier->value),
    initializer(Expression::create(ptNode->variableDeclarator->expression))
{
}

std::string VariableDeclaration::toCode() {
    if (initializer) {
        return type->toCode() + " " + identifier + " = " + initializer->toCode();
    } else {
        return type->toCode() + " " + identifier;
    }
}

} //namespace AST
