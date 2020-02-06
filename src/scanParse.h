#pragma once

#include <vector>
#include <string>
#include <mutex>

#include "utility.h"
#include "pt/parserASTBase.h"

namespace Scan {

using namespace std;

struct LexToken {
	string name;
	string lexeme;
};

struct ScanResult {
	vector<LexToken> tokens;
	bool valid = false;
	s32 errorPosition = -1;
	string detailedStep;
};

}

namespace Parse {

struct ParseResult {
  Tree *treeRoot = nullptr;
  s32 errorLexTokenIndex = -1;
  bool valid = false;
};

}

namespace Weeder {

using namespace std;

enum class WeederCategory
{
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
  // A class/interface must be declared in a .java file with the same base name as the class/interface.
  FileNameMatchClass,
  Max
};

struct WeederViolation {
  enum WeederCategory category;
  // name, location, etc
};

struct WeederResult {
  bool valid = false;

  // TODO: parallalize weeding process
  mutex *theMutex;
  vector<WeederViolation> violations;

};

}
