#include "semantic/typeResolution.h"

#include "ast/expression.h"
#include "ast/name.h"
#include "ast/type.h"
#include "ast/typeDeclaration.h"
#include "ast/variableDeclaration.h"
#include "ast/conditionalStatement.h"
#include "semantic/semantic.h"

using Semantic::SemanticErrorType;

namespace AST
{
thread_local TypeDeclaration *Literal::stringDecl;

/**
 * TypeResolution's job is to associate Types with their corresponding TypeDeclarations.
 * (Note that only NameType has an associated TypeDeclaration, so resolving a PrimitiveType is a NOP)
 */

Semantic::SemanticErrorType NameType::resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	auto [typeDecl, err] = semantic.resolveType(this, enclosingClass);
	declaration = typeDecl;
	return err;
}

Semantic::SemanticErrorType PrimitiveType::resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return Semantic::SemanticErrorType::None;
}

//////////////////////////////////////////////////////////////////////////////
//
// TypeDeclaration and MemberDeclarations
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType TypeDeclaration::resolveSuperTypeNames(Semantic::SemanticDB const& semantic, TypeDeclaration* object)
{
	if (!gStandAloneMode) {
		if (!superClass && !isInterface && fqn != "java.lang.Object") {
			object->children.push_back(this);
		}
	}
	if (superClass)
	{
		if (SemanticErrorType err = superClass->resolve(semantic, this);
			err != SemanticErrorType::None)
		{
			return err;
		}
		superClass->getDeclaration()->children.push_back(this);
	}

	for (auto &intf: interfaces)
	{
		if (SemanticErrorType err = intf->resolve(semantic, this);
			err != SemanticErrorType::None)
		{
			return err;
		}
		intf->getDeclaration()->children.push_back(this);
	}
	return SemanticErrorType::None;
}

SemanticErrorType TypeDeclaration::resolveBodyTypeNames(Semantic::SemanticDB const& semantic)
{
	for (auto &decl : members)
	{
		if (SemanticErrorType err = decl->resolveTypes(semantic);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	return SemanticErrorType::None;
}

SemanticErrorType ConstructorDeclaration::resolveTypes(Semantic::SemanticDB const& semantic)
{
	for (auto &param: parameters)
	{
		if (SemanticErrorType err = param->resolveTypes(semantic, _enclosingClass);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}

	if (SemanticErrorType err = body->resolveTypes(semantic, _enclosingClass);
		err != SemanticErrorType::None)
	{
		return err;
	}

	return SemanticErrorType::None;
}

Semantic::SemanticErrorType FieldDeclaration::resolveTypes(Semantic::SemanticDB const& semantic)
{
	return varDecl->resolveTypes(semantic, _enclosingClass);
}

Semantic::SemanticErrorType MethodDeclaration::resolveTypes(Semantic::SemanticDB const& semantic)
{
	if (Semantic::SemanticErrorType err = returnType->resolve(semantic, _enclosingClass);
		err != Semantic::SemanticErrorType::None)
	{
		return err;
	}

	for (auto &param: parameters)
	{
		if (Semantic::SemanticErrorType err = param->resolveTypes(semantic, _enclosingClass);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}

	if (body)
	{
		if (Semantic::SemanticErrorType err = body->resolveTypes(semantic, _enclosingClass);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	return Semantic::SemanticErrorType::None;
}


//////////////////////////////////////////////////////////////////////////////
//
// Statements
//
//////////////////////////////////////////////////////////////////////////////

SemanticErrorType Block::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	for (auto &stmt: statements)
	{
		if (SemanticErrorType err = stmt->resolveTypes(semantic, enclosingClass);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	return SemanticErrorType::None;
}

SemanticErrorType ConditionalStatement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	Semantic::SemanticErrorType err;
	if (init) {
		err = init->resolveTypes(semantic, enclosingClass);
		GOFAIL_IF_ERR(err);
	}
	if (condition) {
		err = condition->resolveTypes(semantic, enclosingClass);
		GOFAIL_IF_ERR(err);
	}
	if (increment) {
		err = increment->resolveTypes(semantic, enclosingClass);
		GOFAIL_IF_ERR(err);
	}
	if (body) {
		err = body->resolveTypes(semantic, enclosingClass);
		GOFAIL_IF_ERR(err);
	}
	if (elseBody) {
		err = elseBody->resolveTypes(semantic, enclosingClass);
		GOFAIL_IF_ERR(err);
	}
	return Semantic::SemanticErrorType::None;

	fail:
	return err;
}

SemanticErrorType ExpressionStatement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (!expression)
		return SemanticErrorType::None;
	return expression->resolveTypes(semantic, enclosingClass);
}

SemanticErrorType LocalVariableDeclarationStatement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return declaration->resolveTypes(semantic, enclosingClass);
}

SemanticErrorType
ReturnStatement::resolveTypes(Semantic::SemanticDB const &semantic, TypeDeclaration *enclosingClass) {
	if (!returnValue)
		return SemanticErrorType::None;
	return returnValue->resolveTypes(semantic, enclosingClass);
}

//////////////////////////////////////////////////////////////////////////////
//
// Expressions
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
	else if (type->declaration->isInterface ||
		type->declaration->hasModifier(Modifier::Variant::Abstract))
	{
		return SemanticErrorType::InstantiateAbstractClass;
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
// Misc
//
//////////////////////////////////////////////////////////////////////////////

// pre-compute typePrefix in case expression-resolution reaches rule 3 and has to resolve a_1.a_2. ... a_k to a Type
SemanticErrorType Name::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	std::vector<std::string> curPrefix;
	for (unsigned int i = 0; i < ids.size(); ++i)
	{
		curPrefix.push_back(ids[i]);
		// leverage NameType's type resolution
		auto temp = std::make_unique<NameType>(Name(curPrefix));
		if (temp->resolve(semantic, enclosingClass) == SemanticErrorType::None)
		{
			buildConverted(std::move(temp), i+1);
			return SemanticErrorType::None;
		}
	}

	// even if we fail to resolve a type prefix, we can't return an error, because we might still be a valid expression
	return SemanticErrorType::None;
}

Semantic::SemanticErrorType VariableDeclaration::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	Semantic::SemanticErrorType err = Semantic::SemanticErrorType::None;
	if (initializer) {
		err = initializer->resolveTypes(semantic, enclosingClass);
	}
	if (err == Semantic::SemanticErrorType::None) {
		err = type->resolve(semantic, enclosingClass);
	}
	return err;
}

} //namespace AST
