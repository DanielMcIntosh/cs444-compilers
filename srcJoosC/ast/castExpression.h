#pragma once

#include "ast/expression.h"
#include "ast/type.h"
#include "ast/unaryExpression.h"
#include <vector>
#include <memory>

namespace AST
{

class CastExpression: public Expression
{
public:
	static std::unique_ptr<CastExpression> create(const Parse::Tree *ptNode);
	explicit CastExpression(const Parse::TCastExpression *ptNode);
	std::string toCode() const override;

	std::unique_ptr<Type> type;
	std::unique_ptr<Expression> rhs;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
};

} //namespace AST
