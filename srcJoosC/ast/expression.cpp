#include "ast/expression.h"
#include "ast/name.h"
#include "ast/type.h"
#include "ast/nodeList.h"
#include "ast/typeDeclaration.h"
#include "ast/variableDeclaration.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include "semantic/scope.h"
#include <memory>
#include <optional>
#include <ostream>

using Semantic::SemanticErrorType;
namespace AST
{
thread_local TypeDeclaration *Literal::stringDecl;
thread_local TypeDeduceError Expression::gError;

void Expression::resetError() {
	gError.hasError = false;
	gError.function.clear();
}

//////////////////////////////////////////////////////////////////////////////
//
// ResolveTypes
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType Expression::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *source)
{
	return SemanticErrorType::None;
}

SemanticErrorType ArrayAccess::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (auto error = array->resolveTypes(semantic, enclosingClass);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (auto error = index->resolveTypes(semantic, enclosingClass);
		error != SemanticErrorType::None)
	{
		return error;
	}
	return SemanticErrorType::None;
}
SemanticErrorType ArrayCreationExpression::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (auto error = type->resolve(semantic, enclosingClass);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (auto error = size->resolveTypes(semantic, enclosingClass);
		error != SemanticErrorType::None)
	{
		return error;
	}
	return SemanticErrorType::None;
}
SemanticErrorType AssignmentExpression::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (auto error = lhs->resolveTypes(semantic, enclosingClass);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (auto error = rhs->resolveTypes(semantic, enclosingClass);
		error != SemanticErrorType::None)
	{
		return error;
	}
	return SemanticErrorType::None;
}
SemanticErrorType BinaryExpression::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (auto error = lhs->resolveTypes(semantic, enclosingClass);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (op != Variant::InstanceOf)
	{
		return std::get<std::unique_ptr<Expression>>(rhs)->resolveTypes(semantic, enclosingClass);
	} else
	{
		return std::get<std::unique_ptr<Type>>(rhs)->resolve(semantic, enclosingClass);
	}
}
SemanticErrorType CastExpression::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (auto error = type->resolve(semantic, enclosingClass);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (auto error = rhs->resolveTypes(semantic, enclosingClass);
		error != SemanticErrorType::None)
	{
		return error;
	}
	return SemanticErrorType::None;
}
SemanticErrorType
ClassInstanceCreationExpression::resolveTypes(Semantic::SemanticDB const &semantic, TypeDeclaration *enclosingClass) {
	if (auto error = type->resolve(semantic, enclosingClass);
		error != SemanticErrorType::None)
	{
		return error;
	}
	for (auto &expr : args) {
		if (auto error = expr->resolveTypes(semantic, enclosingClass);
			error != SemanticErrorType::None)
		{
			return error;
		}
	}
	return SemanticErrorType::None;
}

SemanticErrorType FieldAccess::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return std::visit(visitor{
		[&semantic, &enclosingClass](std::unique_ptr<Expression> &expr) { return expr->resolveTypes(semantic, enclosingClass); },
		[&semantic, &enclosingClass](std::unique_ptr<NameType> &type) { return type->resolve(semantic, enclosingClass); }
	}, source);
}

SemanticErrorType Literal::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (enclosingClass->fqn == "java.lang.String")
	{
		Literal::stringDecl = enclosingClass;
	}
	return SemanticErrorType::None;
}

SemanticErrorType MethodInvocation::resolveTypes(Semantic::SemanticDB const &semantic, TypeDeclaration *enclosingClass)
{
	{
		SemanticErrorType error = std::visit(visitor {
			[&semantic, &enclosingClass](std::unique_ptr<Expression> &src) {
				return src ? src->resolveTypes(semantic, enclosingClass)	: SemanticErrorType::None;	},
			[&semantic, &enclosingClass](std::unique_ptr<NameType> &src) {
				return src ? src->resolve(semantic, enclosingClass) 		: SemanticErrorType::None;	},
			[&semantic, &enclosingClass](std::unique_ptr<Name> &src) {
				return src ? src->resolveTypes(semantic, enclosingClass)	: SemanticErrorType::None;	}
		}, source);
		if (error != SemanticErrorType::None)
		{
			return error;
		}
	}
	for (auto& arg : args) {
		if (auto error = arg->resolveTypes(semantic, enclosingClass);
			error != SemanticErrorType::None)
		{
			return error;
		}
	}
	return SemanticErrorType::None;
}

SemanticErrorType NameExpression::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return unresolved->resolveTypes(semantic, enclosingClass);
}

SemanticErrorType UnaryExpression::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return expr->resolveTypes(semantic, enclosingClass);
}

