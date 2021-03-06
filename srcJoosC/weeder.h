#pragma once

#include "frontend.h"
#include "parse/parseTreeBase.h"

namespace Weeder {

EXPORT WeederResult weederCheck(Parse::Tree* root, const char* fileName);

}  // namespace Weeder
