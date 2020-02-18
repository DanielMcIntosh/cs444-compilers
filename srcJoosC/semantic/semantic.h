#pragma once

#include "../frontend.h"
#include "ast/compilationUnit.h"
#include "ast/typeDeclaration.h"
#include <vector>
#include <unordered_map>

using namespace std;
using namespace AST;

namespace Semantic {

// Please also update error string
enum class SemanticErrorType {
	None,
	SingleImportAmbiguous,
	MultiImportAmbiguous,
	NotFoundImport,
	MultipleDefinitionOfClassInterface,
	CycleInHierarchy,

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

} // namespace Semantic

