#pragma once

#include "ast/node.h"
#include "ast/name.h"
#include <memory>

namespace AST
{

class PackageDeclaration: public Node
{
public:
	static std::unique_ptr<PackageDeclaration> create(const Parse::Tree *ptNode);
	explicit PackageDeclaration(const Parse::TPackageDeclaration *ptNode);

	std::unique_ptr<Name> packageName;

	std::string toCode() override;
};

} //namespace AST
