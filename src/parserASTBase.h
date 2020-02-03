#pragma once

#include <array>
#include <string>
#include <vector>

#include <assert.h>

#include "parserNode.h"

namespace Parse {

using namespace std;

const int TreeMaxChild = 8;

struct Tree {
  enum NonTerminalType type;
  Tree *parent;
  int numChildren;
  array<Tree *, TreeMaxChild> children;  

  Tree(enum NonTerminalType type_): type(type_), parent(nullptr),
          numChildren(0) {}
  virtual ~Tree() {}
};

typedef void (*parserASTFunc)(vector<Tree *> *stack);

void parserASTDispatcher(vector<Tree *> *stack, int ruleID);
void parserASTSetTopParents(vector<Tree *> *stack, int topN, Tree *parent);
void parserASTPopulateChildrenList(Tree *tree, const vector<Tree *> &stack, int n);
void parserASTDeleteStack(vector<Tree *> *stack);
void parserASTDelete(Tree *root);

template <typename T>
vector<T *> __parserASTFindByType(Tree *root, enum NonTerminalType type) {
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

#define __prependNonTerminalType(x) NonTerminalType::x

#define parserASTFindByType(root, _type) \
  __parserASTFindByType<Tree##_type>(root, __prependNonTerminalType(_type))

} // namespace Parse
