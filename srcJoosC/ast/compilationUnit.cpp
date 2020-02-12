#include "ast/compilationUnit.h"
#include "ast/node.h"
#include "ast/importDeclaration.h"
#include "ast/typeDeclaration.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"
#include <memory>
#include <vector>
#include <string>

namespace AST
{

// static
std::unique_ptr<CompilationUnit> CompilationUnit::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::CompilationUnit:
		return std::make_unique<CompilationUnit>(static_cast<const Parse::TCompilationUnit*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for CompilationUnit: " + std::to_string((int)ptNode->type));
	}
}
CompilationUnit::CompilationUnit(const Parse::TCompilationUnit *ptNode)
  : package(Name::create((ptNode->packageDeclaration) ? ptNode->packageDeclaration->name : nullptr)),
	imports(std::move(NodeList<ImportDeclaration>(ptNode->importDeclarations).list)),
	typeDeclaration(TypeDeclaration::create(ptNode->typeDeclaration))
{
}

std::string CompilationUnit::toCode()
{
	std::string str;
	if (package)
	{
		str += "package " + package->toCode() + ";\n";
	}
	for (auto &imp : imports)
	{
		str += imp->toCode();
	}
	str += "\n";
	str += typeDeclaration->toCode();

	return str;
}

} //namespace AST
