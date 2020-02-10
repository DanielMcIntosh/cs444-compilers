#pragma once

enum class MiddleendStageType {
  Pass,
};

struct MiddleendResult {
  enum MiddleendStageType failedStage = MiddleendStageType::Pass;
};
