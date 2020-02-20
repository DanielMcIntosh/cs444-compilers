#pragma once

#include "ast/node.h"

#include <string>

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
	TypeDeclaration *declaration = nullptr;

	virtual bool equals(PrimitiveType *) = 0;
	virtual bool equals(NameType *) = 0;
	virtual bool equals(Type *) = 0;

	void resolve(TypeDeclaration *decl);
protected:
	Type() = default;
};

} //namespace AST
