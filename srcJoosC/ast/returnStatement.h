#pragma once

#include "ast/statement.h"
#include <memory>

namespace AST
{

class Expression;

class ReturnStatement: public Statement
{
public:
	static std::unique_ptr<ReturnStatement> create(const Parse::Tree *ptNode);
	explicit ReturnStatement(const Parse::TReturnStatement *ptNode);

	// nullable
	std::unique_ptr<Expression> returnValue;

	std::string toCode() const override;
	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
};

} //namespace AST
