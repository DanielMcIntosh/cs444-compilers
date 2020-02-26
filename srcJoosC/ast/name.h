#pragma once

#include "ast/expression.h"
#include "ast/type.h"
#include <memory>
#include <vector>
#include <string>

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
}

namespace AST
{

class TypeDeclaration;

class Name: public Node
{
public:
	static std::unique_ptr<Name> create(const Parse::Tree *ptNode);
	explicit Name(const Parse::TName *ptNode);
	explicit Name(std::vector<std::string> pre, std::string identifier);

	std::vector<std::string> prefix;
	std::string id;
protected:
	// pre-computed during type resolution in case expression-resolution reaches rule 3 and has to resolve a_1.a_2. ... a_k to a Type
	std::unique_ptr<Type> typePrefix;

	friend class NameExpression;
	friend class NameType;
public:
	std::string flatten() const;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);

	bool operator==(const Name &other);
};

} //namespace AST
