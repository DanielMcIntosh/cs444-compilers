#include "weeder.h"

#include <filesystem>
#include <thread>

#include "parse/parseTree.h"

namespace fs = std::filesystem;

namespace Weeder {

using namespace Parse;

void weederCheckClassNotAbstractAndFinal(Tree* root, WeederResult* result) {
  for (auto* cls : ptFindByType(root, ClassDeclaration)) {
    bool is_abstract = false;
    bool is_final = false;
    for (auto* modifier : ptFindByType(cls, Modifier)) {
      is_abstract |= modifier->v == TModifierV::abstract;
      is_final |= modifier->v == TModifierV::final;
    }
    // A class cannot be both abstract and final.
    if (is_abstract && is_final) {
      scoped_lock lock(*result->theMutex);
      result->violations.push_back({WeederCategory::ClassNotAbstractAndFinal});
      return;
    }
  }
}

void weederCheckMethodModifiers(Tree* root, WeederResult* result) {
  for (auto* method : ptFindByType(root, MethodDeclaration)) {
    bool has_body = method->methodBody->v == TMethodBodyV::Block;
    bool is_abstract = false;
    bool is_static = false;
    bool is_final = false;
    bool is_native = false;
    for (auto* modifier : ptFindByType(method, Modifier)) {
      is_abstract |= modifier->v == TModifierV::abstract;
      is_static |= modifier->v == TModifierV::Static;
      is_final |= modifier->v == TModifierV::final;
      is_native |= modifier->v == TModifierV::native;
    }
    // A method has a body if and only if it is neither abstract nor native.
    // https://www.wolframalpha.com/input/?i=%21%28a+%3C%3D%3E+%28%21b+%26+%21c%29%29
    // https://www.wolframalpha.com/input/?i=%28a+%26+%28b+%7C+c%29%29+%7C++%28%21a+%26+%21%28b+%7C+c%29%29
    if ((has_body && (is_abstract || is_native)) ||
        (!has_body && !(is_abstract || is_native))) {
      scoped_lock lock(*result->theMutex);
      result->violations.push_back(
          {WeederCategory::MethodHasBodyIffNotAbstractNative});
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
      result->violations.push_back(
          {WeederCategory::AbstractMethodNoStaticFinal});
      return;
    }
  }
}

void weederCheckInterfaceNotStaticFinalNative(Tree* root,
                                              WeederResult* result) {
  for (auto* interface : ptFindByType(root, InterfaceDeclaration)) {
    for (auto* method : ptFindByType(interface, AbstractMethodDeclaration)) {
      for (auto* modifier : ptFindByType(method, Modifier)) {
        // An interface method cannot be static, final, or native.
        if (modifier->v == TModifierV::Static ||
            modifier->v == TModifierV::final ||
            modifier->v == TModifierV::native) {
          scoped_lock lock(*result->theMutex);
          result->violations.push_back(
              {WeederCategory::InterfaceNotStaticFinalNative});
          return;
        }
      }
    }
  }
}

void weederCheckClassHasConstructor(Tree* root, WeederResult* result) {
  for (auto* cls : ptFindByType(root, ClassDeclaration)) {
    // Every class must contain at least one explicit constructor.
    if (ptFindByType(cls, ConstructorDeclaration).size() == 0) {
      scoped_lock lock(*result->theMutex);
      result->violations.push_back({WeederCategory::ClassHasConstructor});
      return;
    }
  }
}

void weederCheckFieldNotFinal(Tree* root, WeederResult* result) {
  for (auto* field : ptFindByType(root, FieldDeclaration)) {
    for (auto* modifier : ptFindByType(field, Modifier)) {
      // No field can be final.
      if (modifier->v == TModifierV::final) {
        scoped_lock lock(*result->theMutex);
        result->violations.push_back({WeederCategory::FieldNotFinal});
        return;
      }
    }
  }
}

// All integer literals are within the interval [-(1<<31), 1<<31)
// TODO: refactor
void weederCheckNoOverflow(Tree* root, WeederResult* result) {
  int overflow_count = 0;
  for (auto* literal : ptFindByType(root, IntegerLiteral)) {
    if (literal->value == (1u << 31))
      ++overflow_count;
  }
  for (auto* expr : ptFindByType(root, UnaryExpression)) {
    if (expr->v == TUnaryExpressionV::MinusUnaryExpression) {
      if (expr->unaryExpression->v ==
          TUnaryExpressionV::UnaryExpressionNotPlusMinus) {
        auto inner_expr = expr->unaryExpression->unaryExpressionNotPlusMinus;
        if (inner_expr->v == TUnaryExpressionNotPlusMinusV::Primary &&
            inner_expr->primary->v == TPrimaryV::PrimaryNoNewArray &&
            inner_expr->primary->primaryNoNewArray->v ==
                TPrimaryNoNewArrayV::Literal &&
            inner_expr->primary->primaryNoNewArray->literal->v ==
                TLiteralV::IntegerLiteral) {
          auto literal =
              inner_expr->primary->primaryNoNewArray->literal->integerLiteral;
          if (literal->value == (1u << 31))
            --overflow_count;
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

void weederCheckFileNameMatchClass(Tree* root,
                                   const char* fullPath,
                                   WeederResult* result) {
  bool valid = true;
  fs::path p(fullPath);
  if (p.extension() != ".java") {
    valid = false;
  } else {
    for (auto* cls : ptFindByType(root, ClassDeclaration)) {
      if (cls->identifier->value != p.stem()) {
        valid = false;
        break;
      }
    }
    for (auto* interface : ptFindByType(root, InterfaceDeclaration)) {
      if (interface->identifier->value != p.stem()) {
        valid = false;
        break;
      }
    }
  }
  // A class/interface must be declared in a .java file with the same base name
  // as the class/interface.
  if (!valid) {
    scoped_lock lock(*result->theMutex);
    result->violations.push_back({WeederCategory::FileNameMatchClass});
    return;
  }
}

// TODO: refactor
void weederCheckAccessModifiers(Tree* root, WeederResult* result) {
  for (auto* declaration : ptFindByType(root, ClassDeclaration)) {
    int class_access_modifiers = 0;
    // class declaration
    for (auto* modifier : ptFindByType(declaration->modifiers, Modifier)) {
      if (modifier->v == TModifierV::Public ||
          modifier->v == TModifierV::Protected) {
        ++class_access_modifiers;
      }
    }
    if (class_access_modifiers != 1) {
      scoped_lock lock(*result->theMutex);
      result->violations.push_back({WeederCategory::AccessModifiers});
      return;
    }
    // class method declaration
    for (auto* method : ptFindByType(declaration, MethodDeclaration)) {
      int method_access_modifiers = 0;
      for (auto* modifier : ptFindByType(method, Modifier)) {
        if (modifier->v == TModifierV::Public ||
            modifier->v == TModifierV::Protected) {
          ++method_access_modifiers;
        }
      }
      if (method_access_modifiers != 1) {
        scoped_lock lock(*result->theMutex);
        result->violations.push_back({WeederCategory::AccessModifiers});
        return;
      }
    }
    // class field declaration
    for (auto* method : ptFindByType(declaration, FieldDeclaration)) {
      int field_access_modifiers = 0;
      for (auto* modifier : ptFindByType(method, Modifier)) {
        if (modifier->v == TModifierV::Public ||
            modifier->v == TModifierV::Protected) {
          ++field_access_modifiers;
        }
      }
      if (field_access_modifiers != 1) {
        scoped_lock lock(*result->theMutex);
        result->violations.push_back({WeederCategory::AccessModifiers});
        return;
      }
    }
  }
}

// Reject illegal expressions in casts
void weederCheckCast(Tree* root, WeederResult* result) {
  bool fail = false;
  for (auto* cast : ptFindByType(root, CastExpression)) {
    if (cast->v ==
        TCastExpressionV::LParExpressionRParUnaryExpressionNotPlusMinus) {
      fail = true;
      auto expression = cast->expression;
      if (expression->assignmentExpression->v !=
          TAssignmentExpressionV::ConditionalOrExpression)
        break;
      auto assignmentExpression = expression->assignmentExpression;
      if (assignmentExpression->conditionalOrExpression->v !=
          TConditionalOrExpressionV::ConditionalAndExpression)
        break;
      auto conditionalOrExpression =
          assignmentExpression->conditionalOrExpression;
      if (conditionalOrExpression->conditionalAndExpression->v !=
          TConditionalAndExpressionV::InclusiveOrExpression)
        break;
      auto conditionalAndExpression =
          conditionalOrExpression->conditionalAndExpression;
      if (conditionalAndExpression->inclusiveOrExpression->v !=
          TInclusiveOrExpressionV::AndExpression)
        break;
      auto inclusiveOrExpression =
          conditionalAndExpression->inclusiveOrExpression;
      if (inclusiveOrExpression->andExpression->v !=
          TAndExpressionV::EqualityExpression)
        break;
      auto andExpression = inclusiveOrExpression->andExpression;
      if (andExpression->equalityExpression->v !=
          TEqualityExpressionV::RelationalExpression)
        break;
      auto equalityExpression = andExpression->equalityExpression;
      if (equalityExpression->relationalExpression->v !=
          TRelationalExpressionV::AdditiveExpression)
        break;
      auto relationalExpression = equalityExpression->relationalExpression;
      if (relationalExpression->additiveExpression->v !=
          TAdditiveExpressionV::MultiplicativeExpression)
        break;
      auto additiveExpression = relationalExpression->additiveExpression;
      if (additiveExpression->multiplicativeExpression->v !=
          TMultiplicativeExpressionV::UnaryExpression)
        break;
      auto multiplicativeExpression =
          additiveExpression->multiplicativeExpression;
      if (multiplicativeExpression->unaryExpression->v !=
          TUnaryExpressionV::UnaryExpressionNotPlusMinus)
        break;
      auto unaryExpression = multiplicativeExpression->unaryExpression;
      if (unaryExpression->unaryExpressionNotPlusMinus->v !=
          TUnaryExpressionNotPlusMinusV::Name)
        break;
    }
    fail = false;
  }
  if (fail) {
    scoped_lock lock(*result->theMutex);
    result->violations.push_back({WeederCategory::Cast});
    return;
  }
}

WeederResult weederCheck(Tree* root, const char* fileName) {
  WeederResult result;
  result.theMutex = new mutex;
  weederCheckClassNotAbstractAndFinal(root, &result);
  weederCheckMethodModifiers(root, &result);
  weederCheckInterfaceNotStaticFinalNative(root, &result);
  weederCheckClassHasConstructor(root, &result);
  weederCheckFieldNotFinal(root, &result);
  weederCheckNoOverflow(root, &result);
  weederCheckFileNameMatchClass(root, fileName, &result);
  weederCheckAccessModifiers(root, &result);
  weederCheckCast(root, &result);

  {
    scoped_lock lock(*result.theMutex);
    result.valid = result.violations.empty();
  }

  delete result.theMutex;
  result.theMutex = nullptr;
  return result;
}

}  // namespace Weeder
