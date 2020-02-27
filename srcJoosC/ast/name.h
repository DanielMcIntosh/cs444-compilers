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

	bool operator==(const Name &other);

	Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass);
	Semantic::SemanticErrorType disambiguate(Semantic::Scope const& scope);

private:
	void buildConverted(std::unique_ptr<Expression> expr, unsigned int idStart);
	void buildConverted(std::unique_ptr<NameType> type, unsigned int idStart);

public:
	std::vector<std::string> ids;
	// we pre-compute during type resolution the result of rule3 of namespace disambiguation
	std::variant<std::unique_ptr<Expression>, std::unique_ptr<NameType>> converted;
};

} //namespace AST
