#pragma once

#include <array>

#include "parserNode.h"

namespace Parse {

using namespace std;

enum class NodeType
{
  NonTerminal,
  Terminal,
  Max
};

struct NodeTerminal {
  enum NodeType nodeType;
  enum TerminalType terminalType;
};

struct Tree;

struct NodeNonTerminal {
  enum NodeType nodeType;
  Tree *tree;
};

union Node {
  NodeType nodeType;
  NodeTerminal terminal;
  NodeNonTerminal nonTerminal;
};

const int TreeMaxChild = 12;

struct Tree {
  enum NonTerminalType type;

  array<Node, TreeMaxChild> children;
};
  
} // namespace Parse
