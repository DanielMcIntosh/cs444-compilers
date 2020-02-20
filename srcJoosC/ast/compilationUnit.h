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
	static std::unique_ptr<CompilationUnit> create(const Parse::Tree *ptNode);
	explicit CompilationUnit(const Parse::TCompilationUnit *ptNode);

	// nullable
	std::unique_ptr<Name> package;
	std::vector<std::unique_ptr<ImportDeclaration>> imports;
	// nullable
	std::unique_ptr<TypeDeclaration> typeDeclaration;

	std::string toCode() const override;

	std::string packageName;

	// apply package name to all type declarations under this node
	void resolveEnclosingPackageAndApplyToTypeDecl();
	// remove imports that are exactly the same
	void importDeduplication();
};

} //namespace AST
