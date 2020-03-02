#include "ast/fieldDeclaration.h"
#include "ast/memberDeclaration.h"
#include "ast/type.h"
#include "ast/variableDeclaration.h"
#include "ast/modifier.h"
#include "ast/nodeList.h"
#include "ast/expression.h"
#include "ast/typeDeclaration.h"
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
	varDecl(std::make_unique<VariableDeclaration>(ptNode->variableDeclaration))
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
	str += varDecl->toCode() + ";";
	return str;
}

bool FieldDeclaration::equals(const FieldDeclaration *other) const {
  return varDecl->equals(other->varDecl.get());
}

bool FieldDeclaration::idEquals(const FieldDeclaration *other) const {
	return varDecl->idEquals(other->varDecl.get());
}
bool FieldDeclaration::idEquals(const FieldAccess *other) const
{
	return varDecl->idEquals(other->member)
	&& (hasModifier(Modifier::Variant::Static) == other->isStaticAccessor());
}

Semantic::SemanticErrorType FieldDeclaration::resolveTypes(Semantic::SemanticDB const& semantic)
{
	return varDecl->resolveTypes(semantic, _enclosingClass);
}

Semantic::SemanticErrorType FieldDeclaration::resolveExprs()
{
	Semantic::Scope scope(_enclosingClass);
	auto thisDecl = std::make_unique<VariableDeclaration>(_enclosingClass->asType(), "this");
	if (!hasModifier(Modifier::Variant::Static))
	{
		scope.add(thisDecl);
	}
	return varDecl->resolveExprs(scope);
}

} //namespace AST
