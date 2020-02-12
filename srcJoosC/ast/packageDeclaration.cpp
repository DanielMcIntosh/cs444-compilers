#include "ast/packageDeclaration.h"
#include "ast/node.h"
#include "ast/name.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<PackageDeclaration> PackageDeclaration::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return PackageDeclaration::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::PackageDeclaration:
		return std::make_unique<PackageDeclaration>(static_cast<const Parse::TPackageDeclaration*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for PackageDeclaration: " + std::to_string((int)ptNode->type));
	}
}
PackageDeclaration::PackageDeclaration(const Parse::TPackageDeclaration *ptNode)
{
}

} //namespace AST