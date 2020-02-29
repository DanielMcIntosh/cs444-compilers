#include "frontend.h"

#include "parse/parseTreeBase.h"

void frontendResultDelete(FrontendResult* result) {
  delete[] result->fileContent;
  Parse::ptDelete(result->parseResult.treeRoot);
}

Scan::ScanResult::ScanResult() : valid(false), errorPosition(-1) {

}

Parse::ParseResult::ParseResult() : treeRoot(nullptr), errorLexTokenIndex(-1),
 valid(false) {

}

Weeder::WeederResult::WeederResult(): valid(false), theMutex(nullptr) {

}

bool gStandAloneMode;
thread_local int gTestIndex;
