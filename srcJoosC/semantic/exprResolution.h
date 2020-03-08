#pragma once

#include "ast/type.h"
#include <string>

namespace AST
{

class TypeDeclaration;

enum class TypePrimitive
{
	Boolean,
	Byte,
	Short,
	Int,
	Char,
	Void,
	Null,
	Max
};
static_assert( (int)TypePrimitive::Boolean	== (int)PrimitiveType::Variant::Boolean);
static_assert( (int)TypePrimitive::Byte   	== (int)PrimitiveType::Variant::Byte);
static_assert( (int)TypePrimitive::Short  	== (int)PrimitiveType::Variant::Short);
static_assert( (int)TypePrimitive::Int    	== (int)PrimitiveType::Variant::Int);
static_assert( (int)TypePrimitive::Char   	== (int)PrimitiveType::Variant::Char);
static_assert( (int)TypePrimitive::Void   	== (int)PrimitiveType::Variant::Void);
static_assert( (int)TypePrimitive::Null   	== (int)PrimitiveType::Variant::Null);

struct TypeResult {
	bool isPrimitive;
	bool isArray;
	bool isFinal;
	TypePrimitive primitiveType;
	TypeDeclaration *userDefinedType;

	TypeResult(Type const& type, bool final);
	TypeResult(bool arr, TypePrimitive primT, bool final)
		: isPrimitive(true), isArray(arr), isFinal(final), primitiveType(primT), userDefinedType(nullptr) {}
	// is non array numeric type
	[[gnu::pure]]
	bool isNum() const;
	// is array or non array numeric type
	[[gnu::pure]]
	bool isNumOrArrayNum() const;
	// is java string
	[[gnu::pure]]
	bool isJavaString() const;
	// is non array primitive type
	[[gnu::pure]]
	bool isPrimitiveType(TypePrimitive primitive) const;
	[[gnu::pure]]
	bool isReferenceType() const;
	bool operator==(const TypeResult&other) const;

	// assignability (JLS 5), used in more than one place
	bool canAssignToMyType(const TypeResult &other) const ;
};

struct TypeDeduceError {
	bool hasError;
	std::string function;
};


} //namespace AST