//////////////////////////////////////////////////////////////////////////////
//
// resolveAndDeduce
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType Expression::resolveAndDeduce(Semantic::Scope const& scope)
{
	if (auto error = resolve(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	return deduceType();
}

TypeResult::TypeResult(Type const& type)
  : isPrimitive(type.nodeType == NodeType::PrimitiveType),
	isArray(type.isArray)
{
	if (isPrimitive)
	{
		PrimitiveType const& primitive = static_cast<PrimitiveType const&>(type);
		primitiveType = (TypePrimitive)(primitive.type);
		userDefinedType = nullptr;
	} else
	{
		NameType const& name = static_cast<NameType const&>(type);
		primitiveType = TypePrimitive::Max;
		userDefinedType = name.declaration;
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// deduceType
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType CastExpression::deduceType()
{
	// first allow all numeric casts
	auto lhs = TypeResult(*type);
	typeResult = lhs;
	if (lhs.isNum() && rhs->typeResult.isNum())
		OK();

	// then try assignability
	if (lhs.canAssignToMe(rhs->typeResult))
		OK();
	else if (rhs->typeResult.canAssignToMe(lhs))
		OK();

	GOFAIL(); // to print error
	fail:
	return SemanticErrorType::AssignableType;
}

SemanticErrorType ClassInstanceCreationExpression::deduceType()
{
	typeResult = TypeResult(*type);
	return SemanticErrorType::None;
}

SemanticErrorType FieldAccess::deduceType()
{
	typeResult = TypeResult(*(decl->varDecl->type));
	return SemanticErrorType::None;
}

SemanticErrorType Literal::deduceType() {
	typeResult = std::visit(visitor{
					[](unsigned int) { return TypeResult{false, TypePrimitive::Int}; },
					[](bool) { return TypeResult{false, TypePrimitive::Boolean}; },
					[](char) { return TypeResult{false, TypePrimitive::Char}; },
					[](std::string&) {
						return !gStandAloneMode ? TypeResult(*(Literal::stringDecl->asType())) : TypeResult(); },
					[](std::nullptr_t) { return TypeResult{false, TypePrimitive::Null}; }
	}, value);
	return SemanticErrorType::None;
}

Semantic::SemanticErrorType ArrayAccess::deduceType() {
	// array must be array type
	if (!array->typeResult.isArray)
		GOFAIL();

	// index must be numerical type
	if (!index->typeResult.isNum())
		GOFAIL();

	// resulting type is the type of the array with array dropped
	typeResult = array->typeResult;
	typeResult.isArray = false;

	OK();

	fail:
	return Semantic::SemanticErrorType::TypeCheck;
}

SemanticErrorType ArrayCreationExpression::deduceType() {
	// size must be numerical type
	if (!size->typeResult.isNum())
		GOFAIL();

	// result will be of array type
	typeResult.isArray = true;
	if (type->nodeType == NodeType::PrimitiveType) {
		auto item = (PrimitiveType*)type.get();
		// array of primitive value
		typeResult.isPrimitive = true;
		typeResult.primitiveType = static_cast<TypePrimitive>(item->type);
	} else if (type->nodeType == NodeType::NameType) {
		// array of objects of a user-defined type
		auto item = (NameType*)type.get();
		typeResult.isPrimitive = false;
		typeResult.userDefinedType = item->declaration;
	} else {
		ASSERT(false);
	}

	OK();

	fail:
	return SemanticErrorType::TypeCheck;
}

SemanticErrorType AssignmentExpression::deduceType() {
	typeResult = rhs->typeResult;
	if (lhs->typeResult.canAssignToMe(rhs->typeResult))
		OK();
	GOFAIL(); // to print error
	fail:
	return Semantic::SemanticErrorType::TypeCheck;
}

bool IsArithmeticOp(BinaryExpression::Variant op) {
	return (op == BinaryExpression::Variant::Add ||
	        op == BinaryExpression::Variant::Sub ||
	        op == BinaryExpression::Variant::Mult ||
	        op == BinaryExpression::Variant::Div ||
	        op == BinaryExpression::Variant::Mod);
}

bool IsNumCompare(BinaryExpression::Variant op) {
	return (op == BinaryExpression::Variant::Lt ||
	        op == BinaryExpression::Variant::Gt ||
	        op == BinaryExpression::Variant::LtEq ||
	        op == BinaryExpression::Variant::GtEq);
}

bool IsBooleanOp(BinaryExpression::Variant op) {
	return (op == BinaryExpression::Variant::EagerAnd ||
	        op == BinaryExpression::Variant::EagerOr ||
	        op == BinaryExpression::Variant::LazyAnd ||
	        op == BinaryExpression::Variant::LazyOr);
}

std::optional<TypeResult> BinExprHelper(Expression* lhs, Expression* rhs,
                                           BinaryExpression::Variant op) {
	bool bothNum = lhs->typeResult.isNum() && rhs->typeResult.isNum();
	bool bothBool = lhs->typeResult.isPrimitiveType(TypePrimitive::Boolean) &&
	                rhs->typeResult.isPrimitiveType(TypePrimitive::Boolean);

	if (bothNum && IsArithmeticOp(op)) {
		return TypeResult(false, TypePrimitive::Int);
	}

	if (bothNum && IsNumCompare(op)) {
		return TypeResult(false, TypePrimitive::Boolean);
	}

	if (bothBool && IsBooleanOp(op)) {
		return TypeResult(false, TypePrimitive::Boolean);
	}

	if ((bothBool || bothNum) &&
	    (op == BinaryExpression::Variant::Eq || op == BinaryExpression::Variant::NEq)) {
		return TypeResult(false, TypePrimitive::Boolean);
	}

	// At this point, only string concatenation remains
	if (lhs->typeResult.isJavaString() && !rhs->typeResult.isPrimitiveType(TypePrimitive::Void))
		return lhs->typeResult;
	else if (rhs->typeResult.isJavaString() && !lhs->typeResult.isPrimitiveType(TypePrimitive::Void))
		return rhs->typeResult;

	return std::nullopt;
}

SemanticErrorType BinaryExpression::deduceType() {
	SemanticErrorType err = SemanticErrorType::None;
	std::visit(visitor {
					[&](std::unique_ptr<Expression> &rexpr) {
						auto res = BinExprHelper(lhs.get(), rexpr.get(), op);
						if (res)
							typeResult = *res;
						else
							err = SemanticErrorType::TypeCheck;

					},
					[&](std::unique_ptr<Type> &type) {
						if (lhs->typeResult.isPrimitive ||
						    lhs->typeResult.isArray ||
						    op != BinaryExpression::Variant::InstanceOf) {
							err = SemanticErrorType::TypeCheck;
							return;
						}

						typeResult = TypeResult(false, TypePrimitive::Boolean);
					}
	}, rhs);

	GOFAIL_IF_ERR(err);
	OK();

	fail:
	return err;
}

Semantic::SemanticErrorType LocalVariableExpression::deduceType()
{
	typeResult = TypeResult(*(declaration->type));
	return SemanticErrorType::None;
}
Semantic::SemanticErrorType MethodInvocation::deduceType()
{
	// look inside the methods of the name, find the method with matching param types, then fill in declaration
	typeResult = TypeResult(*(declaration->returnType));
	return SemanticErrorType::None;
}
Semantic::SemanticErrorType NameExpression::deduceType() {
	typeResult = converted->typeResult;
	return SemanticErrorType::None;
}
Semantic::SemanticErrorType UnaryExpression::deduceType() {
	auto &t = expr->typeResult;
	if (op == Variant::Bang) {
		if (!t.isPrimitiveType(TypePrimitive::Boolean)) {
			// expected bool
			return SemanticErrorType::TypeCheck;
		}
	} else if (op == Variant::Minus) {
		if (!t.isNum()) {
			// expected numeric
			return SemanticErrorType::TypeCheck;
		}
	} else {
		ASSERT(false);
	}
	typeResult = t;
	return SemanticErrorType::None;
}

//////////////////////////////////////////////////////////////////////////////
//
// resolve
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType Expression::resolve(Semantic::Scope const& scope)
{
	return SemanticErrorType::None;
}

SemanticErrorType ArrayAccess::resolve(Semantic::Scope const& scope)
{
	if (auto error = array->resolveAndDeduce(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (auto error = index->resolveAndDeduce(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	return SemanticErrorType::None;
}
SemanticErrorType ArrayCreationExpression::resolve(Semantic::Scope const& scope)
{
	return size->resolveAndDeduce(scope);
}
SemanticErrorType AssignmentExpression::resolve(Semantic::Scope const& scope)
{
	if (auto error = lhs->resolveAndDeduce(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (auto error = rhs->resolveAndDeduce(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	return SemanticErrorType::None;
}
SemanticErrorType BinaryExpression::resolve(Semantic::Scope const& scope)
{
	if (auto error = lhs->resolveAndDeduce(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (op != Variant::InstanceOf)
	{
		return std::get<std::unique_ptr<Expression>>(rhs)->resolveAndDeduce(scope);
	}
	return SemanticErrorType::None;
}
SemanticErrorType CastExpression::resolve(Semantic::Scope const& scope)
{
	return rhs->resolveAndDeduce(scope);
}
SemanticErrorType ClassInstanceCreationExpression::resolve(Semantic::Scope const& scope)
{
	for (auto &expr : args) {
		if (auto error = expr->resolveAndDeduce(scope);
			error != SemanticErrorType::None)
		{
			return error;
		}
	}
	declaration = type->getDeclaration()->findConstructor(this);
	return declaration == nullptr ? SemanticErrorType::DeclarationNotFound : SemanticErrorType::None;
}

SemanticErrorType FieldAccess::resolve(Semantic::Scope const& scope)
{

	SemanticErrorType ret = SemanticErrorType::None;
	TypeResult sourceDecl = std::visit(visitor{
		[&ret, &scope](std::unique_ptr<Expression> &expr) {
			ret = expr->resolveAndDeduce(scope);
			return expr->typeResult;
		},
		[](std::unique_ptr<NameType> &t) {
			return TypeResult(*t);
		}
	}, source);
	/* TODO: need to create declaration for length field
	if (sourceDecl.isArray) {
		if (member != "length") return SemanticErrorType::ExprResolution;
		return SemanticErrorType::None;
	} */
	if (sourceDecl.isPrimitive) return SemanticErrorType::PrimativeNotExpected;
	decl = sourceDecl.userDefinedType->findField(this);
	return decl == nullptr ? SemanticErrorType::DeclarationNotFound : SemanticErrorType::None;
}

SemanticErrorType LocalVariableExpression::resolve(Semantic::Scope const& scope)
{
	declaration = scope.findDecl(id);
	return declaration == nullptr ? SemanticErrorType::LocalVariableDNE : SemanticErrorType::None;
}

SemanticErrorType MethodInvocation::disambiguateSource(Semantic::Scope const& scope)
{
	// if no source, make the implicit source explicit.
	if (std::visit([](auto &src) { return src == nullptr; }, source))
	{
		// if we're in a non-static method, resolve(this) will succeed.
		if (auto thisExpr = std::make_unique<LocalVariableExpression>("this");
			thisExpr->resolve(scope) == SemanticErrorType::None)
		{
			// implicit TypeName is not permitted in joos non-static methods. We can safely assume the source is thisExpr.
			// https://www.student.cs.uwaterloo.ca/~cs444/features/implicitthisclassforstaticmethods.html
			source = std::move(thisExpr);
		}
		else
		{
			source = scope._enclosingClass->asType();
		}
	}
	else if (std::holds_alternative<std::unique_ptr<Name>>(source))
	{
		auto &src = std::get<std::unique_ptr<Name>>(source);
		if (auto error = src->disambiguate(scope);
			error != SemanticErrorType::None)
		{
			return error;
		}
		auto error = std::visit(
			[this](auto &converted) {
				if (converted == nullptr)
					return SemanticErrorType::DisambiguiationFailed;
				auto temp = std::move(converted);
				source = std::move(temp);
				return SemanticErrorType::None;
			}, src->converted);
		if (error != SemanticErrorType::None)
		{
			return error;
		}
	}
	return SemanticErrorType::None;
}

SemanticErrorType MethodInvocation::resolve(Semantic::Scope const& scope)
{
	if (auto error = disambiguateSource(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}

	{
		SemanticErrorType error = std::visit(visitor {
			[&scope](std::unique_ptr<Expression> &src)	{	return src->resolveAndDeduce(scope); },
			[&scope](std::unique_ptr<NameType> &src) 	{	return SemanticErrorType::None;	},
			[&scope](std::unique_ptr<Name> &src) -> SemanticErrorType {	assert(false);	}
		}, source);
		if (error != SemanticErrorType::None)
		{
			return error;
		}
	}

	for (auto& arg : args) {
		if (auto error = arg->resolveAndDeduce(scope);
			error != SemanticErrorType::None)
		{
			return error;
		}
	}

	// find method declaration
	TypeResult sourceDecl = std::visit(visitor{
		[](std::unique_ptr<Expression> &src) { return src->typeResult; },
		[](std::unique_ptr<NameType> &src)   { return TypeResult(*src); },
		[](std::unique_ptr<Name> &)          { assert(false); return TypeResult(); }
	}, source);
	if (sourceDecl.isPrimitive) return SemanticErrorType::PrimativeNotExpected;
	declaration = sourceDecl.userDefinedType->findMethod(this);
	return declaration == nullptr ? SemanticErrorType::DeclarationNotFound : SemanticErrorType::None;
}

SemanticErrorType NameExpression::resolve(Semantic::Scope const& scope)
{
	if (auto error = unresolved->disambiguate(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	converted = std::visit(visitor {
		[](std::unique_ptr<Expression> &expr)							{ return std::move(expr); },
		[](std::unique_ptr<NameType> &t) -> std::unique_ptr<Expression> { return nullptr; }
	}, unresolved->converted);
	if (converted == nullptr)
	{
		return SemanticErrorType::DisambiguiationFailed;
	}
	return converted->resolveAndDeduce(scope);
}

SemanticErrorType UnaryExpression::resolve(Semantic::Scope const& scope)
{
	return expr->resolveAndDeduce(scope);
}

//////////////////////////////////////////////////////////////////////////////
//
// create functions
//
//////////////////////////////////////////////////////////////////////////////

// static
std::unique_ptr<Expression> Expression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return Expression::create(ptNode->children[0]);
	}

	switch(ptNode->type) {
		case Parse::NonTerminalType::Assignment:
			return AssignmentExpression::create(ptNode);
		case Parse::NonTerminalType::AdditiveExpression:
		case Parse::NonTerminalType::AndExpression:
		case Parse::NonTerminalType::ConditionalAndExpression:
		case Parse::NonTerminalType::ConditionalOrExpression:
		case Parse::NonTerminalType::EqualityExpression:
		case Parse::NonTerminalType::InclusiveOrExpression:
		case Parse::NonTerminalType::MultiplicativeExpression:
		case Parse::NonTerminalType::RelationalExpression:
			return BinaryExpression::create(ptNode);
		case Parse::NonTerminalType::CastExpression:
			return CastExpression::create(ptNode);
		case Parse::NonTerminalType::Name:
			return NameExpression::create(ptNode);
		case Parse::NonTerminalType::UnaryExpression:
		case Parse::NonTerminalType::UnaryExpressionNotPlusMinus:
			return UnaryExpression::create(ptNode);
		case Parse::NonTerminalType::ArrayAccess:
			return ArrayAccess::create(ptNode);
		case Parse::NonTerminalType::ArrayCreationExpression:
			return ArrayCreationExpression::create(ptNode);
		case Parse::NonTerminalType::ClassInstanceCreationExpression:
			return ClassInstanceCreationExpression::create(ptNode);
		case Parse::NonTerminalType::FieldAccess:
			return FieldAccess::create(ptNode);
		case Parse::NonTerminalType::Literal:
			return Literal::create(ptNode);
		case Parse::NonTerminalType::MethodInvocation:
			return MethodInvocation::create(ptNode);
		case Parse::NonTerminalType::This2:
			return LocalVariableExpression::create(ptNode);
		default:
			FAILED("inappropriate PT type for Expression: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<ArrayAccess> ArrayAccess::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::ArrayAccess:
			return std::make_unique<ArrayAccess>(static_cast<const Parse::TArrayAccess*>(ptNode));
		default:
			FAILED("inappropriate PT type for ArrayAccess: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<ArrayCreationExpression> ArrayCreationExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::ArrayCreationExpression:
			return std::make_unique<ArrayCreationExpression>(static_cast<const Parse::TArrayCreationExpression*>(ptNode));
		default:
			FAILED("inappropriate PT type for ArrayCreationExpression: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<AssignmentExpression> AssignmentExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::Assignment:
			return std::make_unique<AssignmentExpression>(static_cast<const Parse::TAssignment*>(ptNode));
		default:
			FAILED("inappropriate PT type for AssignmentExpression: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<BinaryExpression> BinaryExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return BinaryExpression::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::AdditiveExpression:
			return std::make_unique<BinaryExpression>(static_cast<const Parse::TAdditiveExpression*>(ptNode));
		case Parse::NonTerminalType::AndExpression:
			return std::make_unique<BinaryExpression>(static_cast<const Parse::TAndExpression*>(ptNode));
		case Parse::NonTerminalType::ConditionalAndExpression:
			return std::make_unique<BinaryExpression>(static_cast<const Parse::TConditionalAndExpression*>(ptNode));
		case Parse::NonTerminalType::ConditionalOrExpression:
			return std::make_unique<BinaryExpression>(static_cast<const Parse::TConditionalOrExpression*>(ptNode));
		case Parse::NonTerminalType::EqualityExpression:
			return std::make_unique<BinaryExpression>(static_cast<const Parse::TEqualityExpression*>(ptNode));
		case Parse::NonTerminalType::InclusiveOrExpression:
			return std::make_unique<BinaryExpression>(static_cast<const Parse::TInclusiveOrExpression*>(ptNode));
		case Parse::NonTerminalType::MultiplicativeExpression:
			return std::make_unique<BinaryExpression>(static_cast<const Parse::TMultiplicativeExpression*>(ptNode));
		case Parse::NonTerminalType::RelationalExpression:
			return std::make_unique<BinaryExpression>(static_cast<const Parse::TRelationalExpression*>(ptNode));
		default:
			FAILED("inappropriate PT type for BinaryExpression: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<CastExpression> CastExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::CastExpression:
			return std::make_unique<CastExpression>(static_cast<const Parse::TCastExpression*>(ptNode));
		default:
			FAILED("inappropriate PT type for CastExpression: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<ClassInstanceCreationExpression> ClassInstanceCreationExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::ClassInstanceCreationExpression:
			return std::make_unique<ClassInstanceCreationExpression>(static_cast<const Parse::TClassInstanceCreationExpression*>(ptNode));
		default:
			FAILED("inappropriate PT type for ClassInstanceCreationExpression: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<FieldAccess> FieldAccess::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::FieldAccess:
			return std::make_unique<FieldAccess>(static_cast<const Parse::TFieldAccess*>(ptNode));
		default:
			FAILED("inappropriate PT type for FieldAccess: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<Literal> Literal::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return Literal::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::Literal:
			return std::make_unique<Literal>(static_cast<const Parse::TLiteral*>(ptNode));
		default:
			FAILED("inappropriate PT type for Literal: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<LocalVariableExpression> LocalVariableExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::This2:
			return std::make_unique<LocalVariableExpression>(static_cast<const Parse::TThis2*>(ptNode));
		default:
			FAILED("inappropriate PT type for LocalVariableExpression: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<MethodInvocation> MethodInvocation::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::MethodInvocation:
			return std::make_unique<MethodInvocation>(static_cast<const Parse::TMethodInvocation*>(ptNode));
		default:
			FAILED("inappropriate PT type for MethodInvocation: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<NameExpression> NameExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return NameExpression::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::Name:
			return std::make_unique<NameExpression>(Name::create(ptNode));
		default:
			FAILED("inappropriate PT type for NameExpression: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<UnaryExpression> UnaryExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return UnaryExpression::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::UnaryExpression:
			return std::make_unique<UnaryExpression>(static_cast<const Parse::TUnaryExpression*>(ptNode));
		case Parse::NonTerminalType::UnaryExpressionNotPlusMinus:
			return std::make_unique<UnaryExpression>(static_cast<const Parse::TUnaryExpressionNotPlusMinus*>(ptNode));
		default:
			FAILED("inappropriate PT type for UnaryExpression: " + std::to_string((int)ptNode->type));
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// toCode
//
//////////////////////////////////////////////////////////////////////////////

std::string ArrayAccess::toCode() const {
	return "(" + array->toCode() + "[" + index->toCode() + "])";
}

std::string ArrayCreationExpression::toCode() const
{
	return "(new " + type->toCode() + '[' + size->toCode() + "])";
}

std::string AssignmentExpression::toCode() const
{
	return "(" + lhs->toCode() + "=" + rhs->toCode() + ")";
}

std::string BinaryExpression::toCode() const
{
	if (op == Variant::InstanceOf)
	{
		auto &rhsType = std::get<std::unique_ptr<Type>>(rhs);
		return "(" + lhs->toCode() + op + rhsType->toCode() + ")";
	}
	auto &rhsExpr = std::get<std::unique_ptr<Expression>>(rhs);
	return "(" + lhs->toCode() + op + rhsExpr->toCode() + ")";
}

std::string CastExpression::toCode() const {
	return "(" + type->toCode() + ")" + rhs->toCode();
}

std::string ClassInstanceCreationExpression::toCode() const
{
	std::string str = "(new " + type->toCode() + "(";
	for (auto &arg : args)
	{
		str += arg->toCode();
		str += ", ";
	}
	// remove the extra ", "
	if (!args.empty())
	{
		str.pop_back();
		str.pop_back();
	}
	str += "))";
	return str;
}

std::string FieldAccess::toCode() const
{
	return "(" + std::visit([this](auto &src) { return src->toCode(); }, source) + "." + member + ")";
}

std::string Literal::toCode() const {
	return std::visit(visitor {
		[](unsigned int x) { return std::to_string(x); },
		[](bool x) -> std::string { return x ? "true" : "false"; },
		[](char x) { return std::string("'") + x + "'"; },
		[](std::string x) { return x; },
		[](std::nullptr_t) -> std::string { return "null"; }
	}, value);
}

std::string LocalVariableExpression::toCode() const
{
	return id;
}

std::string MethodInvocation::toCode() const
{
	std::string str = "(";
	std::visit([&str](auto &src) {
		if (src != nullptr)
		{
			str += src->toCode() + ".";
		}
	}, source);
	str += methodName + "(";
	for (auto &arg : args)
	{
		str += arg->toCode() + ", ";
	}
	// pop the extra ", "
	if (!args.empty())
	{
		str.pop_back();
		str.pop_back();
	}
	str += "))";
	return str;
}

std::string NameExpression::toCode() const
{
	return converted ? converted->toCode() : unresolved->toCode();
}

std::string UnaryExpression::toCode() const
{
	return "" + op + expr->toCode();
}

//////////////////////////////////////////////////////////////////////////////
//
//										Constructors and other specific things
//
//////////////////////////////////////////////////////////////////////////////

ArrayAccess::ArrayAccess(const Parse::TArrayAccess *ptNode)
				: array(Expression::create(ptNode->expression)),
				  index(Expression::create(ptNode->expression))
{
	nodeType = NodeType::ArrayAccess;
}

ArrayCreationExpression::ArrayCreationExpression(const Parse::TArrayCreationExpression *ptNode)
				: type(Type::create((ptNode->v == Parse::TArrayCreationExpressionV::NewPrimitiveTypeLSBrExpressionRSBr)
				                    ? (const Parse::Tree *)ptNode->primitiveType
				                    : (const Parse::Tree *)ptNode->classOrInterfaceType)),
				  size(Expression::create(ptNode->expression))
{
	nodeType = NodeType::ArrayCreationExpression;
	type->isArray = true;
}

//////////////////////////////////////////////////////////////////////////////
//
// AssignmentExpression
//
//////////////////////////////////////////////////////////////////////////////

AssignmentExpression::AssignmentExpression(const Parse::TAssignment *ptNode)
	: lhs(Expression::create(ptNode->leftHandSide)),
		rhs(Expression::create(ptNode->assignmentExpression))
{
	nodeType = NodeType::AssignmentExpression;
}

//////////////////////////////////////////////////////////////////////////////
//
// BinaryExpression
//
//////////////////////////////////////////////////////////////////////////////

static_assert(BinaryExpression::Variant::Sub == BinaryExpression::Variant::Add + ((int)Parse::TAdditiveExpressionV::AdditiveExpressionMinusMultiplicativeExpression - (int)Parse::TAdditiveExpressionV::AdditiveExpressionPlusMultiplicativeExpression));
BinaryExpression::BinaryExpression(const Parse::TAdditiveExpression *ptNode)
	: op(Variant::Add + ((int)ptNode->v - (int)Parse::TAdditiveExpressionV::AdditiveExpressionPlusMultiplicativeExpression)),
		lhs(Expression::create(ptNode->additiveExpression)),
		rhs(Expression::create(ptNode->multiplicativeExpression))
{
	nodeType = NodeType::BinaryExpression;
}
static_assert(BinaryExpression::Variant::Div == BinaryExpression::Variant::Mult + ((int)Parse::TMultiplicativeExpressionV::MultiplicativeExpressionRSlashUnaryExpression - (int)Parse::TMultiplicativeExpressionV::MultiplicativeExpressionStarUnaryExpression));
static_assert(BinaryExpression::Variant::Mod == BinaryExpression::Variant::Mult + ((int)Parse::TMultiplicativeExpressionV::MultiplicativeExpressionPercUnaryExpression - (int)Parse::TMultiplicativeExpressionV::MultiplicativeExpressionStarUnaryExpression));
BinaryExpression::BinaryExpression(const Parse::TMultiplicativeExpression *ptNode)
	: op(Variant::Mult + ((int)ptNode->v - (int)Parse::TMultiplicativeExpressionV::MultiplicativeExpressionStarUnaryExpression)),
		lhs(Expression::create(ptNode->multiplicativeExpression)),
		rhs(Expression::create(ptNode->unaryExpression))
{
	nodeType = NodeType::BinaryExpression;
}
static_assert(BinaryExpression::Variant::Gt == BinaryExpression::Variant::Lt + ((int)Parse::TRelationalExpressionV::RelationalExpressionGrAdditiveExpression - (int)Parse::TRelationalExpressionV::RelationalExpressionLeAdditiveExpression));
static_assert(BinaryExpression::Variant::LtEq == BinaryExpression::Variant::Lt + ((int)Parse::TRelationalExpressionV::RelationalExpressionLeEqAdditiveExpression - (int)Parse::TRelationalExpressionV::RelationalExpressionLeAdditiveExpression));
static_assert(BinaryExpression::Variant::GtEq == BinaryExpression::Variant::Lt + ((int)Parse::TRelationalExpressionV::RelationalExpressionGrEqAdditiveExpression - (int)Parse::TRelationalExpressionV::RelationalExpressionLeAdditiveExpression));
static_assert(BinaryExpression::Variant::InstanceOf == BinaryExpression::Variant::Lt + ((int)Parse::TRelationalExpressionV::RelationalExpressioninstanceofReferenceType - (int)Parse::TRelationalExpressionV::RelationalExpressionLeAdditiveExpression));
BinaryExpression::BinaryExpression(const Parse::TRelationalExpression *ptNode)
	: op(Variant::Lt + ((int)ptNode->v - (int)Parse::TRelationalExpressionV::RelationalExpressionLeAdditiveExpression)),
		lhs(Expression::create(ptNode->relationalExpression)),
	// will initialize to nullptr for instanceof
		rhs(Expression::create(ptNode->additiveExpression))
{
	nodeType = NodeType::BinaryExpression;
	if (op == Variant::InstanceOf)
	{
		rhs = Type::create(ptNode->referenceType);
	}
}
static_assert(BinaryExpression::Variant::NEq == BinaryExpression::Variant::Eq + ((int)Parse::TEqualityExpressionV::EqualityExpressionBangEqRelationalExpression - (int)Parse::TEqualityExpressionV::EqualityExpressionEqEqRelationalExpression));
BinaryExpression::BinaryExpression(const Parse::TEqualityExpression *ptNode)
	: op(Variant::Eq + ((int)ptNode->v - (int)Parse::TEqualityExpressionV::EqualityExpressionEqEqRelationalExpression)),
		lhs(Expression::create(ptNode->equalityExpression)),
		rhs(Expression::create(ptNode->relationalExpression))
{
	nodeType = NodeType::BinaryExpression;
}
BinaryExpression::BinaryExpression(const Parse::TAndExpression *ptNode)
	: op(Variant::EagerAnd),
		lhs(Expression::create(ptNode->andExpression)),
		rhs(Expression::create(ptNode->equalityExpression))
{
	nodeType = NodeType::BinaryExpression;
}
BinaryExpression::BinaryExpression(const Parse::TInclusiveOrExpression *ptNode)
	: op(Variant::EagerOr),
		lhs(Expression::create(ptNode->inclusiveOrExpression)),
		rhs(Expression::create(ptNode->andExpression))
{
	nodeType = NodeType::BinaryExpression;
}
BinaryExpression::BinaryExpression(const Parse::TConditionalAndExpression *ptNode)
	: op(Variant::LazyAnd),
		lhs(Expression::create(ptNode->conditionalAndExpression)),
		rhs(Expression::create(ptNode->inclusiveOrExpression))
{
	nodeType = NodeType::BinaryExpression;
}
BinaryExpression::BinaryExpression(const Parse::TConditionalOrExpression *ptNode)
	: op(Variant::LazyOr),
		lhs(Expression::create(ptNode->conditionalOrExpression)),
		rhs(Expression::create(ptNode->conditionalAndExpression))
{
	nodeType = NodeType::BinaryExpression;
}

std::string operator+=(std::string& str, BinaryExpression::Variant op)
{
	switch(op)
	{
		case BinaryExpression::Variant::Add:				return str += "+";
		case BinaryExpression::Variant::Sub:				return str += "-";
		case BinaryExpression::Variant::Mult:				return str += "*";
		case BinaryExpression::Variant::Div:				return str += "/";
		case BinaryExpression::Variant::Mod:				return str += "%";
		case BinaryExpression::Variant::Lt:					return str += "<";
		case BinaryExpression::Variant::Gt:					return str += ">";
		case BinaryExpression::Variant::LtEq:				return str += "<=";
		case BinaryExpression::Variant::GtEq:				return str += ">=";
		case BinaryExpression::Variant::InstanceOf:	return str += "instanceof";
		case BinaryExpression::Variant::Eq:					return str += "==";
		case BinaryExpression::Variant::NEq:				return str += "!=";
		case BinaryExpression::Variant::EagerAnd:		return str += "&";
		case BinaryExpression::Variant::EagerOr:		return str += "|";
		case BinaryExpression::Variant::LazyAnd:		return str += "&&";
		case BinaryExpression::Variant::LazyOr:			return str += "||";
		case BinaryExpression::Variant::Max:		;// fallthrough
			// no default to trigger compiler warning on missing case
	}
	FAILED("String conversion on invalid opcode: " + std::to_string((int)op));
}
std::string operator+(std::string str, BinaryExpression::Variant op)
{
	return str += op;
}

std::ostream& operator<<(std::ostream& os, BinaryExpression::Variant op)
{
	if (op >= BinaryExpression::Variant::Max) {
		os.setstate(std::ios_base::failbit);
		return os;
	}
	return os << ("" + op);
}

//////////////////////////////////////////////////////////////////////////////
//
// CastExpression
//
//////////////////////////////////////////////////////////////////////////////

CastExpression::CastExpression(const Parse::TCastExpression *ptNode)
{
	nodeType = NodeType::CastExpression;
	switch (ptNode->v) {
		case Parse::TCastExpressionV::LParPrimitiveTypeRParUnaryExpression:
			type = Type::create(ptNode->primitiveType);
			rhs = Expression::create(ptNode->unaryExpression);
			break;
		case Parse::TCastExpressionV::LParPrimitiveTypeLSBrRSBrRParUnaryExpression:
			type = Type::create(ptNode->primitiveType);
			type->isArray = true;
			rhs = Expression::create(ptNode->unaryExpression);
			break;
		case Parse::TCastExpressionV::LParExpressionRParUnaryExpressionNotPlusMinus:
			type = Type::create(ptNode->expression);
			rhs = Expression::create(ptNode->unaryExpressionNotPlusMinus);
			break;
		case Parse::TCastExpressionV::LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus:
			type = Type::create(ptNode->name);
			type->isArray = true;
			rhs = Expression::create(ptNode->unaryExpressionNotPlusMinus);
			break;
		default:
			ASSERT(false);
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// ClassInstanceCreationExpression
//
//////////////////////////////////////////////////////////////////////////////

ClassInstanceCreationExpression::ClassInstanceCreationExpression(const Parse::TClassInstanceCreationExpression *ptNode)
	: type(NameType::create(ptNode->classType)),
		args(std::move(NodeList<Expression>(ptNode->argumentList).list))
{
	nodeType = NodeType::ClassInstanceCreationExpression;
}

//////////////////////////////////////////////////////////////////////////////
//
// FieldAccess
//
//////////////////////////////////////////////////////////////////////////////

FieldAccess::FieldAccess(const Parse::TFieldAccess *ptNode)
  :	source(Expression::create(ptNode->primary)),
	member(ptNode->identifier->value)
{
	nodeType = NodeType::FieldAccess;
}
FieldAccess::FieldAccess(std::unique_ptr<Expression> obj, std::string field)
  :	source(std::move(obj)),
	member(std::move(field))
{
	nodeType = NodeType::FieldAccess;
}
FieldAccess::FieldAccess(std::unique_ptr<NameType> type, std::string field)
  :	source(std::move(type)),
	member(std::move(field))
{
	nodeType = NodeType::FieldAccess;
}

bool FieldAccess::isStaticAccessor() const
{
	return std::holds_alternative<std::unique_ptr<NameType>>(source);
}


//////////////////////////////////////////////////////////////////////////////
//
// Literal
//
//////////////////////////////////////////////////////////////////////////////

Literal::Literal(const Parse::TLiteral *ptNode)
{
	nodeType = NodeType::Literal;
	switch (ptNode->v) {
		case Parse::TLiteralV::IntegerLiteral:
			value = static_cast<unsigned int>(ptNode->integerLiteral->value);
			break;
		case Parse::TLiteralV::BooleanLiteral:
			value = static_cast<bool>(ptNode->booleanLiteral->value);
			break;
		case Parse::TLiteralV::CharacterLiteral:
			value = static_cast<char>(ptNode->characterLiteral->value);
			break;
		case Parse::TLiteralV::StringLiteral:
			value = ptNode->stringLiteral->value;
			break;
		case Parse::TLiteralV::NullLiteral:
			value = nullptr;
			break;
		default:
			ASSERT(false);
	}
}

bool Literal::isJavaString(TypeDeclaration *decl) {
	return decl == stringDecl;
}

//////////////////////////////////////////////////////////////////////////////
//
// LocalVariableExpression
//
//////////////////////////////////////////////////////////////////////////////

// mostly a dummy class - the equivalent of the Literal class, but for a "this" expression
LocalVariableExpression::LocalVariableExpression(const Parse::TThis2 *ptNode)
  : id("this")
{
	nodeType = NodeType::LocalVariableExpression;
}

LocalVariableExpression::LocalVariableExpression(std::string identifier)
  :	id(identifier)
{
	nodeType = NodeType::LocalVariableExpression;
}

//////////////////////////////////////////////////////////////////////////////
//
// MethodInvocation
//
//////////////////////////////////////////////////////////////////////////////

MethodInvocation::MethodInvocation(const Parse::TMethodInvocation *ptNode)
  :	methodName(ptNode->identifier->value),
	args(std::move(NodeList<Expression>(ptNode->argumentList).list))
{
	nodeType = NodeType::MethodInvocation;
	if (ptNode->name != nullptr)
	{
		source = Name::create(ptNode->name);
	} else {
		// even if there is no prefix and ptNode->primary is null, we want to initialize the variant with
		// a null unique_ptr<Expression>, since Expression is the simpler case (it has simpler expression resolution)
		source = Expression::create(ptNode->primary);
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// NameExpression
//
//////////////////////////////////////////////////////////////////////////////

NameExpression::NameExpression(std::unique_ptr<Name> other)
  : unresolved(std::move(other))
{
	nodeType = NodeType::NameExpression;
}

//////////////////////////////////////////////////////////////////////////////
//
// UnaryExpression
//
//////////////////////////////////////////////////////////////////////////////

UnaryExpression::UnaryExpression(const Parse::TUnaryExpression *ptNode)
	: op(Variant::Minus),
		expr(Expression::create(ptNode->unaryExpression))
{
	nodeType = NodeType::UnaryExpression;
}

UnaryExpression::UnaryExpression(const Parse::TUnaryExpressionNotPlusMinus *ptNode)
	: op(Variant::Bang),
		expr(Expression::create(ptNode->unaryExpression))
{
	nodeType = NodeType::UnaryExpression;
}


std::string operator+=(std::string& str, UnaryExpression::Variant type)
{
	switch(type)
	{
		case UnaryExpression::Variant::Minus:	return str += "-";
		case UnaryExpression::Variant::Bang:	return str += "!";
		case UnaryExpression::Variant::Max:		;// fallthrough
			// no default to trigger compiler warning on missing case
	}
	FAILED("String conversion on invalid operator type: " + std::to_string((int)type));
}
std::string operator+(std::string str, UnaryExpression::Variant type)
{
	return str += type;
}

std::ostream& operator<<(std::ostream& os, UnaryExpression::Variant type)
{
	if (type >= UnaryExpression::Variant::Max) {
		os.setstate(std::ios_base::failbit);
		return os;
	}
	return os << ("" + type);
}

TypeResult::TypeResult(): isPrimitive(true), isArray(false), userDefinedType(nullptr) {

}

bool TypeResult::isNum() const {
	return !isArray && isNumOrArrayNum();

}

bool TypeResult::isJavaString() const  {
	return !isPrimitive && !isArray && Literal::isJavaString(userDefinedType);
}

bool TypeResult::isPrimitiveType(TypePrimitive primitive) const {
	return isPrimitive && !isArray && primitiveType == primitive;
}

bool TypeResult::operator==(const TypeResult &other) const {
	return isPrimitive == other.isPrimitive &&
		   isArray == other.isArray &&
		   (isPrimitive ? primitiveType == other.primitiveType :
			userDefinedType == other.userDefinedType);
}

bool TypeResult::isNumOrArrayNum() const {
	return isPrimitive && (primitiveType == TypePrimitive::Int ||
	                       primitiveType == TypePrimitive::Short ||
	                       primitiveType == TypePrimitive::Byte ||
	                       primitiveType == TypePrimitive::Char);
}

bool TypeResult::canAssignToMe(const TypeResult &other) const {
	// TODO: remaining rules in JLS 5.1.4
	// same type on both sides
	if (*this == other)
		return true;
	if (!isArray) {
		// short <- byte
		if (primitiveType == TypePrimitive::Short &&
			other.primitiveType == TypePrimitive::Byte)
			return true;
		// int <- byte
		if (primitiveType == TypePrimitive::Int &&
			other.primitiveType == TypePrimitive::Byte)
			return true;
		// int <- short
		if (primitiveType == TypePrimitive::Int &&
			other.primitiveType == TypePrimitive::Short)
			return true;
		// int <- char
		if (primitiveType == TypePrimitive::Int &&
			other.primitiveType == TypePrimitive::Char)
			return true;
	}
	// C := null where C is any non-primitive
	if (!isPrimitive && other.isPrimitiveType(TypePrimitive::Null))
		return true;
	// both are (either single or array of) objects
	if (!isPrimitive && !other.isPrimitive) {
		// same type on both sides is handled at the top
		for (auto *decl : other.userDefinedType->hyperSet) {
			// assigning to super class
			if (userDefinedType == decl)
				return true;
		}
	}
	return false;
}

} //namespace AST
