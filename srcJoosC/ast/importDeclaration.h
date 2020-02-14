#pragma once

#include "ast/node.h"
#include "ast/name.h"
#include <memory>

namespace AST
{

class ImportDeclaration: public Node
{
public:
	static std::unique_ptr<ImportDeclaration> create(const Parse::Tree *ptNode);
	ImportDeclaration(const Parse::TSingleTypeImportDeclaration *ptNode);
	ImportDeclaration(const Parse::TTypeImportOnDemandDeclaration *ptNode);

	std::unique_ptr<Name> importName;
	bool multiImport;

	std::string toCode() override;
};

} //namespace AST
