#pragma once

#include <array>
#include <string>
#include <vector>

#include <assert.h>

#include "parseTreeNode.h"

namespace Parse {

using namespace std;

const int TreeMaxChild = 8;

struct Tree {
  enum NonTerminalType type;
  Tree *parent;
  int numChildren;
  array<Tree *, TreeMaxChild> children;
  // tree node is derived from a rule that has a single non-temrinal on right hand side  
  bool oneNt;
  

  Tree(enum NonTerminalType type_): type(type_), parent(nullptr),
                                    numChildren(0), children({}), oneNt(false) {}
  virtual ~Tree() {}
};

typedef void (*ptFunc)(vector<Tree *> *stack);

void ptDispatcher(vector<Tree *> *stack, int ruleID);
void ptSetTopParents(vector<Tree *> *stack, int topN, Tree *parent);
void ptPopulateChildrenList(Tree *tree, const vector<Tree *> &stack, int n);
void ptDeleteStack(vector<Tree *> *stack);
void ptDelete(Tree *root);

template <typename T>
vector<T *> __ptFindByType(Tree *root, enum NonTerminalType type) {
  vector<Tree *> stack;
  vector<T *> result;
  stack.push_back(root);
  while (!stack.empty()) {
    Tree *tree = stack.back();
    stack.pop_back();
    for (int i = 0; i < tree->numChildren; ++i) {
      stack.push_back(tree->children[i]);
    }
    if (tree->type == type) {
      result.push_back(dynamic_cast<T *>(tree));
      assert(result.back() != nullptr);
    }
  }
  return result;
}

} // namespace Parse

#define __prependNonTerminalType(x) Parse::NonTerminalType::x

#define ptFindByType(root, _type) \
  Parse::__ptFindByType<Parse::T##_type>(root, __prependNonTerminalType(_type))

