#include "weeder.h"
#include "parserAST.h"

namespace Weeder {

using namespace Parse;

void weederCheckInterfaceNoStaticFinalNative(Tree *root, WeederResult *result) {
  auto interfaces = parserASTFindByType(root, InterfaceDeclaration);
  for (Tree *id: interfaces) {
    auto methods = parserASTFindByType(id, AbstractMethodDeclaration);
    for (Tree *method: methods) {
      auto modifiers = parserASTFindByType(method, Modifier);
      for (TreeModifier *modifier: modifiers) {
        if (modifier->variant == NTModifierVariants::Static ||
            modifier->variant == NTModifierVariants::final ||
            modifier->variant == NTModifierVariants::native) {
          scoped_lock lock(*result->theMutex);
          result->violations.push_back({WeederCategory::InterfaceNoStaticFinalNative});
          return;
        }
      }
    }
  }
}

WeederResult weederCheck(Tree *root) {
  WeederResult result;
  result.theMutex = new mutex;
  weederCheckInterfaceNoStaticFinalNative(root, &result);

  {
    scoped_lock lock(*result.theMutex);
    result.valid = result.violations.empty();
  }

  delete result.theMutex;
  result.theMutex = nullptr;
  return result;
}

} // namespace Weeder
