#pragma once
#include "frontend.h"

namespace AST {

void astDumpDebugInfo(ASTResult const& result, const char *baseOutputPath);
ASTResult buildAST(const Parse::Tree *root);


} // namespace AST
