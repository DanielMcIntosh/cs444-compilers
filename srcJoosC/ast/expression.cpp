#include "ast/expression.h"
#include "ast/name.h"
#include "ast/type.h"
#include "ast/nodeList.h"
#include "ast/typeDeclaration.h"
#include "ast/variableDeclaration.h"
#include "parse/parseTree.h"
#include <memory>
#include <optional>
#include <ostream>

namespace AST
{

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

static std::string charEscape(char c)
{
	return c >= 32 ? std::string() + c
	               : c == '\b' ? "\\b"
	               : c == '\t' ? "\\t"
	               : c == '\n' ? "\\n"
	               : c == '\f' ? "\\f"
	               : c == '\r' ? "\\r"
	               : c == '\'' ? "\\'"
	               : c == '\"' ? "\\\""
	               : c == '\\' ? "\\\\"
	               : std::string("\\") + (char)('0' + (c>>6)%8)
	                                   + (char)('0' + (c>>3)%8)
	                                   + (char)('0' + (c>>0)%8);
}

static std::string stringEscape(std::string s)
{
	for (unsigned int i = 0; i < s.length(); ++i)
	{
		if (s[i] < 32)
		{
			std::string escaped = charEscape(s[i]);
			s.replace(i, 1, escaped);
			i += escaped.length() - 1;
		}
	}
	return s;
}

std::string Literal::toCode() const {
	return std::visit(visitor {
		[](unsigned int x) { return std::to_string(x); },
		[](bool x) -> std::string { return x ? "true" : "false"; },
		[](char x) { return "'" + charEscape(x) + "'"; },
		[](std::string x) { return "\"" + stringEscape(x) + "\""; },
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

//////////////////////////////////////////////////////////////////////////////
//
// ArrayAccess
//
//////////////////////////////////////////////////////////////////////////////

ArrayAccess::ArrayAccess(const Parse::TArrayAccess *ptNode)
	: array(Expression::create((ptNode->v == Parse::TArrayAccessV::NameLSBrExpressionRSBr)
						? (const Parse::Tree *)ptNode->name
						: (const Parse::Tree *)ptNode->primaryNoNewArray)),
	  index(Expression::create(ptNode->expression))
{
	nodeType = NodeType::ArrayAccess;
}
ArrayAccess::ArrayAccess(std::unique_ptr<Expression> arr, std::unique_ptr<Expression> ind)
  : array(std::move(arr)),
	index(std::move(ind))
{
	nodeType = NodeType::ArrayAccess;
}
ArrayAccess* ArrayAccess::clone() const {
	ArrayAccess* dup = new ArrayAccess(std::unique_ptr<Expression>(array->clone()), std::unique_ptr<Expression>(index->clone()));
	dup->typeResult = this->typeResult;
	return dup;
}

//////////////////////////////////////////////////////////////////////////////
//
// ArrayCreationExpression
//
//////////////////////////////////////////////////////////////////////////////

ArrayCreationExpression::ArrayCreationExpression(const Parse::TArrayCreationExpression *ptNode)
	: type(Type::create((ptNode->v == Parse::TArrayCreationExpressionV::NewPrimitiveTypeLSBrExpressionRSBr)
	                    ? (const Parse::Tree *)ptNode->primitiveType
	                    : (const Parse::Tree *)ptNode->classOrInterfaceType)),
	  size(Expression::create(ptNode->expression))
{
	nodeType = NodeType::ArrayCreationExpression;
	type->isArray = true;
}
ArrayCreationExpression::ArrayCreationExpression(std::unique_ptr<Type> t, std::unique_ptr<Expression> sz)
  :	type(std::move(t)),
	size(std::move(sz))
{
	nodeType = NodeType::ArrayCreationExpression;
}

ArrayCreationExpression* ArrayCreationExpression::clone() const {
	ArrayCreationExpression* dup = new ArrayCreationExpression(std::unique_ptr<Type>(type->clone()), std::unique_ptr<Expression>(size->clone()));
	dup->typeResult = this->typeResult;
	return dup;
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
AssignmentExpression::AssignmentExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
  : lhs(std::move(left)),
	rhs(std::move(right))
{
	nodeType = NodeType::AssignmentExpression;
}
AssignmentExpression* AssignmentExpression::clone() const {
	AssignmentExpression* dup = new AssignmentExpression(std::unique_ptr<Expression>(lhs->clone()), std::unique_ptr<Expression>(rhs->clone()));
	dup->typeResult = this->typeResult;
	return dup;
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
BinaryExpression::BinaryExpression(Variant opVar, std::unique_ptr<Expression> left, std::variant<std::unique_ptr<Expression>, std::unique_ptr<Type>> right)
  :	op(opVar),
	lhs(std::move(left)),
	rhs(std::move(right))
{
	nodeType = NodeType::BinaryExpression;
}
BinaryExpression* BinaryExpression::clone() const {
	std::variant<std::unique_ptr<Expression>, std::unique_ptr<Type>> rhsDup = std::visit(visitor {
			[](std::unique_ptr<Expression> const& right) -> std::variant<std::unique_ptr<Expression>, std::unique_ptr<Type>> {
				return std::unique_ptr<Expression>(right->clone());},
			[](std::unique_ptr<Type> const& right) -> std::variant<std::unique_ptr<Expression>, std::unique_ptr<Type>> {
				return std::unique_ptr<Type>(right->clone());}
		}, rhs);
	BinaryExpression* dup = new BinaryExpression(op, std::unique_ptr<Expression>(lhs->clone()), std::move(rhsDup));
	dup->typeResult = this->typeResult;
	return dup;
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
CastExpression::CastExpression(std::unique_ptr<Type> t, std::unique_ptr<Expression> expr)
  :	type(std::move(t)),
	rhs(std::move(expr))
{
	nodeType = NodeType::CastExpression;
}
CastExpression* CastExpression::clone() const {
	CastExpression* dup = new CastExpression(std::unique_ptr<Type>(type->clone()), std::unique_ptr<Expression>(rhs->clone()));
	dup->typeResult = this->typeResult;
	return dup;
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

ClassInstanceCreationExpression::ClassInstanceCreationExpression(std::unique_ptr<NameType> t, std::vector<std::unique_ptr<Expression>> arguments)
	: type(std::move(t)),
		args(std::move(arguments))
{
	nodeType = NodeType::ClassInstanceCreationExpression;
}
ClassInstanceCreationExpression* ClassInstanceCreationExpression::clone() const {
	std::vector<std::unique_ptr<Expression>> dupArgs;
	for (auto &argument : args)
	{
		dupArgs.push_back(std::unique_ptr<Expression>(argument->clone()));
	}
	ClassInstanceCreationExpression* dup = new ClassInstanceCreationExpression(std::unique_ptr<NameType>(type->clone()), std::move(dupArgs));
	dup->typeResult = this->typeResult;
	dup->declaration = this->declaration;
	return dup;
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
FieldAccess::FieldAccess(std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>> src, std::string field)
  :	source(std::move(src)),
	member(std::move(field))
{
	nodeType = NodeType::FieldAccess;
}
FieldAccess* FieldAccess::clone() const {
	std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>> srcDup = std::visit(visitor {
			[](std::unique_ptr<Expression> const& src) -> std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>> {
				return std::unique_ptr<Expression>(src->clone());},
			[](std::unique_ptr<NameType> const& src) -> std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>> {
				return std::unique_ptr<NameType>(src->clone());}
		}, source);
	FieldAccess* dup = new FieldAccess(std::move(srcDup), member);
	dup->typeResult = this->typeResult;
	dup->decl = this->decl;
	return dup;
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
Literal::Literal(std::variant<unsigned int, bool, char, std::string, std::nullptr_t > val)
  : value(std::move(val))
{
	nodeType = NodeType::Literal;
}
Literal* Literal::clone() const {
	Literal* dup = new Literal(value); // pass by value results in copy
	dup->typeResult = this->typeResult;
	return dup;
}

bool Literal::isJavaString(TypeDeclaration *decl) {
	return decl == stringDecl;
}

//////////////////////////////////////////////////////////////////////////////
//
// LocalVariableExpression
//
//////////////////////////////////////////////////////////////////////////////

LocalVariableExpression::LocalVariableExpression(const Parse::TThis2 *ptNode)
  : id("this")
{
	nodeType = NodeType::LocalVariableExpression;
}
LocalVariableExpression::LocalVariableExpression(std::string identifier)
  :	id(std::move(identifier))
{
	nodeType = NodeType::LocalVariableExpression;
}

LocalVariableExpression* LocalVariableExpression::clone() const {
	LocalVariableExpression* dup = new LocalVariableExpression(id);
	dup->typeResult = this->typeResult;
	dup->declaration = this->declaration;
	return dup;
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
MethodInvocation::MethodInvocation(std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>, std::unique_ptr<Name>> src, std::string name, std::vector<std::unique_ptr<Expression>> arguments)
  :	source(std::move(src)),
	methodName(std::move(name)),
	args(std::move(arguments))
{
	nodeType = NodeType::MethodInvocation;
}
MethodInvocation* MethodInvocation::clone() const {
	std::vector<std::unique_ptr<Expression>> dupArgs;
	for (auto &argument : args)
	{
		dupArgs.push_back(std::unique_ptr<Expression>(argument->clone()));
	}
	std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>, std::unique_ptr<Name>> srcDup = std::visit(visitor {
			[](std::unique_ptr<Expression> const& src) -> std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>, std::unique_ptr<Name>> {
				return std::unique_ptr<Expression>(src->clone());},
			[](std::unique_ptr<NameType> const& src) -> std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>, std::unique_ptr<Name>> {
				return std::unique_ptr<NameType>(src->clone());},
			[](std::unique_ptr<Name> const& src) -> std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>, std::unique_ptr<Name>> {
				return std::unique_ptr<Name>(src->clone());}
		}, source);
	MethodInvocation* dup = new MethodInvocation(std::move(srcDup), methodName, std::move(dupArgs));
	dup->typeResult = this->typeResult;
	dup->declaration = this->declaration;
	return dup;
}

bool MethodInvocation::isStaticCall() const
{
	return std::holds_alternative<std::unique_ptr<NameType>>(source);
}
bool MethodInvocation::isDisambiguated() const
{
	return !std::holds_alternative<std::unique_ptr<Name>>(source);
}

//////////////////////////////////////////////////////////////////////////////
//
// NameExpression
//
//////////////////////////////////////////////////////////////////////////////

NameExpression::NameExpression(std::unique_ptr<Name> name, std::unique_ptr<Expression> conv)
  : unresolved(std::move(name)),
	converted(std::move(conv))
{
	nodeType = NodeType::NameExpression;
}
NameExpression* NameExpression::clone() const {
	NameExpression* dup = new NameExpression(std::unique_ptr<Name>(unresolved->clone()), converted ? std::unique_ptr<Expression>(converted->clone()) : nullptr);
	dup->typeResult = this->typeResult;
	return dup;
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
UnaryExpression::UnaryExpression(Variant opVar, std::unique_ptr<Expression> expression)
  : op(opVar),
	expr(std::move(expression))
{
	nodeType = NodeType::UnaryExpression;
}
UnaryExpression* UnaryExpression::clone() const {
	UnaryExpression* dup = new UnaryExpression(op, std::unique_ptr<Expression>(expr->clone()));
	dup->typeResult = this->typeResult;
	return dup;
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

ConstExpr UnaryExpression::tryEval() {
	auto constExpr = expr->tryEval();
	if (constExpr.type == ConstExprType::Bool && op == UnaryExpression::Variant::Bang) {
		return ConstExpr{ConstExprType::Bool, 0, !constExpr.boolVal};
	}
	return ConstExpr();
}

TypeResult::TypeResult(Type const& type, bool final)
  : isPrimitive(type.nodeType == NodeType::PrimitiveType),
	isArray(type.isArray),
	isFinal(final)
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

bool TypeResult::isNum() const {
	return !isArray && isNumOrArrayNum();

}

bool TypeResult::isJavaString() const  {
	return !isPrimitive && !isArray && Literal::isJavaString(userDefinedType);
}

bool TypeResult::isPrimitiveType(TypePrimitive primitive) const {
	return isPrimitive && !isArray && primitiveType == primitive;
}

bool TypeResult::isReferenceType() const {
	return isArray || !isPrimitive;
}

bool TypeResult::operator==(const TypeResult &other) const {
	return isPrimitive == other.isPrimitive &&
		   isArray == other.isArray &&
		   (isPrimitive ? primitiveType == other.primitiveType :
			userDefinedType == other.userDefinedType);
}
bool TypeResult::operator!=(const TypeResult &other) const {
	return !operator==(other);
}

bool TypeResult::isNumOrArrayNum() const {
	return isPrimitive && (primitiveType == TypePrimitive::Int ||
	                       primitiveType == TypePrimitive::Short ||
	                       primitiveType == TypePrimitive::Byte ||
	                       primitiveType == TypePrimitive::Char);
}

bool TypeResult::canAssignToMyType(const TypeResult &other) const {
	if ((isPrimitive && primitiveType == TypePrimitive::Void) ||
		(other.isPrimitive && other.primitiveType == TypePrimitive::Void))
		return false;
	// same type on both sides
	if (*this == other)
		return true;

	if (!isReferenceType()) {
		if (other.isReferenceType())
			return false;
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
		return false;
	}

	// C := null where C is any reference type
	if (other.isPrimitiveType(TypePrimitive::Null))
		return true;

	if (!isPrimitive && other.isArray)
	{
		if (userDefinedType->fqn == "java.lang.Object" ||
			userDefinedType->fqn == "java.lang.Cloneable" ||
			userDefinedType->fqn == "java.io.Serializable")
		{
			return true;
		}
	}
	// both are (either single or array of) objects
	if (!isPrimitive && !other.isPrimitive && (isArray == other.isArray)) {
		if (userDefinedType->fqn == "java.lang.Object" &&
			other.userDefinedType->isInterface)
		{
			return true;
		}

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
