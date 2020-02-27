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
class Expression;
class TypeDeclaration;

class VariableDeclaration: public Node
{
public:
	static std::unique_ptr<VariableDeclaration> create(const Parse::Tree *ptNode);
	explicit VariableDeclaration(const Parse::TFormalParameter *ptNode);
	explicit VariableDeclaration(const Parse::TVariableDeclaration *ptNode);
	explicit VariableDeclaration(std::unique_ptr<Type> t, std::string id, std::unique_ptr<Expression> init = nullptr);
	std::string toCode() const override;

	bool equals(const VariableDeclaration *) const;
	[[gnu::pure]]
	bool idEquals(const VariableDeclaration *other) const;
	bool idEquals(std::string const& str) const;
	bool typeEquals(const VariableDeclaration *other) const;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope const& parentScope);
protected:
	std::unique_ptr<Type> type;
	std::string identifier;
	// nullable
	std::unique_ptr<Expression> initializer;

};

} //namespace AST
