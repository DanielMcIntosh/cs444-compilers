#include "ast/fieldDeclaration.h"
#include "ast/memberDeclaration.h"
#include "ast/type.h"
#include "ast/modifier.h"
#include "ast/variableDeclarator.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"
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

bool FieldDeclaration::equals(FieldDeclaration *other) {
  return declaration->equals(other->declaration.get());
}

bool FieldDeclaration::equals(MemberDeclaration *other) {
  return false;
}

bool FieldDeclaration::equals(ConstructorDeclaration *other) {
  return false;
}

bool FieldDeclaration::equals(MethodDeclaration *) {
  return false;
}

} //namespace AST
