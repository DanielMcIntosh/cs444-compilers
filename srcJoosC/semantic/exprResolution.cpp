#include "semantic/exprResolution.h"
#include "ast/expression.h"
#include "ast/name.h"
#include "ast/typeDeclaration.h"
#include "ast/variableDeclaration.h"
#include "ast/conditionalStatement.h"
#include "semantic/semantic.h"
#include "semantic/scope.h"


using Semantic::SemanticErrorType;

namespace AST
{

thread_local TypeDeduceError Expression::gError;
void Expression::resetError() {
	gError.hasError = false;
	gError.function.clear();
}

/**
 * ExprResolution's job is to associate LocalVariableExpressionss, FieldAccesses, MethodInvocations, etc.
 * with their corresponding declarations (could be any one of VariableDeclaration, FieldDeclaration, MethodDeclaration, etc.)
 *
 * In order to do this, a few things have to happen first:
 *	 -	We need to resolve Types (Already done, so we don't need to do it ourselves. We covered in class why we need it)
 * 	 -	If we encounter a Name, we have to disambiguate it. (Consider for example, trying to resolve a method invocation
 * 			when the source is an ambiguous Name. We can't tell what class to search for the MethodDeclaration without
 *			disambiguating the Name). Note that name disambituation involves attempting to resolve things as if they were
 *			expressions, so unlike for type resolution, we can't do name disambiguation before starting ExprResolution.
 *	 -	If we have child expressions, we have to deduce their types (Consider for example, trying to resolve a
 *			ClassInstanceCreationExpression to its corresponding ConstructorDeclaration. In order to figure out if we match
 *			a constructor's function signature, we need to know the types of the arugments we're passing it. Note that this
 *			process is NOT type resolution - the difference is exemplified by rvalues. E.g. We need to type of an addition
 *			expression, and type resolution doesn't provide it)
 *
 * However, type deduction (which we need to do on our child expressions) needs expression resolution to be completed first.
 * (e.g. we can't know the type of a FieldAccess if we don't know what type they declared the field with, so we need the
 * corresponding FieldDeclaration)
 *
 * To summarize:
 * ExprResolution needs to do the following things BEFORE it can search for a declaration:
 *	1. Name disambiguation
 *	2. Child expression expression resolution and type deduction
 *
 * THEN it can do a search for the corresponding declaration (its primary job).
 */

SemanticErrorType Expression::resolveAndDeduce(Semantic::Scope const& scope)
{
	if (auto error = disambiguate(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (auto error = deduceChildTypes(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (auto error = resolve(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	return deduceType();
}

SemanticErrorType Expression::disambiguate(Semantic::Scope const& scope)
{
	return SemanticErrorType::None;
}
SemanticErrorType Expression::deduceChildTypes(Semantic::Scope const& scope)
{
	return SemanticErrorType::None;
}
SemanticErrorType Expression::resolve(Semantic::Scope const& scope)
{
	return SemanticErrorType::None;
}

//////////////////////////////////////////////////////////////////////////////
//
// Disambiguation
//
//////////////////////////////////////////////////////////////////////////////

// !!NOT!! an override of Expression::disambiguate
SemanticErrorType Name::disambiguate(Semantic::Scope const& scope)
{
	// resolve to local variable
	{
		auto local = std::make_unique<LocalVariableExpression>(ids[0]);
		if (auto err = local->resolve(scope);
			err == SemanticErrorType::None)
		{
			buildConverted(std::move(local), 1);
			return SemanticErrorType::None;
		} else if(err == SemanticErrorType::VariableInOwnInitializer) {
			return err;
		}
	}

	// resolve to field access
	// in the process, we're going to make any implicit "this" or TypeName explicit
	{
		// if we're in a non-static method, resolve(this) will succeed.
		if (auto thisExpr = std::make_unique<LocalVariableExpression>("this");
			thisExpr->resolve(scope) == SemanticErrorType::None)
		{
			// LocalVariableExpression::deduceType can't fail, skip error check
			thisExpr->deduceType();
			// attempt construct a FieldAccess using the implicit "this"
			auto field = std::make_unique<FieldAccess>(std::move(thisExpr), ids[0]);
			if (field->resolve(scope) == SemanticErrorType::None)
			{
				buildConverted(std::move(field), 1);
				return SemanticErrorType::None;
			}
		}
		// implicit TypeName is not permitted in joos.
		// https://www.student.cs.uwaterloo.ca/~cs444/features/implicitthisclassforstaticmethods.html
	}

	// since we pre-computed during type resolution the result of rule3 of namespace disambiguation,
	// converted should already be non-null. If it is null, that means rule3 failed.
	return std::visit([](auto &expr){ return expr == nullptr; }, converted) ? SemanticErrorType::DisambiguiationFailed : SemanticErrorType::None;
}

void Name::buildConverted(std::unique_ptr<Expression> expr, unsigned int idStart)
{
	for (unsigned int i = idStart; i < ids.size(); ++i)
	{
		expr = std::make_unique<FieldAccess>(std::move(expr), ids[i]);
	}
	converted = std::move(expr);
}
void Name::buildConverted(std::unique_ptr<NameType> type, unsigned int idStart)
{
	if (idStart >= ids.size())
	{
		converted = std::move(type);
	} else
	{
		buildConverted(std::make_unique<FieldAccess>(std::move(type), ids[idStart]), idStart+1);
	}
}

SemanticErrorType MethodInvocation::disambiguate(Semantic::Scope const& scope)
{
	// if no source, make the implicit source explicit.
	if (std::visit([](auto &src) { return src == nullptr; }, source))
	{
		// if we're in a non-static method, resolve(this) will succeed.
		if (auto thisExpr = std::make_unique<LocalVariableExpression>("this");
			thisExpr->resolve(scope) == SemanticErrorType::None)
		{
			source = std::move(thisExpr);
		}
		else
		{
			// implicit TypeName is not permitted in joos. We can safely assume the source is thisExpr.
			// https://www.student.cs.uwaterloo.ca/~cs444/features/implicitthisclassforstaticmethods.html
			return SemanticErrorType::DisambiguiationFailed;
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

SemanticErrorType NameExpression::disambiguate(Semantic::Scope const& scope)
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
	return SemanticErrorType::None;
}

//////////////////////////////////////////////////////////////////////////////
//
// deduceChildTypes
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType ArrayAccess::deduceChildTypes(Semantic::Scope const& scope)
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
SemanticErrorType ArrayCreationExpression::deduceChildTypes(Semantic::Scope const& scope)
{
	return size->resolveAndDeduce(scope);
}
SemanticErrorType AssignmentExpression::deduceChildTypes(Semantic::Scope const& scope)
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
SemanticErrorType BinaryExpression::deduceChildTypes(Semantic::Scope const& scope)
{
	if (auto error = lhs->resolveAndDeduce(scope);
		error != SemanticErrorType::None)
	{
		return error;
	}
	if (op != Variant::InstanceOf)
	{
		auto &rhsExpr = std::get<std::unique_ptr<Expression>>(rhs);
		if (auto error = rhsExpr->resolveAndDeduce(scope);
			error != SemanticErrorType::None)
		{
			return error;
		}
		if (op == Variant::Add)
		{
			// String concatenation: if needed, make an explicit call to String::valueOf so both lhs and rhs are Strings
			if ((lhs->typeResult.isJavaString() && !rhsExpr->typeResult.isJavaString()) ||
				(!lhs->typeResult.isJavaString() && rhsExpr->typeResult.isJavaString()))
			{
				auto &strExpr = lhs->typeResult.isJavaString() ? lhs : rhsExpr;
				auto &otherExpr = !lhs->typeResult.isJavaString() ? lhs : rhsExpr;

				std::vector<std::unique_ptr<Expression>> args;
				if (otherExpr->typeResult.isReferenceType() || otherExpr->typeResult.isPrimitiveType(TypePrimitive::Null))
				{
					// use a hack to get the TypeDecl for java.lang.Object (String has Object as its implicit superclass)
					TypeDeclaration *objDecl = strExpr->typeResult.userDefinedType->superClass->declaration;
					// cast otherExpr to Object, since valueOf expects an Object, String or primitive as its argument
					args.push_back(std::make_unique<CastExpression>(objDecl->asType(), std::move(otherExpr)));
				}
				else
					args.push_back(std::move(otherExpr));

				// overwrite otherExpr with the exlicit invocation of String::valueOf
				otherExpr = std::make_unique<MethodInvocation>(strExpr->typeResult.userDefinedType->asType(), "valueOf", std::move(args));
				return otherExpr->resolveAndDeduce(scope);
			}
		}
	}
	return SemanticErrorType::None;
}
SemanticErrorType CastExpression::deduceChildTypes(Semantic::Scope const& scope)
{
	return rhs->resolveAndDeduce(scope);
}
SemanticErrorType ClassInstanceCreationExpression::deduceChildTypes(Semantic::Scope const& scope)
{
	for (auto &expr : args) {
		if (auto error = expr->resolveAndDeduce(scope);
			error != SemanticErrorType::None)
		{
			return error;
		}
	}

	return SemanticErrorType::None;
}

SemanticErrorType FieldAccess::deduceChildTypes(Semantic::Scope const& scope)
{
	return std::visit(visitor{
		[&scope](std::unique_ptr<Expression> &expr) {
			return expr->resolveAndDeduce(scope);
		},
		[](std::unique_ptr<NameType> &t) {
			return SemanticErrorType::None;
		}
	}, source);
}

SemanticErrorType MethodInvocation::deduceChildTypes(Semantic::Scope const& scope)
{
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

	return SemanticErrorType::None;
}

SemanticErrorType NameExpression::deduceChildTypes(Semantic::Scope const& scope)
{
	return converted->deduceChildTypes(scope);
}

SemanticErrorType UnaryExpression::deduceChildTypes(Semantic::Scope const& scope)
{
	return expr->resolveAndDeduce(scope);
}

//////////////////////////////////////////////////////////////////////////////
//
// resolve
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType ClassInstanceCreationExpression::resolve(Semantic::Scope const& scope)
{
	declaration = type->declaration->findConstructor(this);

	if (declaration == nullptr)
	{
		return SemanticErrorType::DeclarationNotFound;
	}
	if (declaration->hasModifier(Modifier::Variant::Protected))
	{
		// check that we can access the declaration (JLS 6.6.1)
		// protected constructors can only be used within the same package
		if (!scope._enclosingClass->isSamePackage(declaration->_enclosingClass))
		{
			return SemanticErrorType::AccessViolation;
		}
	}

	return SemanticErrorType::None;
}

SemanticErrorType FieldAccess::resolve(Semantic::Scope const& scope)
{
	TypeResult sourceType = std::visit(visitor{
		[](std::unique_ptr<Expression> &expr) {
			return expr->typeResult;
		},
		[](std::unique_ptr<NameType> &t) {
			return TypeResult(*t, false);
		}
	}, source);

	if (sourceType.isArray && member == "length") {
		// TODO provide a declaration for length?
		// this is a temporary hack until we better understand how we want to implement length
		decl = nullptr;
		return SemanticErrorType::None;
	}

	if (sourceType.isPrimitive) return SemanticErrorType::PrimativeNotExpected;

	decl = sourceType.userDefinedType->findField(this);
	if (decl == nullptr)
	{
		return SemanticErrorType::DeclarationNotFound;
	}
	if (decl->hasModifier(Modifier::Variant::Protected))
	{
		// check that we can access the declaration (JLS 6.6.1)
		if (!(scope._enclosingClass->isSamePackage(decl->_enclosingClass) ||
			 (scope._enclosingClass->isSubClassOf(decl->_enclosingClass) &&
			  (isStaticAccessor() || sourceType.userDefinedType->isSubClassOf(scope._enclosingClass)))))
		{
			return SemanticErrorType::AccessViolation;
		}
	}

	return SemanticErrorType::None;
}

SemanticErrorType LocalVariableExpression::resolve(Semantic::Scope const& scope)
{
	declaration = scope.findDecl(id);
	if (declaration == nullptr)
		return SemanticErrorType::LocalVariableDNE;
	if (declaration == scope._currentDeclaration)
		return SemanticErrorType::VariableInOwnInitializer;

	return SemanticErrorType::None;
}

SemanticErrorType MethodInvocation::resolve(Semantic::Scope const& scope)
{
	// find method declaration
	TypeResult sourceType = std::visit(visitor{
		[](std::unique_ptr<Expression> &src) { return src->typeResult; },
		[](std::unique_ptr<NameType> &src)   { return TypeResult(*src, false); },
		[](std::unique_ptr<Name> &) -> TypeResult { assert(false); }
	}, source);

	if (sourceType.isPrimitive) return SemanticErrorType::PrimativeNotExpected;

	declaration = sourceType.userDefinedType->findMethod(this);
	if (declaration == nullptr)
	{
		return SemanticErrorType::DeclarationNotFound;
	}
	if (declaration->hasModifier(Modifier::Variant::Protected))
	{
		// check that we can access the declaration (JLS 6.6.1)
		if (!(scope._enclosingClass->isSamePackage(declaration->_enclosingClass) ||
			 (scope._enclosingClass->isSubClassOf(declaration->_enclosingClass) &&
			  (isStaticCall() || sourceType.userDefinedType->isSubClassOf(scope._enclosingClass)))))
		{
			return SemanticErrorType::AccessViolation;
		}
	}

	return SemanticErrorType::None;
}

SemanticErrorType NameExpression::resolve(Semantic::Scope const& scope)
{
	return converted->resolve(scope);
}

//////////////////////////////////////////////////////////////////////////////
//
// deduceType
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType CastExpression::deduceType()
{
	// first allow all numeric casts
	auto lhs = TypeResult(*type, rhs->typeResult.isFinal);
	typeResult = lhs;
	if (lhs.isNum() && rhs->typeResult.isNum())
		OK();

	// then try assignability
	if (lhs.canAssignToMyType(rhs->typeResult))
		OK();
	else if (rhs->typeResult.canAssignToMyType(lhs))
		OK();

	GOFAIL(); // to print error
	fail:
	return SemanticErrorType::AssignableType;
}

SemanticErrorType ClassInstanceCreationExpression::deduceType()
{
	typeResult = TypeResult(*type, true);
	return SemanticErrorType::None;
}

SemanticErrorType FieldAccess::deduceType()
{
	// this is a temporary hack until we better understand how we want to implement length
	if (decl == nullptr)
	{
		if (member != "length")
		{
			return SemanticErrorType::TypeCheck;
		}
		typeResult = TypeResult(false, TypePrimitive::Int, true);
	}
	else
	{
		// type result is the type the field was declared with
		typeResult = TypeResult(*(decl->varDecl->type), decl->hasModifier(Modifier::Variant::Final));
	}
	return SemanticErrorType::None;
}

SemanticErrorType Literal::deduceType() {
	typeResult = std::visit(visitor{
					[](unsigned int) { return TypeResult{false, TypePrimitive::Int, true}; },
					[](bool) { return TypeResult{false, TypePrimitive::Boolean, true}; },
					[](char) { return TypeResult{false, TypePrimitive::Char, true}; },
					[](std::string&) {
						return (!gStandAloneMode) ? TypeResult(*(Literal::stringDecl->asType()), true) : TypeResult{false, TypePrimitive::Max, true}; },
					[](std::nullptr_t) { return TypeResult{false, TypePrimitive::Null, true}; }
	}, value);
	return SemanticErrorType::None;
}

SemanticErrorType ArrayAccess::deduceType() {
	// array must be array type
	if (!array->typeResult.isArray)
		GOFAIL();

	// index must be numerical type
	if (!index->typeResult.isNum())
		GOFAIL();

	// resulting type is the type of the array with array dropped
	typeResult = array->typeResult;
	typeResult.isArray = false;
	typeResult.isFinal = false;

	OK();

	fail:
	return SemanticErrorType::TypeCheck;
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
	typeResult = lhs->typeResult;
	if (lhs->typeResult.canAssignToMyType(rhs->typeResult) &&
		!lhs->typeResult.isFinal)
		OK();
	GOFAIL(); // to print error
	fail:
	return SemanticErrorType::TypeCheck;
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

std::optional<TypeResult> BinExprHelper(std::unique_ptr<Expression> &lhs, std::unique_ptr<Expression> &rhs,
                                           BinaryExpression::Variant op) {
	const auto &lhsTR = lhs->typeResult;
	const auto &rhsTR = rhs->typeResult;
	bool bothNum = lhsTR.isNum() && rhsTR.isNum();
	bool bothBool = lhsTR.isPrimitiveType(TypePrimitive::Boolean) &&
	                rhsTR.isPrimitiveType(TypePrimitive::Boolean);
	bool assignable = lhsTR.canAssignToMyType(rhsTR) || rhsTR.canAssignToMyType(lhsTR);

	if (bothNum && IsArithmeticOp(op)) {
		return TypeResult(false, TypePrimitive::Int, true);
	}

	if (bothNum && IsNumCompare(op)) {
		return TypeResult(false, TypePrimitive::Boolean, true);
	}

	if (bothBool && IsBooleanOp(op)) {
		return TypeResult(false, TypePrimitive::Boolean, true);
	}

	if ((bothNum || assignable) &&
	    (op == BinaryExpression::Variant::Eq || op == BinaryExpression::Variant::NEq)) {
		return TypeResult(false, TypePrimitive::Boolean, true);
	}

	// At this point, only string concatenation remains
	if (op == BinaryExpression::Variant::Add)
	{
		if (lhsTR.isJavaString() && !rhsTR.isPrimitiveType(TypePrimitive::Void))
		{
			TypeResult ret = lhsTR;
			ret.isFinal = true;
			return ret;
		}
		else if (rhsTR.isJavaString() && !lhsTR.isPrimitiveType(TypePrimitive::Void))
		{
			TypeResult ret = rhsTR;
			ret.isFinal = true;
			return ret;
		}
	}
	return std::nullopt;
}

SemanticErrorType BinaryExpression::deduceType() {
	SemanticErrorType err = SemanticErrorType::None;
	std::visit(visitor {
					[&](std::unique_ptr<Expression> &rexpr) {
						auto res = BinExprHelper(lhs, rexpr, op);
						if (res)
							typeResult = *res;
						else
							err = SemanticErrorType::TypeCheck;
					},
					[&](std::unique_ptr<Type> &type) {
						assert(op == BinaryExpression::Variant::InstanceOf);
						if (auto rhsTypeResult = TypeResult(*type, false);
							!lhs->typeResult.canAssignToMyType(rhsTypeResult) &&
							!rhsTypeResult.canAssignToMyType(lhs->typeResult))
						{
							err = SemanticErrorType::TypeCheck;
							return;
						}

						typeResult = TypeResult(false, TypePrimitive::Boolean, true);
					}
	}, rhs);

	GOFAIL_IF_ERR(err);
	OK();

	fail:
	return err;
}

SemanticErrorType LocalVariableExpression::deduceType()
{
	typeResult = TypeResult(*(declaration->type), false);
	return SemanticErrorType::None;
}
SemanticErrorType MethodInvocation::deduceType()
{
	typeResult = TypeResult(*(declaration->returnType), false);
	return SemanticErrorType::None;
}
SemanticErrorType NameExpression::deduceType() {
	if (auto err = converted->deduceType();
		err != SemanticErrorType::None)
	{
		return err;
	}
	typeResult = converted->typeResult;
	return SemanticErrorType::None;
}
SemanticErrorType UnaryExpression::deduceType() {
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
	typeResult.isFinal = true;
	return SemanticErrorType::None;
}

//////////////////////////////////////////////////////////////////////////////
//
// Non-expressions, which have to call down to resolveAndDeduce
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Statements
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType Block::resolveExprs(Semantic::Scope &parentScope)
{
	Semantic::Scope scope(parentScope);
	for (auto &stmt: statements)
	{
		if (SemanticErrorType err = stmt->resolveExprs(scope);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	return SemanticErrorType::None;
}

SemanticErrorType ConditionalStatement::resolveExprs(Semantic::Scope &parentScope)
{
	Semantic::Scope mainScope(parentScope);
	SemanticErrorType err;
	if (init)
	{
		err = init->resolveExprs(mainScope);
		GOFAIL_IF_ERR(err);
	}
	if (condition)
	{
		err = condition->resolveAndDeduce(mainScope);
		GOFAIL_IF_ERR(err);
		if (!condition->typeResult.isPrimitiveType(TypePrimitive::Boolean)) {
			return SemanticErrorType::TypeCheck;
		}
	}
	if (increment)
	{
		err = increment->resolveAndDeduce(mainScope);
		GOFAIL_IF_ERR(err);
	}
	err = body->resolveExprs(mainScope);
	GOFAIL_IF_ERR(err);
	if (elseBody)
	{
		Semantic::Scope elseScope(parentScope);
		err = elseBody->resolveExprs(elseScope);
		GOFAIL_IF_ERR(err);
	}
	OK();

	fail:
	return err;
}

SemanticErrorType ExpressionStatement::resolveExprs(Semantic::Scope &parentScope)
{
	if (expression != nullptr)
	{
		return expression->resolveAndDeduce(parentScope);
	}
	return SemanticErrorType::None;
}

SemanticErrorType LocalVariableDeclarationStatement::resolveExprs(Semantic::Scope &parentScope)
{
	if (!parentScope.add(declaration))
	{
		return SemanticErrorType::LocalVariableShadowing;
	}

	parentScope._currentDeclaration = declaration.get();
	// resolve initializer if it exists
	if (SemanticErrorType err = declaration->resolveExprs(parentScope);
		err != SemanticErrorType::None)
	{
		return err;
	}
	parentScope._currentDeclaration = nullptr;

	return SemanticErrorType::None;
}

SemanticErrorType ReturnStatement::resolveExprs(Semantic::Scope &parentScope)
{
	if (returnValue != nullptr)
	{
		auto err = returnValue->resolveAndDeduce(parentScope);
		if (err != SemanticErrorType::None) return err;
		if (std::holds_alternative<ConstructorDeclaration *>(parentScope._enclosingMethod)) {
			return SemanticErrorType::ReturningFromConstructor;
		}
		auto enclMethod = std::get<MethodDeclaration *>(parentScope._enclosingMethod);
		auto declaredType = TypeResult(*enclMethod->returnType, false);
		if (declaredType.isPrimitiveType(TypePrimitive::Void)) {
			return SemanticErrorType::ReturningValueFromVoidFunction;
		}
		if (!declaredType.canAssignToMyType(returnValue->typeResult)) {
			return SemanticErrorType::AssignableType;
		}
	}
	return SemanticErrorType::None;
}

//////////////////////////////////////////////////////////////////////////////
//
// TypeDeclaration and MemberDeclarations
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType TypeDeclaration::resolveBodyExprs()
{
	for (auto &decl : members)
	{
		if (SemanticErrorType err = decl->resolveExprs();
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	return SemanticErrorType::None;
}

SemanticErrorType ConstructorDeclaration::resolveExprs()
{
	if (identifier != _enclosingClass->name) {
		return SemanticErrorType::ConstructorWrongName;
	}
	Semantic::Scope scope(_enclosingClass, this);
	for (auto &param: parameters)
	{
		if (!scope.add(param))
		{
			return SemanticErrorType::LocalVariableShadowing;
		}
	}

	// TODO: probably want to remove this, and somehow add an explicit call to the
	// parent constructor at the start of body, which then gets resolved in body->resolveExprs
	if (_enclosingClass->superClass != nullptr)
	{
		auto *superDecl = _enclosingClass->superClass->declaration;
		auto implicitSuperCall = std::make_unique<ClassInstanceCreationExpression>(superDecl->asType(), std::vector<std::unique_ptr<Expression>>{});
		if (superDecl->findConstructor(implicitSuperCall.get()) == nullptr)
		{
			return SemanticErrorType::DefaultSuperConstructorMissing;
		}
	}

	if (body)
	{
		if (SemanticErrorType err = body->resolveExprs(scope);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	return SemanticErrorType::None;
}

SemanticErrorType FieldDeclaration::resolveExprs()
{
	Semantic::Scope scope(_enclosingClass);
	auto thisDecl = std::make_unique<VariableDeclaration>(_enclosingClass->asType(), "this");
	if (!hasModifier(Modifier::Variant::Static))
	{
		scope.add(thisDecl);
	}
	return varDecl->resolveExprs(scope);
}

SemanticErrorType MethodDeclaration::resolveExprs()
{
	Semantic::Scope scope(_enclosingClass, this);
	for (auto &param: parameters)
	{
		if (!scope.add(param))
		{
			return SemanticErrorType::LocalVariableShadowing;
		}
	}

	if (body)
	{
		if (SemanticErrorType err = body->resolveExprs(scope);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	return SemanticErrorType::None;
}


//////////////////////////////////////////////////////////////////////////////
//
// Other
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType VariableDeclaration::resolveExprs(Semantic::Scope const& parentScope)
{
	if (initializer != nullptr)
	{
		auto err = initializer->resolveAndDeduce(parentScope);
		if (err != SemanticErrorType::None) return err;
		if (!TypeResult(*type, false).canAssignToMyType(initializer->typeResult)) {
			return SemanticErrorType::AssignableType;
		}
	}
	return SemanticErrorType::None;
}


} //namespace AST
