#include "ast/classInstanceCreationExpression.h"
#include "ast/type.h"
#include "ast/expression.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"
#include <vector>
#include <memory>
#include <semantic/semantic.h>

namespace AST
{

// static
std::unique_ptr<ClassInstanceCreationExpression> ClassInstanceCreationExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ClassInstanceCreationExpression:
		return std::make_unique<ClassInstanceCreationExpression>(static_cast<const Parse::TClassInstanceCreationExpression*>(ptNode));
	default:
		FAILED("inappropriate PT type for ClassInstanceCreationExpression: " + std::to_string((int)ptNode->type));
	}
}
ClassInstanceCreationExpression::ClassInstanceCreationExpression(const Parse::TClassInstanceCreationExpression *ptNode)
  : type(Type::create(ptNode->classType)),
	args(std::move(NodeList<Expression>(ptNode->argumentList).list))
{
}

std::string ClassInstanceCreationExpression::toCode() const
{
	std::string str = "(new " + type->toCode() + "(";
	for (auto &arg : args)
	{
		str += arg->toCode();
		str += ", ";
	}
	// remove the extra ", "
	if (!args.empty())
	{
		str.pop_back();
		str.pop_back();
	}
	str += "))";
	return str;
}

Semantic::SemanticErrorType
ClassInstanceCreationExpression::resolveTypes(Semantic::SemanticDB const &semantic, TypeDeclaration *enclosingClass) {
	auto error = type->resolve(semantic, enclosingClass);
	if (error != Semantic::SemanticErrorType::None)
		return error;
	for (auto &expr : args) {
		error = expr->resolveTypes(semantic, enclosingClass);
		if (error != Semantic::SemanticErrorType::None)
			return error;
	}
	return Semantic::SemanticErrorType::None;
}

} //namespace AST
