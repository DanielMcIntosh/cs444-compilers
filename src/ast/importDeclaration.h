#pragma once

#include "ast/node.h"
#include "ast/name.h"
#include <memory>

namespace AST
{

class ImportDeclaration: public Node
{
public:
	ImportDeclaration(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Name> importName;
	bool multiImport;
};

} //namespace AST
