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
class Name;

//////////////////////////////////////////////////////////////////////////////
//
// Type
//
//////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////
//
// PrimitiveType
//
//////////////////////////////////////////////////////////////////////////////

class PrimitiveType: public Type
{
public:
	enum class Variant
	{
		Boolean,
		Byte,
		Short,
		Int,
		Char,
		Void,
		Max
	} type;

	static std::unique_ptr<PrimitiveType> create(const Parse::Tree *ptNode);
	explicit PrimitiveType(const Parse::TPrimitiveType *ptNode);
	// void type - see note in Type::create
	explicit PrimitiveType(std::nullptr_t null);

	Semantic::SemanticErrorType resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	using Type::equals;
	virtual bool equals(PrimitiveType *) override;
	std::string toCode() const override;
};

std::string operator+(std::string str, PrimitiveType::Variant type);
std::string operator+=(std::string& str, PrimitiveType::Variant type);
std::ostream& operator<<(std::ostream& os, PrimitiveType::Variant type);

//////////////////////////////////////////////////////////////////////////////
//
// NameType
//
//////////////////////////////////////////////////////////////////////////////

class NameType: public Type
{
public:
	static std::unique_ptr<NameType> create(const Parse::Tree *ptNode);
	explicit NameType(Name&& other);
	std::string toCode() const override;

	std::string flatten() const;
	Semantic::SemanticErrorType resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	TypeDeclaration *getDeclaration();

	using Type::equals;
	virtual bool equals(NameType *) override;

protected:
	std::vector<std::string> prefix;
	std::string id;

	TypeDeclaration *declaration = nullptr;
};

} //namespace AST
