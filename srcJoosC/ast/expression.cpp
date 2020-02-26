#include "ast/expression.h"
#include "ast/name.h"
#include "ast/type.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include <memory>
#include <ostream>

using Semantic::SemanticErrorType;
namespace AST
{

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
	return object->resolveTypes(semantic, enclosingClass);
}

SemanticErrorType
MethodInvocation::resolveTypes(Semantic::SemanticDB const &semantic, TypeDeclaration *enclosingClass)
{
	{
		SemanticErrorType error = std::visit(visitor {
			[&semantic, &enclosingClass](std::unique_ptr<Expression> &src) {
				return src ? src->resolveTypes(semantic, enclosingClass)	: SemanticErrorType::None;	},
			[&semantic, &enclosingClass](std::unique_ptr<Type> &src) {
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
	if (!prefix.empty())
	{
		// leverage Name's type resolution
		// note that we don't need to include id in this because we must evaluate to an expression,
		// so id must be a field, and thus not part of typePrefix.
		Name temp = Name(std::vector<std::string>(prefix.begin(), --prefix.end()), prefix.back());
		// just as we can't return an error (see comment below), Name.resolveTypes also
		// can't return an error, so there's no point in checking the return value
		temp.resolveTypes(semantic, enclosingClass);
		typePrefix = std::move(temp.typePrefix);
	}
	// even if we fail to resolve a type prefix, we can't return an error, because we might still be a valid expression
	return SemanticErrorType::None;
}

SemanticErrorType UnaryExpression::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return expr->resolveTypes(semantic, enclosingClass);
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
			return This::create(ptNode);
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
			return std::make_unique<NameExpression>(std::move(*Name::create(ptNode)));
		default:
			FAILED("inappropriate PT type for NameExpression: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<This> This::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::This2:
			return std::make_unique<This>(static_cast<const Parse::TThis2*>(ptNode));
		default:
			FAILED("inappropriate PT type for This: " + std::to_string((int)ptNode->type));
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
	return "(" + object->toCode() + "." + member + ")";
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
	std::string str;
	for (auto &pre : prefix)
	{
		str += pre + ".";
	}
	str += id;
	return str;
}

std::string This::toCode() const
{
	return "this";
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
	: type(Type::create(ptNode->classType)),
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
	: object(Expression::create(ptNode->primary)),
		member(ptNode->identifier->value)
{
	nodeType = NodeType::FieldAccess;
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
	}
	// even if there is no prefix and ptNode->primary is null, we want to initialize the variant with
	// a null unique_ptr<Expression>, since Expression is the simpler case (it has simpler expression resolution)
	source = Expression::create(ptNode->primary);
}

//////////////////////////////////////////////////////////////////////////////
//
// NameExpression
//
//////////////////////////////////////////////////////////////////////////////

NameExpression::NameExpression(Name &&other)
	: prefix(std::move(other.prefix)),
		id(std::move(other.id))
{
	nodeType = NodeType::NameExpression;
}

//////////////////////////////////////////////////////////////////////////////
//
// This
//
//////////////////////////////////////////////////////////////////////////////

// mostly a dummy class - the equivalent of the Literal class, but for a "this" expression
This::This(const Parse::TThis2 *ptNode)
{
	nodeType = NodeType::This;
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

} //namespace AST
