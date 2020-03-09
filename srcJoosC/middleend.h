#pragma once

#include "semantic/semantic.h"

#include <vector>
#include <string>

enum class MiddleendStageType {
	Semantic,
  Pass,
};

struct MiddleendResult {
	Semantic::SemanticDB semanticDB;

  enum MiddleendStageType failedStage = MiddleendStageType::Pass;
};

struct SFile {
	std::string fileName;
	std::string fileContent;
};

struct BackendResult {
	std::vector<SFile> sFiles;
};
