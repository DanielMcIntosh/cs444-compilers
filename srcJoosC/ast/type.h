#pragma once

#include "ast/node.h"

#include <string>

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
	class Type;
}

namespace AST
{

class TypeDeclaration;
class PrimitiveType;
class NameType;
class Name;
class TypeResult;

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

	virtual Semantic::SemanticErrorType resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) = 0;
protected:
	Type() = default;

public:
	// double dispatch for correct equals behaviour
	virtual bool equals(const Type *) const = 0;
	virtual bool equals(const TypeResult &) const = 0;
protected:
	virtual bool equalsDerived(const PrimitiveType *) const { return false; };
	virtual bool equalsDerived(const NameType *) const { return false; };
	friend class NameType;
	friend class PrimitiveType;
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
		Null,
		Max
	} type;

	static std::unique_ptr<PrimitiveType> create(const Parse::Tree *ptNode);
	explicit PrimitiveType(const Parse::TPrimitiveType *ptNode);
	// void type - see note in Type::create
	explicit PrimitiveType(std::nullptr_t null);

	Semantic::SemanticErrorType resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	using Type::equals;
	virtual bool equals(const Type *other) const override { return other->equalsDerived(this); };
	virtual bool equals(const TypeResult &) const override;
	std::string toCode() const override;

	static thread_local int val;

protected:
	using Type::equalsDerived;
	virtual bool equalsDerived(const PrimitiveType *other) const override { return type == other->type; }
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
	explicit NameType(Name const& other);
	explicit NameType(TypeDeclaration *decl, std::string name);
	std::string toCode() const override;

	std::string flatten() const;
	Semantic::SemanticErrorType resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	TypeDeclaration *getDeclaration();

	using Type::equals;
	virtual bool equals(const Type *other) const override { return other->equalsDerived(this); };
	virtual bool equals(const TypeResult &) const override;

protected:
	using Type::equalsDerived;
	virtual bool equalsDerived(const NameType *other) const override { return declaration == other->declaration; }

protected:
	std::vector<std::string> ids;
public:
	TypeDeclaration *declaration = nullptr;
};

} //namespace AST
