#include "ast/constructorDeclaration.h"
#include "ast/memberDeclaration.h"
#include "ast/modifier.h"
#include "ast/methodDeclarator.h"
#include "ast/block.h"
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
		throw std::runtime_error("inapropriate PT type for ConstructorDeclaration: " + std::to_string((int)ptNode->type));
	}
}

ConstructorDeclaration::ConstructorDeclaration(const Parse::TModifiers *ptModifiers, MethodDeclarator &&declarator, const Parse::TBlock *block)
  : MemberDeclaration(ptModifiers, declarator.id),
	parameters(std::move(declarator.parameterList)),
	body(std::make_unique<Block>(block))
{
}
ConstructorDeclaration::ConstructorDeclaration(const Parse::TConstructorDeclaration *ptNode)
  : ConstructorDeclaration(ptNode->modifiers, MethodDeclarator(ptNode->constructorDeclarator), ptNode->block)
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
	str += body->toCode();
	return str;
}

} //namespace AST
