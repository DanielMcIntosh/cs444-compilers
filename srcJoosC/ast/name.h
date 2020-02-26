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
	Name() = default;

	std::vector<std::string> prefix;
	std::string id;

	std::string flatten() const;
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);

	bool operator==(const Name &other);
};

} //namespace AST
