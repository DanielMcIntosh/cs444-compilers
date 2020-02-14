#pragma once

#include "semantic/semantic.h"

enum class MiddleendStageType {
	Semantic,
  Pass,
};

struct MiddleendResult {
	Semantic::SemanticDB semanticDB;

  enum MiddleendStageType failedStage = MiddleendStageType::Pass;
};
