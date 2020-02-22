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

	virtual bool equals(PrimitiveType *);
	virtual bool equals(NameType *);
	virtual bool equals(Type *);

	virtual Semantic::SemanticErrorType resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) = 0;
protected:
	Type() = default;
};

} //namespace AST
