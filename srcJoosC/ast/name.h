#pragma once

#include "ast/node.h"
#include <memory>
#include <vector>
#include <string>
#include <variant>

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
	class Scope;
}

namespace AST
{

class TypeDeclaration;
class Expression;
class NameType;

class Name: public Node
{
public:
	static std::unique_ptr<Name> create(const Parse::Tree *ptNode);
	explicit Name(const Parse::TName *ptNode);
	explicit Name(std::vector<std::string> idList);

	std::string flatten() const;
	std::string toCode() const override;
	std::string getId() const;

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);
	Semantic::SemanticErrorType resolveExprs(Semantic::Scope const& scope);

	bool operator==(const Name &other);


	std::vector<std::string> ids;
protected:
	// pre-computed during type resolution in case expression-resolution reaches rule 3 and has to resolve a_1.a_2. ... a_k to a Type
	std::unique_ptr<NameType> typePrefix;

	std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>> converted;

	friend class NameExpression;
	friend class NameType;
};

} //namespace AST
