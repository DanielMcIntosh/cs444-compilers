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
  return other && varDecl->equals(other->varDecl.get());
}

bool FieldDeclaration::idEquals(const FieldDeclaration *other) const {
	return other && varDecl->idEquals(other->varDecl.get());
}
bool FieldDeclaration::idEquals(const FieldAccess *other) const
{
	return other && varDecl->idEquals(other->member)
	&& (hasModifier(Modifier::Variant::Static) == other->isStaticAccessor());
}

std::unique_ptr<FieldAccess> FieldDeclaration::asFieldAccess(std::unique_ptr<Expression> src)
{
	std::unique_ptr<FieldAccess> ret;
	if (hasModifier(Modifier::Variant::Static))
	{
		assert(src == nullptr);
		ret = std::make_unique<FieldAccess>(_enclosingClass->asType(), varDecl->identifier);
	}
	else
	{
		assert(src != nullptr);
		ret = std::make_unique<FieldAccess>(std::move(src), varDecl->identifier);
	}
	if (!src || src->hasBeenResolved())
	{
		// resolve
		ret->decl = this;
		// deduce
		ret->deduceType();
	}
	return ret;
}

} //namespace AST
