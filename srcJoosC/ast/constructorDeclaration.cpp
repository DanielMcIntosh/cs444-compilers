#include "ast/constructorDeclaration.h"
#include "ast/memberDeclaration.h"
#include "ast/modifier.h"
#include "ast/methodDeclarator.h"
#include "ast/block.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<ConstructorDeclaration> ConstructorDeclaration::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ConstructorDeclaration:
		return std::make_unique<ConstructorDeclaration>(static_cast<const Parse::TConstructorDeclaration*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for ConstructorDeclaration: " + std::to_string((int)ptNode->type));
	}
}

ConstructorDeclaration::ConstructorDeclaration(std::vector<std::unique_ptr<Modifier>> mods, MethodDeclarator &&declarator, std::unique_ptr<Block> block)
  : MemberDeclaration(std::move(mods), std::move(declarator.id)),
	parameters(std::move(declarator.parameterList)),
	body(std::move(block))
{
}
ConstructorDeclaration::ConstructorDeclaration(const Parse::TConstructorDeclaration *ptNode)
  : ConstructorDeclaration(std::move(NodeList<Modifier>(ptNode->modifiers).list),
		MethodDeclarator(ptNode->constructorDeclarator), std::make_unique<Block>(ptNode->block))
{
}

std::string ConstructorDeclaration::toCode()
{
	std::string str;
	for (auto &mod: modifiers)
	{
		str += mod->toCode() + " ";
	}
	str += identifier;
	str += "(";
	for (auto &param : parameters)
	{
		str += param->toCode() + ", ";
	}
	// pop the extra ", "
	if (!parameters.empty())
	{
		str.pop_back();
		str.pop_back();
	}
    str += ") ";
	str += body->toCode();
	return str;
}

bool ConstructorDeclaration::equals(FieldDeclaration *other) {
  return false;
}

bool ConstructorDeclaration::equals(MemberDeclaration *other) {
  return false;
}

bool ConstructorDeclaration::equals(ConstructorDeclaration *other) {
  if (parameters.size() != other->parameters.size())
    return false;
  for (size_t i = 0; i < parameters.size(); ++i) {
    if (!parameters[i]->equals(other->parameters[i].get()))
      return false;
  }
  return true;
}

bool ConstructorDeclaration::equals(MethodDeclaration *other) {
  return false;
}

} //namespace AST
