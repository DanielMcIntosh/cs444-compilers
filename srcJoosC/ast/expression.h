#pragma once

#include "ast/node.h"
#include "ast/type.h"

#include <variant>


namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
	class Scope;
}

namespace AST
{

class TypeDeclaration;
class Type;
class NameType;
class Name;
class VariableDeclaration;
class FieldDeclaration;
class MethodDeclaration;
class ConstructorDeclaration;



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
	TypePrimitive primitiveType;
	TypeDeclaration *userDefinedType;

	TypeResult(Type const& type);
	TypeResult(bool arr, TypePrimitive primT)
		: isPrimitive(true), isArray(arr), primitiveType(primT), userDefinedType(nullptr) {}
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
	bool canAssignToMe(const TypeResult &other) const ;
};

struct TypeDeduceError {
	bool hasError;
	std::string function;
};

//////////////////////////////////////////////////////////////////////////////
//
// Expression
//
//////////////////////////////////////////////////////////////////////////////

class Expression: public Node
{
public:
	static std::unique_ptr<Expression> create(const Parse::Tree *ptNode);

	virtual Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);
	virtual Semantic::SemanticErrorType resolve(Semantic::Scope const& scope);
	Semantic::SemanticErrorType resolveAndDeduce(Semantic::Scope const& scope);

	TypeResult typeResult = TypeResult(false, TypePrimitive::Max);
	virtual Semantic::SemanticErrorType deduceType() = 0;

	static void resetError();
	static thread_local TypeDeduceError gError;
protected:

};

//////////////////////////////////////////////////////////////////////////////
//
// ArrayAccess
//
//////////////////////////////////////////////////////////////////////////////

class ArrayAccess: public Expression
{
public:
	static std::unique_ptr<ArrayAccess> create(const Parse::Tree *ptNode);
	explicit ArrayAccess(const Parse::TArrayAccess *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;
protected:
	std::unique_ptr<Expression> array;
	std::unique_ptr<Expression> index;
};

//////////////////////////////////////////////////////////////////////////////
//
// ArrayCreationExpression
//
//////////////////////////////////////////////////////////////////////////////

class ArrayCreationExpression: public Expression
{
public:
	static std::unique_ptr<ArrayCreationExpression> create(const Parse::Tree *ptNode);
	explicit ArrayCreationExpression(const Parse::TArrayCreationExpression *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;
protected:
	// IMPORTANT: during construction, we have to change type->isArray to true
	std::unique_ptr<Type> type;
	std::unique_ptr<Expression> size;
};

//////////////////////////////////////////////////////////////////////////////
//
// AssignmentExpression
//
//////////////////////////////////////////////////////////////////////////////

class AssignmentExpression: public Expression
{
public:
	static std::unique_ptr<AssignmentExpression> create(const Parse::Tree *ptNode);
	explicit AssignmentExpression(const Parse::TAssignment *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

protected:
	std::unique_ptr<Expression> lhs;
	std::unique_ptr<Expression> rhs;
};

//////////////////////////////////////////////////////////////////////////////
//
// BinaryExpression
//
//////////////////////////////////////////////////////////////////////////////

class BinaryExpression: public Expression
{
public:
	static std::unique_ptr<BinaryExpression> create(const Parse::Tree *ptNode);

	explicit BinaryExpression(const Parse::TAdditiveExpression *ptNode);
	explicit BinaryExpression(const Parse::TAndExpression *ptNode);
	explicit BinaryExpression(const Parse::TConditionalAndExpression *ptNode);
	explicit BinaryExpression(const Parse::TConditionalOrExpression *ptNode);
	explicit BinaryExpression(const Parse::TEqualityExpression *ptNode);
	explicit BinaryExpression(const Parse::TInclusiveOrExpression *ptNode);
	explicit BinaryExpression(const Parse::TMultiplicativeExpression *ptNode);
	explicit BinaryExpression(const Parse::TRelationalExpression *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	enum class Variant {
		Add,		// Accept Int, Return Int
		Sub,
		Mult,
		Div,
		Mod,
		Lt,			// Accept Int, Return Bool
		Gt,
		LtEq,
		GtEq,
		InstanceOf, // Accept Expr, Type, Return Bool
		Eq,			// Accpet Int/Bool, Return Bool
		NEq,
		EagerAnd,	// Accept Bool, Return Bool
		EagerOr,
		LazyAnd,
		LazyOr,
		Max
	};
protected:
 	Variant op;

	std::unique_ptr<Expression> lhs;
	// instanceof has a rhs that's a ReferenceType instead of an Expression
	std::variant<std::unique_ptr<Expression>, std::unique_ptr<Type>> rhs;
};

std::string operator+(std::string str, BinaryExpression::Variant op);
std::string operator+=(std::string& str, BinaryExpression::Variant op);
std::ostream& operator<<(std::ostream& os, BinaryExpression::Variant op);
// not entirely sold on doing things this way. The alternative is a lot of casting in the .cpp file.
constexpr inline BinaryExpression::Variant operator+(BinaryExpression::Variant a, int b) { return (BinaryExpression::Variant)((int)a + b); }

//////////////////////////////////////////////////////////////////////////////
//
// CastExpression
//
//////////////////////////////////////////////////////////////////////////////

class CastExpression: public Expression
{
public:
	static std::unique_ptr<CastExpression> create(const Parse::Tree *ptNode);
	explicit CastExpression(const Parse::TCastExpression *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;
protected:
	std::unique_ptr<Type> type;
	std::unique_ptr<Expression> rhs;
};

//////////////////////////////////////////////////////////////////////////////
//
// ClassInstanceCreationExpression
//
//////////////////////////////////////////////////////////////////////////////

class ClassInstanceCreationExpression: public Expression
{
public:
	static std::unique_ptr<ClassInstanceCreationExpression> create(const Parse::Tree *ptNode);
	explicit ClassInstanceCreationExpression(const Parse::TClassInstanceCreationExpression *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;
protected:
	std::unique_ptr<NameType> type;
	std::vector<std::unique_ptr<Expression>> args;
	friend class ConstructorDeclaration;

	const ConstructorDeclaration *declaration;
};

//////////////////////////////////////////////////////////////////////////////
//
// FieldAccess
//
//////////////////////////////////////////////////////////////////////////////

class FieldAccess: public Expression
{
public:
	static std::unique_ptr<FieldAccess> create(const Parse::Tree *ptNode);
	explicit FieldAccess(const Parse::TFieldAccess *ptNode);
	explicit FieldAccess(std::unique_ptr<Expression> object, std::string field);
	explicit FieldAccess(std::unique_ptr<NameType> type, std::string field);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	bool isStaticAccessor() const;
protected:
	std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>> source;
	std::string member;
	friend class FieldDeclaration;

