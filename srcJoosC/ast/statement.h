#pragma once

#include "ast/node.h"

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
}

namespace AST
{

class TypeDeclaration;

class Statement: public Node
{
public:
	static std::unique_ptr<Statement> create(const Parse::Tree *ptNode);

	virtual Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);
};

} //namespace AST
