#include "ast/fieldDeclaration.h"
#include "ast/memberDeclaration.h"
#include "ast/type.h"
#include "ast/variableDeclaration.h"
#include "ast/modifier.h"
#include "ast/nodeList.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include "semantic/scope.h"
#include "semantic/semantic.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<FieldDeclaration> FieldDeclaration::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::FieldDeclaration:
		return std::make_unique<FieldDeclaration>(static_cast<const Parse::TFieldDeclaration*>(ptNode));
	default:
		FAILED("inappropriate PT type for FieldDeclaration: " + std::to_string((int)ptNode->type));
	}
}
FieldDeclaration::FieldDeclaration(const Parse::TFieldDeclaration *ptNode)
  : MemberDeclaration(std::move(NodeList<Modifier>(ptNode->modifiers).list)),
	declaration(std::make_unique<VariableDeclaration>(ptNode->variableDeclaration))
{
	nodeType = NodeType::FieldDeclaration;
}

std::string FieldDeclaration::toCode() const
{
	std::string str;
	for (auto &mod: modifiers)
	{
		str += mod->toCode() + " ";
	}
	str += declaration->toCode() + ";";
	return str;
}

bool FieldDeclaration::equals(const FieldDeclaration *other) const {
  return declaration->equals(other->declaration.get());
}

bool FieldDeclaration::idEquals(const FieldDeclaration *other) const {
	return declaration->idEquals(other->declaration.get());
}
bool FieldDeclaration::idEquals(const FieldAccess *other) const
{
	return declaration->idEquals(other->member)
	&& (hasModifier(Modifier::Variant::Static) == std::holds_alternative<std::unique_ptr<NameType>>(other->source));
}

Semantic::SemanticErrorType FieldDeclaration::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return declaration->resolveTypes(semantic, enclosingClass);
}

Semantic::SemanticErrorType FieldDeclaration::resolveExprs(Semantic::Scope &parentScope)
{
	return declaration->resolveExprs(parentScope);
}

} //namespace AST
