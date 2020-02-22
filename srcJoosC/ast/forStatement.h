#pragma once

#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include <memory>

namespace AST
{

class ForStatement: public ConditionalStatement
{
public:
	static std::unique_ptr<ForStatement> create(const Parse::Tree *ptNode);
	explicit ForStatement(const Parse::TForStatementNoShortIf *ptNode);
	explicit ForStatement(const Parse::TForStatement *ptNode);
	std::string toCode() const override;

    // nullable
	std::unique_ptr<Statement> init;
	// nullable
	std::unique_ptr<Expression> increment;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
};

} //namespace AST
