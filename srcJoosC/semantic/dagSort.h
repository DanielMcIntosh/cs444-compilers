#pragma once
#include <vector>

namespace AST {
	class TypeDeclaration;
}

namespace Semantic {

bool dagSort(std::vector<AST::TypeDeclaration *> &allTypes);

} // namespace Semantic

