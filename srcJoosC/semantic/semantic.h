#pragma once

#include "../frontend.h"
#include <vector>
#include <unordered_map>

using namespace std;
using namespace AST;

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

	Max
};

extern const char *gSemanticErrorTypeName[];

struct SemanticDB {
  vector<CompilationUnit *> cpus;
  unordered_map<string, TypeDeclaration *> typeMap;

  enum SemanticErrorType error = SemanticErrorType::None;
};

void semanticInit(SemanticDB *db, const vector<FrontendResult> &frontendResult);
void semanticDo(SemanticDB *sdb);
SemanticErrorType semanticResolveType(SemanticDB *db, Type *type, 
																			const string &typeName, const CompilationUnit *cpu,
																			TypeDeclaration *source);

} // namespace Semantic

