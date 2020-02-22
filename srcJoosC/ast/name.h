#pragma once

#include "ast/expression.h"
#include "ast/type.h"
#include "semantic/semantic.h"
#include <memory>
#include <vector>
#include <string>

namespace AST
{

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

	bool operator==(const Name &other);
};

class NameType: public Type
{
public:
	static std::unique_ptr<NameType> create(const Parse::Tree *ptNode);
	explicit NameType(Name&& other);

	std::string flatten() const;
	Semantic::SemanticErrorType resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

	std::vector<std::string> prefix;
	std::string id;

	TypeDeclaration *declaration = nullptr;

	virtual bool equals(NameType *) override;

	std::string toCode() const override;
};

class NameExpression: public Expression
{
public:
	std::vector<std::string> prefix;
	std::string id;

	explicit NameExpression(Name&& other);

	std::string toCode() const override;
};

} //namespace AST
