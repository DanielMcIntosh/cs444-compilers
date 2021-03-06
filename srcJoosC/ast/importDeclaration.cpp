#include "ast/importDeclaration.h"
#include "ast/node.h"
#include "ast/name.h"
#include "ast/type.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<ImportDeclaration> ImportDeclaration::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return ImportDeclaration::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::SingleTypeImportDeclaration:
		return std::make_unique<ImportDeclaration>(static_cast<const Parse::TSingleTypeImportDeclaration*>(ptNode));
	case Parse::NonTerminalType::TypeImportOnDemandDeclaration:
		return std::make_unique<ImportDeclaration>(static_cast<const Parse::TTypeImportOnDemandDeclaration*>(ptNode));
	default:
		FAILED("inappropriate PT type for ImportDeclaration: " + std::to_string((int)ptNode->type));
	}
}

ImportDeclaration::ImportDeclaration(const Parse::TSingleTypeImportDeclaration *ptNode):
importName(Name::create(ptNode->name)), multiImport(false)
{
	nodeType = NodeType::ImportDeclaration;
}
ImportDeclaration::ImportDeclaration(const Parse::TTypeImportOnDemandDeclaration *ptNode):
importName(Name::create(ptNode->name)), multiImport(true)
{
	nodeType = NodeType::ImportDeclaration;
}

std::string ImportDeclaration::toCode() const
{
	std::string str = "import " + importName->toCode();
	if (multiImport)
	{
		str += ".*";
	}
	str += ";";
	return str;
}

bool ImportDeclaration::operator==(const ImportDeclaration &other) {
	return *importName == *other.importName && multiImport == other.multiImport;
}

} //namespace AST
