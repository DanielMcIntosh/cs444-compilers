#pragma once

#include "ast/node.h"

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
	class Scope;
}

namespace AST
{

class TypeDeclaration;

class Expression: public Node
{
public:
	static std::unique_ptr<Expression> create(const Parse::Tree *ptNode);

	virtual Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);
	//virtual Semantic::SemanticErrorType resolve(Semantic::Scope const& scope);
};

} //namespace AST
