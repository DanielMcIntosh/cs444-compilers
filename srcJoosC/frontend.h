#pragma once

#include <mutex>
#include <string>
#include <vector>

#include "parse/parseTreeBase.h"
#include "utility.h"

namespace Scan {

using namespace std;

struct LexToken {
  string name;
  string lexeme;
};

struct ScanResult {
  vector<LexToken> tokens;
  bool valid;
  s32 errorPosition;
  string detailedStep;

  ScanResult();
};

}  // namespace Scan

namespace Parse {

struct ParseResult {
  Tree* treeRoot;
  s32 errorLexTokenIndex;
  bool valid;

  ParseResult();
};

}  // namespace Parse

namespace Weeder {

using namespace std;

enum class WeederCategory {
  // An abstract method cannot be static or final.
  ClassNotAbstractAndFinal,
  // A method has a body if and only if it is neither abstract nor native.
  MethodHasBodyIffNotAbstractNative,
  // A static method cannot be final.
  StaticMethodNoFinal,
  // A native method must be static.
  NativeMethodIsStatic,
  // An abstract method cannot be static or final.
  AbstractMethodNoStaticFinal,
  // An interface method cannot be static, final, or native.
  InterfaceNotStaticFinalNative,
  // Every class must contain at least one explicit constructor.
  ClassHasConstructor,
  // No field can be final.
  FieldNotFinal,
  // A method or constructor must not contain explicit this() or super() calls.
  MethodThisCall,
  // All integer literals are within the interval [-(1<<31), 1<<31)
  NoOverflow,
  // A class/interface must be declared in a .java file with the same base name
  // as the class/interface.
  FileNameMatchClass,
  // A class, class method or field must have exactly one access modifier
  AccessModifiers,
  // Reject illegal expressions in casts
  Cast,
  Max
};

struct WeederViolation {
  enum WeederCategory category;
  // name, location, etc
};

struct WeederResult {
  bool valid;

  mutex* theMutex;
  vector<WeederViolation> violations;

  WeederResult();
};

}  // namespace Weeder

namespace AST {

class Node;

struct ASTResult {
  std::shared_ptr<Node> ast;
};

}  // namespace AST

enum class FrontendStageType { Scan, Parse, Weed, Pass };

struct FrontendResult {
  std::string fileName;
  s32 fileSize;
  char* fileContent;

  FrontendStageType failedStage;

  Scan::ScanResult scanResult;
  Parse::ParseResult parseResult;
  Weeder::WeederResult weederResult;
  AST::ASTResult astResult;
};

void frontendResultDelete(FrontendResult* result);
