#include "ast/methodDeclaration.h"
#include "ast/memberDeclaration.h"
#include "ast/methodHeader.h"
#include "ast/type.h"
#include "ast/variableDeclaration.h"
#include "ast/modifier.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "ast/typeDeclaration.h"
#include "parse/parseTree.h"
#include "semantic/scope.h"
#include "semantic/semantic.h"
#include <memory>

namespace AST
{

void MethodDeclaration::staticAnalysis(StaticAnalysisCtx *ctx) {
	auto nCtx = *ctx;
	if (body) {
		body->staticAnalysis(&nCtx);
		if (returnType->nodeType == NodeType::PrimitiveType) {
			auto primType = (PrimitiveType*)returnType.get();
			if (primType->type != PrimitiveType::Variant::Void) {
				nCtx.hasError |= nCtx.out;
			}
		} else {
			nCtx.hasError |= nCtx.out;
		}
	}
	ctx->hasError = nCtx.hasError;
}

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
	std::string s;
	for (auto &mod : modifiers)
	{
		s += mod->toCode() + " ";
	}
	s += returnType->toCode() + " " + identifier + "(";
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

bool MethodDeclaration::signatureEquals(const MethodDeclaration *other) const {
	if (parameters.size() != other->parameters.size())
		return false;
	for (size_t i = 0; i < parameters.size(); ++i) {
		if (!parameters[i]->typeEquals(other->parameters[i].get()))
			return false;
	}
	return identifier == other->identifier;
}
bool MethodDeclaration::signatureEquals(const MethodInvocation *invocation) const {
	return std::visit(visitor {
			[&invocation, this](const std::unique_ptr<Expression> &src) {
				if (hasModifier(Modifier::Variant::Static))
					return false;
				// account for extra "this" parameter
				if (invocation->args.size() + 1 != parameters.size())
					return false;
				for (size_t i = 1; i < parameters.size(); ++i) {
					if (!parameters[i]->typeEquals(invocation->args[i-1]->typeResult))
						return false;
				}
				return identifier == invocation->methodName;
			},
			[&invocation, this](const std::unique_ptr<NameType> &src) {
				if (!hasModifier(Modifier::Variant::Static))
					return false;
				if (parameters.size() != invocation->args.size())
					return false;
				for (size_t i = 0; i < parameters.size(); ++i) {
					if (!parameters[i]->typeEquals(invocation->args[i]->typeResult))
						return false;
				}
				return identifier == invocation->methodName;
			},
			[](const std::unique_ptr<Name> &src) { return false; }
		}, invocation->source);
}

bool MethodDeclaration::returnEquals(const MethodDeclaration *other) const {
	return returnType->equals(other->returnType.get());
}

bool MethodDeclaration::equals(const MethodDeclaration *other) const {
	if (parameters.size() != other->parameters.size())
		return false;
	for (size_t i = 0; i < parameters.size(); ++i) {
		if (!parameters[i]->equals(other->parameters[i].get()))
			return false;
	}
	return identifier == other->identifier;
}

void MethodDeclaration::addThisParam()
{
	if (!hasModifier(Modifier::Variant::Static))
	{
		parameters.insert(parameters.begin(), std::make_unique<VariableDeclaration>(_enclosingClass->asType(), "this"));
	}
}

} //namespace AST
