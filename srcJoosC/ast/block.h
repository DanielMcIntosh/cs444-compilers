#pragma once

#include "ast/statement.h"
#include <memory>
#include <vector>

namespace AST
{

class Block: public Statement
{
public:
	static std::unique_ptr<Block> create(const Parse::Tree *ptNode);
	explicit Block(const Parse::TBlock *ptNode);
	std::string toCode() const override;

	std::vector<std::unique_ptr<Statement>> statements;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) override;
};

} //namespace AST
