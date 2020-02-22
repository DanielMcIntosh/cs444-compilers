#pragma once

#include "ast/node.h"

#include <string>

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
}

namespace AST
{

class TypeDeclaration;
class PrimitiveType;
class NameType;

class Type: public Node
{
public:
	static std::unique_ptr<Type> create(const Parse::Tree *ptNode);

	bool isArray = false;

	virtual bool equals(PrimitiveType *) = 0;
	virtual bool equals(NameType *) = 0;
	virtual bool equals(Type *) = 0;

	virtual Semantic::SemanticErrorType resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) = 0;
protected:
	Type() = default;
};

} //namespace AST
