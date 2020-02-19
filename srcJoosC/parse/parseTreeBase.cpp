#include "parseTreeBase.h"

#include "../profiler.h"
#include "../utility.h"

namespace Parse {

Tree::~Tree() {}
Tree::Tree(enum NonTerminalType type_)
				: type(type_),
				  parent(nullptr),
				  numChildren(0),
				  children({}),
				  oneNt(false) {}

void ptSetTopParents(vector<Tree*>* stack, int topN, Tree* parent) {
  const int n = stack->size();
  assert(topN <= n);
  for (int i = 0; i < topN; ++i) {
    assert(!(*stack)[n - i - 1]->parent);
    (*stack)[n - i - 1]->parent = parent;
  }
}

void ptPopulateChildrenList(Tree* tree, const vector<Tree*>& stack, int n) {
  tree->numChildren = n;
  const int stackN = stack.size();
  assert(stackN >= n);
  for (int i = 0; i < n; ++i) {
    tree->children[i] = stack[stackN - (n - i)];
  }
}

void ptDeleteStack(vector<Tree*>* stack) {
  for (const auto tree : *stack) {
    ptDelete(tree);
  }
}

void ptDelete(Tree* root) {
  profileSection("pt delete");
  if (!root)
    return;
  vector<Tree*> stack;
  stack.push_back(root);
  while (!stack.empty()) {
    Tree* node = stack.back();
    stack.pop_back();
    for (int i = 0; i < node->numChildren; ++i) {
      stack.push_back(node->children[i]);
    }
    delete node;
  }
}

}  // namespace Parse
