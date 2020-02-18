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
		throw std::runtime_error("inappropriate PT type for FieldDeclaration: " + std::to_string((int)ptNode->type));
	}
}
FieldDeclaration::FieldDeclaration(std::vector<std::unique_ptr<Modifier>> mods, VariableDeclarator &&declarator, std::unique_ptr<Type> t)
  : MemberDeclaration(std::move(mods), std::move(declarator.id)),
    type(std::move(t)),
    initializer(std::move(declarator.initializer))
{
}
FieldDeclaration::FieldDeclaration(const Parse::TFieldDeclaration *ptNode)
  : FieldDeclaration(std::move(NodeList<Modifier>(ptNode->modifiers).list), VariableDeclarator(ptNode->variableDeclarator), Type::create(ptNode->type))
{
}

std::string FieldDeclaration::toCode()
{
	std::string str;
	for (auto &mod: modifiers)
	{
		str += mod->toCode() + " ";
	}
	str += type->toCode() + " ";
	str += identifier;
	if (initializer)
	{
		str += "=" + initializer->toCode();
	}
	str += ";";
	return str;
}

bool FieldDeclaration::equals(FieldDeclaration *other) {
  return identifier == other->identifier && type->equals(other->type.get());
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
