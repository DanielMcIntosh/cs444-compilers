#include "ast/methodDeclaration.h"
#include "ast/memberDeclaration.h"
#include "ast/methodHeader.h"
#include "ast/type.h"
#include "ast/variableDeclaration.h"
#include "ast/modifier.h"
#include "ast/statement.h"
#include "parse/parseTree.h"
#include "semantic/scope.h"
#include "semantic/semantic.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<MethodDeclaration> MethodDeclaration::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return MethodDeclaration::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::AbstractMethodDeclaration:
		return std::make_unique<MethodDeclaration>(static_cast<const Parse::TAbstractMethodDeclaration*>(ptNode));
	case Parse::NonTerminalType::MethodDeclaration:
		return std::make_unique<MethodDeclaration>(static_cast<const Parse::TMethodDeclaration*>(ptNode));
	default:
		FAILED("inappropriate PT type for MethodDeclaration: " + std::to_string((int)ptNode->type));
	}
}

MethodDeclaration::MethodDeclaration(MethodHeader&& header, std::unique_ptr<Block> block)
	: MemberDeclaration(std::move(header.modifiers)),
		returnType(std::move(header.returnType)),
		identifier(std::move(header.id)),
		parameters(std::move(header.parameterList)),
		body(std::move(block))
{
	nodeType = NodeType::MethodDeclaration;
	for (const auto &mod : modifiers) {
		modifierSet[static_cast<size_t>(mod->type)] = true;
	}
}
MethodDeclaration::MethodDeclaration(const Parse::TAbstractMethodDeclaration *ptNode)
	: MethodDeclaration(MethodHeader(ptNode->methodHeader), nullptr)
{
	nodeType = NodeType::MethodDeclaration;
	// interface methods are implicitly public abstract
	modifierSet[static_cast<size_t>(Modifier::Variant::Public)] = true;
	modifierSet[static_cast<size_t>(Modifier::Variant::Abstract)] = true;
}
MethodDeclaration::MethodDeclaration(const Parse::TMethodDeclaration *ptNode)
	: MethodDeclaration(MethodHeader(ptNode->methodHeader), Block::create(ptNode->methodBody->block))
{
	nodeType = NodeType::MethodDeclaration;
}
std::string MethodDeclaration::toCode() const {
	std::string s = returnType->toCode() + " " + identifier + "(";
	for (const auto& p : parameters)
	{
		s += p->toCode() + ", ";
	}
	if (!parameters.empty()) {
		s.pop_back();
		s.pop_back();
	}
	s += ") ";
	if (body)
	{
		s += body->toCode();
	}
	return s;
}

bool MethodDeclaration::signatureEquals(MethodDeclaration *other) {
	if (parameters.size() != other->parameters.size())
		return false;
	for (size_t i = 0; i < parameters.size(); ++i) {
		if (!parameters[i]->typeEquals(other->parameters[i].get()))
			return false;
	}
	return identifier == other->identifier;
}

bool MethodDeclaration::returnEquals(MethodDeclaration *other) {
	return returnType->equals(other->returnType.get());
}

bool MethodDeclaration::equals(MethodDeclaration *other) {
	if (parameters.size() != other->parameters.size())
		return false;
	for (size_t i = 0; i < parameters.size(); ++i) {
		if (!parameters[i]->equals(other->parameters[i].get()))
			return false;
	}
	return identifier == other->identifier;
}

Semantic::SemanticErrorType MethodDeclaration::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (Semantic::SemanticErrorType err = returnType->resolve(semantic, enclosingClass);
		err != Semantic::SemanticErrorType::None)
	{
		return err;
	}

	for (auto &param: parameters)
	{
		if (Semantic::SemanticErrorType err = param->resolveTypes(semantic, enclosingClass);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}

	if (body)
	{
		if (Semantic::SemanticErrorType err = body->resolveTypes(semantic, enclosingClass);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	return Semantic::SemanticErrorType::None;
}

Semantic::SemanticErrorType MethodDeclaration::resolveExprs(Semantic::Scope &parentScope)
{
	Semantic::Scope scope(parentScope);
	for (auto &param: parameters)
	{
		if (!scope.add(param))
		{
			return Semantic::SemanticErrorType::ExprResolution;
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

} //namespace AST
