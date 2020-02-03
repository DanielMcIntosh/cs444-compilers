#pragma once

#include <vector>
#include <string>
#include <mutex>

#include "utility.h"
#include "parserASTBase.h"

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
  //An interface method cannot be static, final, or native.
  InterfaceNoStaticFinalNative,
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
