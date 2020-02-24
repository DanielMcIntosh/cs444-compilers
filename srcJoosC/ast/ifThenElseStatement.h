#pragma once

#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include <memory>

namespace AST
{

class IfThenElseStatement: public ConditionalStatement
{
public:
	static std::unique_ptr<IfThenElseStatement> create(const Parse::Tree *ptNode);
	explicit IfThenElseStatement(const Parse::TIfThenElseStatement *ptNode);
	explicit IfThenElseStatement(const Parse::TIfThenElseStatementNoShortIf *ptNode);
	std::string toCode() const override;

	std::unique_ptr<Statement> elseBody;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
};

} //namespace AST
