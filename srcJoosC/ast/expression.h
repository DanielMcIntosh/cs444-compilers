#pragma once

#include "ast/node.h"

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
class Name;

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
	//virtual Semantic::SemanticErrorType resolve(Semantic::Scope const& scope);
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
	//Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
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
protected:
	std::unique_ptr<Type> type;
	std::vector<std::unique_ptr<Expression>> args;
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
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
protected:
	std::unique_ptr<Expression> object;
	std::string member;
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
protected:
	std::variant<unsigned int, bool, char, std::string, std::nullptr_t > value;
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
protected:
	// nullable.
	// Expression when non-static method, Type when static method, Name only before expression resolution
	std::variant<std::unique_ptr<Expression>, std::unique_ptr<Type>, std::unique_ptr<Name>> source;
	std::string methodName;
	std::vector<std::unique_ptr<Expression>> args;
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
	explicit NameExpression(Name&& other);
	std::string toCode() const override;
protected:
	std::vector<std::string> prefix;
	std::string id;
};

//////////////////////////////////////////////////////////////////////////////
//
// This
//
//////////////////////////////////////////////////////////////////////////////

// mostly a dummy class - the equivalent of the Literal class, but for a "this" expression
class This: public Expression
{
public:
	static std::unique_ptr<This> create(const Parse::Tree *ptNode);
	explicit This(const Parse::TThis2 *ptNode);

	std::string toCode() const override;
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
