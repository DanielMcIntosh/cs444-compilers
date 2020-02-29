#pragma once

#include "../frontend.h"
#include <vector>
#include <unordered_map>
#include <string>

namespace AST {

class CompilationUnit;
class TypeDeclaration;
class NameType;

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
	LocalVariableShadowing,
	FieldIdConflict,
	LocalVariableDNE,
	ExprResolution,
	DuplicateFieldDeclaration,
	DuplicateMethodDeclaration,
	DuplicateConstructorDeclaration,
	AbstractClassNotAbstract,
	AmbiguousReturnType,
	OverrideStatic,
	OverrideDifferentReturn,
	OverridePublic,
	OverrideFinal,
	TypeCheck,
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
  SemanticErrorType error;
  std::string errMsg;

  SemanticDB();
  ~SemanticDB() = default;

  std::tuple<AST::TypeDeclaration *, SemanticErrorType> resolveType(const AST::NameType *type, AST::TypeDeclaration *source) const;
  std::tuple<AST::TypeDeclaration *, SemanticErrorType> resolveType(const AST::NameType *type, const AST::CompilationUnit *cpu) const;
  std::tuple<AST::TypeDeclaration *, SemanticErrorType> resolveSingleImport(const AST::CompilationUnit *cpu, const std::string &simpleName) const;
  std::tuple<AST::TypeDeclaration *, SemanticErrorType> resolveMultiImport(const AST::CompilationUnit *cpu, const std::string &simpleName) const;
private:
  std::tuple<AST::TypeDeclaration *, SemanticErrorType> resolveTypeHelper(const AST::NameType *type, const std::string &typeName, const AST::CompilationUnit *cpu, AST::TypeDeclaration *source) const;
};

void semanticInit(SemanticDB *db, const std::vector<FrontendResult> &frontendResult);
void semanticDo(SemanticDB *sdb);

#define GOFAIL() { \
if (!Expression::gError.hasError) { \
char buffer[2048]; \
snprintf(buffer, ARRAY_SIZE(buffer), "\n%s\n%s:%d\n", __PRETTY_FUNCTION__, __FILE__, __LINE__); \
Expression::gError.hasError = true; \
Expression::gError.function = std::string(buffer); } \
goto fail;}

#define GOFAIL_IF_ERR(_err) if ((_err) != Semantic::SemanticErrorType::None) GOFAIL()
#define OK() return Semantic::SemanticErrorType::None

} // namespace Semantic

