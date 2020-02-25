#pragma once

#include "ast/statement.h"
#include <memory>

namespace AST
{

class Expression;

class ExpressionStatement: public Statement
{
public:
	static std::unique_ptr<ExpressionStatement> create(const Parse::Tree *ptNode);
	explicit ExpressionStatement(const Parse::TExpressionStatement *ptNode);
	std::string toCode() const override;

	// nullable
	std::unique_ptr<Expression> expression;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
};

} //namespace AST
