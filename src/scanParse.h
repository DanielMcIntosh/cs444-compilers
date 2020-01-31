#pragma once

#include <vector>
#include <string>

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
};
  
}

namespace Parse {

struct ParseResult {
  bool valid;    
};
  
}
