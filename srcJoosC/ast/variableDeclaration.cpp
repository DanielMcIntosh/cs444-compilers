#include "ast/variableDeclaration.h"
#include "ast/variableDeclarator.h"
#include "ast/expression.h"
#include "ast/type.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
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
	nodeType = NodeType::VariableDeclaration;
}
VariableDeclaration::VariableDeclaration(const Parse::TVariableDeclaration *ptNode)
	: type(Type::create(ptNode->type)),
	identifier(ptNode->variableDeclarator->identifier->value),
    initializer(Expression::create(ptNode->variableDeclarator->expression))
{
	nodeType = NodeType::VariableDeclaration;
}
VariableDeclaration::VariableDeclaration(std::unique_ptr<Type> t, std::string id, std::unique_ptr<Expression> init)
  :	type(std::move(t)),
	identifier(std::move(id)),
    initializer(std::move(init))
{
	nodeType = NodeType::VariableDeclaration;
}


std::string VariableDeclaration::toCode() const {
    if (initializer) {
        return type->toCode() + " " + identifier + " = " + initializer->toCode();
    } else {
        return type->toCode() + " " + identifier;
    }
}

bool VariableDeclaration::equals(const VariableDeclaration *other) const {
	return idEquals(other) && typeEquals(other);
}

bool VariableDeclaration::idEquals(const VariableDeclaration *other) const {
	return identifier == other->identifier;
}
bool VariableDeclaration::idEquals(std::string const& str) const
{
	return identifier == str;
}

bool VariableDeclaration::typeEquals(const VariableDeclaration *other) const {
	return type->equals(other->type.get());
}
bool VariableDeclaration::typeEquals(const Type *other) const {
	return type->equals(other);
}
bool VariableDeclaration::typeEquals(const TypeResult &other) const {
	return type->equals(other);
}

bool VariableDeclaration::hasInitializer() const
{
	return initializer != nullptr;
}

std::unique_ptr<LocalVariableExpression> VariableDeclaration::asLocalVarExpr()
{
	auto ret = std::make_unique<LocalVariableExpression>(identifier);
	// resolve
	ret->declaration = this;
	// deduce
	ret->deduceType();
	return ret;
}
std::unique_ptr<AssignmentExpression> VariableDeclaration::initializerAsAssignmentExpr(std::unique_ptr<Expression> lhs)
{
	return std::make_unique<AssignmentExpression>(std::move(lhs), std::unique_ptr<Expression>(initializer->clone()));
}


} //namespace AST
