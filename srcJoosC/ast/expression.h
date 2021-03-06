#pragma once

#include "ast/node.h"
#include "ast/type.h"
#include "semantic/exprResolution.h"
#include "semantic/staticAnalysis.h"

#include <variant>
#include <optional>

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
	class Scope;
}

namespace CodeGen {
  class SContext;
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

//////////////////////////////////////////////////////////////////////////////
//
// Expression
//
//////////////////////////////////////////////////////////////////////////////

class Expression: public Node
{
public:
	static std::unique_ptr<Expression> create(const Parse::Tree *ptNode);
    virtual Expression* clone() const = 0;

	virtual Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);

	Semantic::SemanticErrorType resolveAndDeduce(Semantic::Scope const& scope);
	virtual Semantic::SemanticErrorType disambiguate(Semantic::Scope const& scope);
	virtual Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope);
	virtual Semantic::SemanticErrorType resolve(Semantic::Scope const& scope);
	virtual Semantic::SemanticErrorType deduceType() = 0;
	bool hasBeenResolved();

	TypeResult typeResult = TypeResult(false, TypePrimitive::Max, true);

	static void resetError();
	static thread_local TypeDeduceError gError;

	// a4

	virtual ConstExpr tryEval();

	// a5

	virtual void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) = 0;
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
	explicit ArrayAccess(std::unique_ptr<Expression> arr, std::unique_ptr<Expression> ind);
	ArrayAccess* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

public:
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
	explicit ArrayCreationExpression(std::unique_ptr<Type> t, std::unique_ptr<Expression> sz);
	ArrayCreationExpression* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

public:
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
	explicit AssignmentExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
	AssignmentExpression* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

public:
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
	enum class Variant;
	static std::unique_ptr<BinaryExpression> create(const Parse::Tree *ptNode);

	explicit BinaryExpression(const Parse::TAdditiveExpression *ptNode);
	explicit BinaryExpression(const Parse::TAndExpression *ptNode);
	explicit BinaryExpression(const Parse::TConditionalAndExpression *ptNode);
	explicit BinaryExpression(const Parse::TConditionalOrExpression *ptNode);
	explicit BinaryExpression(const Parse::TEqualityExpression *ptNode);
	explicit BinaryExpression(const Parse::TInclusiveOrExpression *ptNode);
	explicit BinaryExpression(const Parse::TMultiplicativeExpression *ptNode);
	explicit BinaryExpression(const Parse::TRelationalExpression *ptNode);
	explicit BinaryExpression(Variant opVar, std::unique_ptr<Expression> left, std::variant<std::unique_ptr<Expression>, std::unique_ptr<Type>> right);
	BinaryExpression* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope) override;
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

	// a4

	ConstExpr tryEval() override;

  // a5
  void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;
public:
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
	explicit CastExpression(std::unique_ptr<Type> t, std::unique_ptr<Expression> expr);
	CastExpression* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

  // a5
  void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

public:
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
	explicit ClassInstanceCreationExpression(std::unique_ptr<NameType> t, std::vector<std::unique_ptr<Expression>> arguments);
	ClassInstanceCreationExpression* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

  // a5
  void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

public:
	std::unique_ptr<NameType> type;
	std::vector<std::unique_ptr<Expression>> args;
	friend class ConstructorDeclaration;

protected:
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
	explicit FieldAccess(std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>> src, std::string field);
	FieldAccess* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	bool isStaticAccessor() const;

	// a5
	void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

public:
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
	explicit Literal(std::variant<unsigned int, bool, char, std::string, std::nullptr_t > val);
	Literal* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;
	Semantic::SemanticErrorType deduceType() override;
	static bool isJavaString(TypeDeclaration *decl);

	// a4
	ConstExpr tryEval() override;

	// a5
	void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

public:
	std::variant<unsigned int, bool, char, std::string, std::nullptr_t > value;
protected:
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
	LocalVariableExpression* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	// a5
	void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

public:
	std::string id;
	const VariableDeclaration *declaration;
	friend class NameExpression;
	friend class Name;
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
	explicit MethodInvocation(std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>, std::unique_ptr<Name>> src, std::string name, std::vector<std::unique_ptr<Expression>> arguments);
	MethodInvocation* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	Semantic::SemanticErrorType disambiguate(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	// a5
	void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

	bool isStaticCall() const;
	bool isDisambiguated() const;

public:
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
	explicit NameExpression(std::unique_ptr<Name> name, std::unique_ptr<Expression> conv = nullptr);
	NameExpression* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	Semantic::SemanticErrorType disambiguate(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType resolve(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	// a5
	void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

public:
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
	enum class Variant;

	static std::unique_ptr<UnaryExpression> create(const Parse::Tree *ptNode);
	explicit UnaryExpression(const Parse::TUnaryExpression *ptNode);
	explicit UnaryExpression(const Parse::TUnaryExpressionNotPlusMinus *ptNode);
	explicit UnaryExpression(Variant opVar, std::unique_ptr<Expression> expression);
	UnaryExpression* clone() const override;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	Semantic::SemanticErrorType deduceChildTypes(Semantic::Scope const& scope) override;
	Semantic::SemanticErrorType deduceType() override;

	// a4
	ConstExpr tryEval() override;

	// a5
	void codeGenerate(CodeGen::SContext *ctx, bool returnLValue = false) override;

public:
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
