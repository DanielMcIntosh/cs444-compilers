#pragma once

#include "ast/expression.h"
#include <memory>
#include <string>

namespace AST
{

class Type;

class VariableDeclaration: public Node
{
public:
	static std::unique_ptr<VariableDeclaration> create(const Parse::Tree *ptNode);
	explicit VariableDeclaration(const Parse::TFormalParameter *ptNode);
	explicit VariableDeclaration(const Parse::TVariableDeclaration *ptNode);
	std::string toCode() const override;

	bool equals(const VariableDeclaration *) const;
	[[gnu::pure]]
	bool idEquals(const VariableDeclaration *other) const;
	bool typeEquals(const VariableDeclaration *other) const;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);
protected:
	std::unique_ptr<Type> type;
	std::string identifier;
	// nullable
	std::unique_ptr<Expression> initializer;

};

} //namespace AST
