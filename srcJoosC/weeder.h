#pragma once

#include "parse/parseTreeBase.h"
#include "frontend.h"

namespace Weeder {

WeederResult weederCheck(Parse::Tree *root, const char *fileName);

} // namespace Weeder
