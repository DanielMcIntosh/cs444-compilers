#include "frontend.h"

#include "parse/parseTreeBase.h"

void frontendResultDelete(FrontendResult *result) {
  delete [] result->fileContent;
  Parse::ptDelete(result->parseResult.treeRoot);
}
