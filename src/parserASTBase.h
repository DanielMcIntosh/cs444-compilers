#pragma once

#include <array>
#include <string>

#include "parserNode.h"

namespace Parse {

using namespace std;

const int TreeMaxChild = 8;

struct Tree {
  enum NonTerminalType type;

  array<Tree *, TreeMaxChild> children;
};


struct TreeIntegerLiteral: public Tree {
  int value;
};

struct TreeBooleanLiteral: public Tree {
  bool value;
};

struct TreeCharacterLiteral: public Tree {
  char value;
};

struct TreeStringLiteral: public Tree {
  string value;
};

struct TreeNullLiteral: public Tree {
};

struct TreeIdentifier: public Tree {
  string value;
};

} // namespace Parse
