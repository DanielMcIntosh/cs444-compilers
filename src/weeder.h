#pragma once

#include "parserASTBase.h"
#include "scanParse.h"

namespace Weeder {

WeederResult weederCheck(Parse::Tree *root);
  
} // namespace Weeder
