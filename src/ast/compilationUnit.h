#pragma once

#include "ast/node.h"
#include "ast/name.h"
#include "ast/importDeclaration.h"
#include "ast/typeDeclaration.h"
#include <memory>
#include <vector>

namespace AST
{

class CompilationUnit: public Node
{
public:
	CompilationUnit(std::vector<Parser::ASTToken>& children);

	// nullable
	std::shared_ptr<Name> package;
	std::vector<std::shared_ptr<ImportDeclaration>> imports;
	// nullable
	std::shared_ptr<TypeDeclaration> typeDeclaration;
};

} //namespace AST
