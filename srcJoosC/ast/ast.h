#pragma once
#include "frontend.h"

namespace AST {

EXPORT void astDumpDebugInfo(ASTResult const& result, const char *baseOutputPath);
EXPORT ASTResult buildAST(const Parse::Tree *root);

} // namespace AST
