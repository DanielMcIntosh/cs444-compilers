#pragma once

#include "ast/node.h"
#include <memory>

namespace AST
{

class Name;

class ImportDeclaration: public Node
{
public:
	static std::unique_ptr<ImportDeclaration> create(const Parse::Tree *ptNode);
	explicit ImportDeclaration(const Parse::TSingleTypeImportDeclaration *ptNode);
	explicit ImportDeclaration(const Parse::TTypeImportOnDemandDeclaration *ptNode);
	ImportDeclaration() = default;

	std::unique_ptr<Name> importName;
	bool multiImport;

	std::string toCode() const override;

	bool operator==(const ImportDeclaration &other);
};

} //namespace AST
