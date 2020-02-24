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
	case Parse::NonTerminalType::VariableDeclaration:
		return std::make_unique<VariableDeclaration>(static_cast<const Parse::TVariableDeclaration*>(ptNode));
	default:
		FAILED("inappropriate PT type for VariableDeclaration: " + std::to_string((int)ptNode->type));
	}
}
VariableDeclaration::VariableDeclaration(const Parse::TFormalParameter *ptNode)
	: type(Type::create(ptNode->type)),
	identifier(ptNode->identifier->value)
{

}
VariableDeclaration::VariableDeclaration(const Parse::TVariableDeclaration *ptNode)
	: type(Type::create(ptNode->type)),
	identifier(ptNode->variableDeclarator->identifier->value),
    initializer(Expression::create(ptNode->variableDeclarator->expression))
{
}

std::string VariableDeclaration::toCode() const {
    if (initializer) {
        return type->toCode() + " " + identifier + " = " + initializer->toCode();
    } else {
        return type->toCode() + " " + identifier;
    }
}

bool VariableDeclaration::equals(const VariableDeclaration *other) const{
	return identifier == other->identifier && type->equals(other->type.get());
}

bool VariableDeclaration::idEqual(const VariableDeclaration *other) const{
	return identifier == other->identifier;
}

Semantic::SemanticErrorType VariableDeclaration::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return type->resolve(semantic, enclosingClass);
}

} //namespace AST
