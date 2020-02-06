#pragma once

#include "parserASTBase.h"
#include "scanParse.h"

namespace Weeder {

WeederResult weederCheck(Parse::Tree *root, const char *fileName);
  
} // namespace Weeder
