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
		FAILED("inappropriate PT type for CompilationUnit: " + std::to_string((int)ptNode->type));
	}
}
CompilationUnit::CompilationUnit(const Parse::TCompilationUnit *ptNode)
{
	Type::setCurrentCompilationUnit(this);
	package = Name::create((ptNode->packageDeclaration) ? ptNode->packageDeclaration->name : nullptr);
	imports = std::move(NodeList<ImportDeclaration>(ptNode->importDeclarations).list);
	typeDeclaration = TypeDeclaration::create(ptNode->typeDeclaration);
	resolveEnclosingPackageAndApplyToTypeDecl();
}

void CompilationUnit::resolveEnclosingPackageAndApplyToTypeDecl() {
  if (!typeDeclaration)
    return;

  std::string thePackage;
  if (!package)
    thePackage = "java._global";
  else {
    for (const auto &s: package->prefix) {
      thePackage.append(s);
      thePackage.append(".");
    }
    thePackage.append(package->id);
  }

  packageName = thePackage;
  typeDeclaration->fqn = thePackage + "." + typeDeclaration->name;
	typeDeclaration->cpu = this;
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

void CompilationUnit::importDeduplication() {
	for (size_t i = 0; i < imports.size(); ++i) {
		for (size_t j = i + 1; j < imports.size(); ++j) {
			if (imports[i] && imports[j] && *imports[i] == *imports[j]) {
				imports[j] = nullptr;
			}
		}
	}
	size_t left = 0;
	for (size_t i = 0; i < imports.size(); ++i) {
		if (imports[i]) {
			if (left < i) {
				imports[left] = std::move(imports[i]);
			}
			++left;
		}
	}
	imports.resize(left);
}

} //namespace AST
