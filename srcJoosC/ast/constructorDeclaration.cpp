#include "ast/constructorDeclaration.h"
#include "ast/memberDeclaration.h"
#include "ast/modifier.h"
#include "ast/methodDeclarator.h"
#include "ast/variableDeclaration.h"
#include "ast/nodeList.h"
#include "ast/type.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "ast/typeDeclaration.h"
#include "parse/parseTree.h"
#include "semantic/scope.h"
#include "semantic/semantic.h"
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
		FAILED("inappropriate PT type for ConstructorDeclaration: " + std::to_string((int)ptNode->type));
	}
}

ConstructorDeclaration::ConstructorDeclaration(std::vector<std::unique_ptr<Modifier>> mods, MethodDeclarator &&declarator, std::unique_ptr<Block> block)
  : MemberDeclaration(std::move(mods)),
	identifier(std::move(declarator.id)),
	parameters(std::move(declarator.parameterList)),
	body(std::move(block))
{
	nodeType = NodeType::ConstructorDeclaration;
}
ConstructorDeclaration::ConstructorDeclaration(const Parse::TConstructorDeclaration *ptNode)
	: ConstructorDeclaration(std::move(NodeList<Modifier>(ptNode->modifiers).list),
		MethodDeclarator(ptNode->constructorDeclarator), std::make_unique<Block>(ptNode->block))
{
	nodeType = NodeType::ConstructorDeclaration;
}

std::string ConstructorDeclaration::toCode() const
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

bool ConstructorDeclaration::equals(const ConstructorDeclaration *other) const {
	if (parameters.size() != other->parameters.size())
		return false;
	for (size_t i = 0; i < parameters.size(); ++i) {
		if (!parameters[i]->equals(other->parameters[i].get()))
			return false;
	}
	return true;
}

bool ConstructorDeclaration::signatureEquals(const ConstructorDeclaration *other) const {
	if (parameters.size() != other->parameters.size())
		return false;
	for (size_t i = 0; i < parameters.size(); ++i) {
		if (!parameters[i]->typeEquals(other->parameters[i].get()))
			return false;
	}
	return identifier == other->identifier;
}
bool ConstructorDeclaration::signatureEquals(const ClassInstanceCreationExpression *invocation) const {
	// account for extra "this" parameter
	if (invocation->args.size() + 1 != parameters.size())
		return false;
	// this check is reduntant, but helps with clarity
	if (!parameters[0]->typeEquals(invocation->type.get()))
		return false;
	for (size_t i = 1; i < parameters.size(); ++i) {
		if (!parameters[i]->typeEquals(invocation->args[i-1]->typeResult))
			return false;
	}
	return true;
}

Semantic::SemanticErrorType ConstructorDeclaration::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	for (auto &param: parameters)
	{
		if (Semantic::SemanticErrorType err = param->resolveTypes(semantic, enclosingClass);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}

	if (Semantic::SemanticErrorType err = body->resolveTypes(semantic, enclosingClass);
		err != Semantic::SemanticErrorType::None)
	{
		return err;
	}

	return Semantic::SemanticErrorType::None;
}

Semantic::SemanticErrorType ConstructorDeclaration::resolveExprs(Semantic::Scope &parentScope)
{
	if (identifier != parentScope._enclosingClass->name) {
		return Semantic::SemanticErrorType::ConstructorWrongName;
	}
	Semantic::Scope scope(parentScope);
	for (auto &param: parameters)
	{
		if (!scope.add(param))
		{
			return Semantic::SemanticErrorType::LocalVariableShadowing;
		}
	}

	if (body)
	{
		if (Semantic::SemanticErrorType err = body->resolveExprs(scope);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	return Semantic::SemanticErrorType::None;
}

void ConstructorDeclaration::addThisParam(TypeDeclaration *decl)
{
	if (!hasModifier(Modifier::Variant::Static))
	{
		parameters.insert(parameters.begin(), std::make_unique<VariableDeclaration>(decl->asType(), "this"));
	}
}

} //namespace AST