	const FieldDeclaration *decl;
};

//////////////////////////////////////////////////////////////////////////////
//
// Literal
//
//////////////////////////////////////////////////////////////////////////////

class Literal: public Expression
{
public:
	static std::unique_ptr<Literal> create(const Parse::Tree *ptNode);
	explicit Literal(const Parse::TLiteral *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType deduceType() override;
	static bool isJavaString(TypeDeclaration *decl);
protected:
	std::variant<unsigned int, bool, char, std::string, std::nullptr_t > value;
	static thread_local TypeDeclaration *stringDecl;
};

//////////////////////////////////////////////////////////////////////////////
//
// LocalVariableExpression
//
//////////////////////////////////////////////////////////////////////////////

class LocalVariableExpression: public Expression
{
public:
	static std::unique_ptr<LocalVariableExpression> create(const Parse::Tree *ptNode);
	explicit LocalVariableExpression(const Parse::TThis2 *ptNode);
	explicit LocalVariableExpression(std::string identifier);
	std::string toCode() const override;
protected:
	friend class NameExpression;
	friend class Name;

public:
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;
protected:
	std::string id;
	const VariableDeclaration *declaration;
};

//////////////////////////////////////////////////////////////////////////////
//
// MethodInvocation
//
//////////////////////////////////////////////////////////////////////////////

class MethodInvocation: public Expression
{
public:
	static std::unique_ptr<MethodInvocation> create(const Parse::Tree *ptNode);
	explicit MethodInvocation(const Parse::TMethodInvocation *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	bool isStaticCall() const;
private:
	Semantic::SemanticErrorType disambiguateSource(Semantic::Scope const& scope);
protected:
	// nullable prior to expression resolution
	// Expression when non-static method, NameType when static method, Name only before expression resolution
	std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>, std::unique_ptr<Name>> source;
	std::string methodName;
	std::vector<std::unique_ptr<Expression>> args;
	friend class MethodDeclaration;

	const MethodDeclaration *declaration;
};

//////////////////////////////////////////////////////////////////////////////
//
// NameExpression
//
//////////////////////////////////////////////////////////////////////////////

class NameExpression: public Expression
{
public:
	static std::unique_ptr<NameExpression> create(const Parse::Tree *ptNode);
	explicit NameExpression(std::unique_ptr<Name> other);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;
protected:
	std::unique_ptr<Name> unresolved;
	std::unique_ptr<Expression> converted;
};

//////////////////////////////////////////////////////////////////////////////
//
// UnaryExpression
//
//////////////////////////////////////////////////////////////////////////////

class UnaryExpression: public Expression
{
public:
	static std::unique_ptr<UnaryExpression> create(const Parse::Tree *ptNode);
	explicit UnaryExpression(const Parse::TUnaryExpression *ptNode);
	explicit UnaryExpression(const Parse::TUnaryExpressionNotPlusMinus *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;
protected:
	enum class Variant
	{
		Minus,
		Bang,
		Max
	} op;

	std::unique_ptr<Expression> expr;

	friend std::string operator+(std::string, UnaryExpression::Variant);
	friend std::string operator+=(std::string&, UnaryExpression::Variant);
	friend std::ostream& operator<<(std::ostream&, UnaryExpression::Variant);
};

std::string operator+(std::string str, UnaryExpression::Variant type);
std::string operator+=(std::string& str, UnaryExpression::Variant type);
std::ostream& operator<<(std::ostream& os, UnaryExpression::Variant type);

} //namespace AST
