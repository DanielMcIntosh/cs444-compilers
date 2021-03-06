#pragma once

#include "ast/node.h"
#include <memory>
#include <string>

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
	class Scope;
}

namespace AST
{

class Type;
class TypeResult;
class Expression;
class TypeDeclaration;
class LocalVariableExpression;
class AssignmentExpression;

class VariableDeclaration: public Node
{
public:
	static std::unique_ptr<VariableDeclaration> create(const Parse::Tree *ptNode);
	explicit VariableDeclaration(const Parse::TFormalParameter *ptNode);
	explicit VariableDeclaration(const Parse::TVariableDeclaration *ptNode);
	explicit VariableDeclaration(std::unique_ptr<Type> t, std::string id, std::unique_ptr<Expression> init = nullptr);
	std::string toCode() const override;

	[[gnu::pure]]
	bool equals(const VariableDeclaration *) const;
	[[gnu::pure]]
	bool idEquals(const VariableDeclaration *other) const;
	[[gnu::pure]]
	bool idEquals(std::string const& str) const;
	[[gnu::pure]]
	bool typeEquals(const VariableDeclaration *other) const;
	[[gnu::pure]]
	bool typeEquals(const Type *other) const;
	bool typeEquals(const TypeResult &other) const;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope const& parentScope);

	bool hasInitializer() const;

	std::unique_ptr<LocalVariableExpression> asLocalVarExpr();
	std::unique_ptr<AssignmentExpression> initializerAsAssignmentExpr(std::unique_ptr<Expression> lhs);

public:
	std::unique_ptr<Type> type;
	std::string identifier;
	// nullable
	std::unique_ptr<Expression> initializer;

	// for local variables/parameters, this is the index on the stack (sort of)
	// for fields, this is the offset from the start of the data
	int index;
};

} //namespace AST
