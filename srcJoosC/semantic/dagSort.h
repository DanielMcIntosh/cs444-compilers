#pragma once

#include "utility.h"
#include <vector>

namespace AST {
	class TypeDeclaration;
}

namespace Semantic {

EXPORT bool dagSort(std::vector<AST::TypeDeclaration *> &allTypes);

} // namespace Semantic

