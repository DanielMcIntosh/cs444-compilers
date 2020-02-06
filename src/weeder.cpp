#include "weeder.h"

#ifndef PARSERAST_DISABLED
#include "pt/parserAST.h"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

namespace Weeder {

using namespace Parse;

#ifndef PARSERAST_DISABLED

void weederCheckClassNotAbstractAndFinal(Tree *root, WeederResult *result) {
  for (auto *cls: parserASTFindByType(root, ClassDeclaration)) {
    bool is_abstract = false;
    bool is_final = false;
    for (auto *modifier: parserASTFindByType(cls, Modifier)) {
      is_abstract |= modifier->variant == NTModifierVariants::abstract;
      is_final |= modifier->variant == NTModifierVariants::final;
    }
    // A class cannot be both abstract and final.
    if (is_abstract && is_final) {
      scoped_lock lock(*result->theMutex);
      result->violations.push_back({WeederCategory::ClassNotAbstractAndFinal});
      return;
    }
  }
}

void weederCheckMethodModifiers(Tree *root, WeederResult *result) {
  for (auto *method: parserASTFindByType(root, MethodDeclaration)) {
    bool has_body = method->methodBody->variant == NTMethodBodyVariants::Block;
    bool is_abstract = false;
    bool is_static = false;
    bool is_final = false;
    bool is_native = false;
    for (auto *modifier: parserASTFindByType(method, Modifier)) {
      is_abstract |= modifier->variant == NTModifierVariants::abstract;
      is_static |= modifier->variant == NTModifierVariants::Static;
      is_final |= modifier->variant == NTModifierVariants::final;
      is_native |= modifier->variant == NTModifierVariants::native;
    }
    // A method has a body if and only if it is neither abstract nor native.
    // https://www.wolframalpha.com/input/?i=%21%28a+%3C%3D%3E+%28%21b+%26+%21c%29%29
    // https://www.wolframalpha.com/input/?i=%28a+%26+%28b+%7C+c%29%29+%7C++%28%21a+%26+%21%28b+%7C+c%29%29
    if ((has_body && (is_abstract || is_native)) || (!has_body && !(is_abstract || is_native))) {
      scoped_lock lock(*result->theMutex);
      result->violations.push_back({WeederCategory::MethodHasBodyIffNotAbstractNative});
      return;
    }
    // A static method cannot be final.
    if (is_static && is_final) {
      scoped_lock lock(*result->theMutex);
      result->violations.push_back({WeederCategory::StaticMethodNoFinal});
      return;
    }
    // A native method must be static.
    if (is_native && !is_static) {
      scoped_lock lock(*result->theMutex);
      result->violations.push_back({WeederCategory::NativeMethodIsStatic});
      return;
    }
    // An abstract method cannot be static or final.
    if (is_abstract && (is_static || is_final)) {
      scoped_lock lock(*result->theMutex);
      result->violations.push_back({WeederCategory::AbstractMethodNoStaticFinal});
      return;
    }
  }
}

void weederCheckInterfaceNotStaticFinalNative(Tree *root, WeederResult *result) {
  for (auto *interface: parserASTFindByType(root, InterfaceDeclaration)) {
    for (auto *method: parserASTFindByType(interface, AbstractMethodDeclaration)) {
      for (auto *modifier: parserASTFindByType(method, Modifier)) {
        // An interface method cannot be static, final, or native.
        if (modifier->variant == NTModifierVariants::Static ||
            modifier->variant == NTModifierVariants::final ||
            modifier->variant == NTModifierVariants::native) {
          scoped_lock lock(*result->theMutex);
          result->violations.push_back({WeederCategory::InterfaceNotStaticFinalNative});
          return;
        }
      }
    }
  }
}

void weederCheckClassHasConstructor(Tree *root, WeederResult *result) {
  for (auto *cls: parserASTFindByType(root, ClassDeclaration)) {
    // Every class must contain at least one explicit constructor.
    if (parserASTFindByType(cls, ConstructorDeclaration).size() == 0) {
      scoped_lock lock(*result->theMutex);
      result->violations.push_back({WeederCategory::ClassHasConstructor});
      return;
    }
  }
}

void weederCheckFieldNotFinal(Tree *root, WeederResult *result) {
  for (auto *field: parserASTFindByType(root, FieldDeclaration)) {
    for (auto *modifier: parserASTFindByType(field, Modifier)) {
      // No field can be final.
      if (modifier->variant == NTModifierVariants::final) {
        scoped_lock lock(*result->theMutex);
        result->violations.push_back({WeederCategory::FieldNotFinal});
        return;
      }
    }
  }
}

// All integer literals are within the interval [-(1<<31), 1<<31)
// TODO: refactor
void weederCheckNoOverflow(Tree *root, WeederResult *result) {
  int overflow_count = 0;
  for (auto *literal: parserASTFindByType(root, IntegerLiteral)) {
    if (literal->value == (1u<<31)) ++overflow_count;
  }
  for (auto *expr: parserASTFindByType(root, UnaryExpression)) {
    if (expr->variant == NTUnaryExpressionVariants::MinusUnaryExpression) {
      if (expr->unaryExpression->variant == NTUnaryExpressionVariants::UnaryExpressionNotPlusMinus) {
        auto inner_expr = expr->unaryExpression->unaryExpressionNotPlusMinus;
        if (inner_expr->variant == NTUnaryExpressionNotPlusMinusVariants::Primary &&
            inner_expr->primary->variant == NTPrimaryVariants::PrimaryNoNewArray &&
            inner_expr->primary->primaryNoNewArray->variant == NTPrimaryNoNewArrayVariants::Literal &&
            inner_expr->primary->primaryNoNewArray->literal->variant == NTLiteralVariants::IntegerLiteral) {
          auto literal = inner_expr->primary->primaryNoNewArray->literal->integerLiteral;
          if (literal->value == (1u<<31)) --overflow_count;
        }
      }
    }
  }
  if (overflow_count > 0) {
    scoped_lock lock(*result->theMutex);
    result->violations.push_back({WeederCategory::NoOverflow});
    return;
  }
}

void weederCheckFileNameMatchClass(Tree *root, const char *fullPath, WeederResult *result) {
  bool valid = true;
  fs::path p(fullPath);
  if (p.extension() != ".java") {
    valid = false;
  } else {
    for (auto *cls: parserASTFindByType(root, ClassDeclaration)) {
      if (cls->identifier->value != p.stem()) {
        valid = false;
        break;
      }
    }
    for (auto *interface: parserASTFindByType(root, InterfaceDeclaration)) {
      if (interface->identifier->value != p.stem()) {
        valid = false;
        break;
      }
    }
  }
  // A class/interface must be declared in a .java file with the same base name as the class/interface.
  if (!valid) {
    scoped_lock lock(*result->theMutex);
    result->violations.push_back({WeederCategory::FileNameMatchClass});
    return;
  }
}

WeederResult weederCheck(Tree *root, const char *fileName) {
  WeederResult result;
  result.theMutex = new mutex;
  weederCheckClassNotAbstractAndFinal(root, &result);
  weederCheckMethodModifiers(root, &result);
  weederCheckInterfaceNotStaticFinalNative(root, &result);
  weederCheckClassHasConstructor(root, &result);
  weederCheckFieldNotFinal(root, &result);
  weederCheckNoOverflow(root, &result);
  weederCheckFileNameMatchClass(root, fileName, &result);

  {
    scoped_lock lock(*result.theMutex);
    result.valid = result.violations.empty();
  }

  delete result.theMutex;
  result.theMutex = nullptr;
  return result;
}

#else

WeederResult weederCheck(Tree *root, const char *fileName) {
  WeederResult result;
  return result;
}

#endif // PARSERAST_DISABLED

} // namespace Weeder
