#pragma once

#include "../frontend.h"
#include <vector>
#include <unordered_map>
#include <string>

namespace AST {
	class CompilationUnit;
	class TypeDeclaration;
}

namespace AST {

class CompilationUnit;
class TypeDeclaration;
class Type;

}

namespace Semantic {

// Please also update error string
enum class SemanticErrorType {
	None,
	SingleImportAmbiguous,
	MultiImportAmbiguous,
	NotFoundImport,
	MultipleDefinitionOfClassInterface,
	CycleInHierarchy,
	ImplementSameInterface,
	ExtendImplementSame,
	ImplementNonInterface,
	ExtendNonClass,
	ExtendClass,
	ExtendFinalClass,
	TypeDeclarationClashImport,
	PrefixNameIsType,
	NotPackage,

	Max
};

extern const char *gSemanticErrorTypeName[];

struct Trie;

struct Trie {
	Trie();
	std::string name;
	AST::TypeDeclaration *theTypeDecl = nullptr;
	std::vector<std::unique_ptr<Trie>> children;
};

struct SemanticDB {
  std::vector<AST::CompilationUnit *> cpus;
  std::unordered_map<std::string, AST::TypeDeclaration *> typeMap;
  Trie packageTrie;

  enum SemanticErrorType error = SemanticErrorType::None;
};

void semanticInit(SemanticDB *db, const std::vector<FrontendResult> &frontendResult);
void semanticDo(SemanticDB *sdb);
SemanticErrorType semanticResolveType(SemanticDB *db, AST::Type *type,
																			const std::string &typeName, const AST::CompilationUnit *cpu,
																			AST::TypeDeclaration *source);

} // namespace Semantic

