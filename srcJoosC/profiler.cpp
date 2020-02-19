#include "profiler.h"

#include <assert.h>

#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace chrono;

ProfileScope::ProfileScope(const char* file_, int line_, const char* name_) {
	impl = profileSectionFunc(file_, line_, name_);
}

ProfileScope::~ProfileScope() { profileSectionEndFunc(impl); }

namespace Profiler {

struct Node {
  string id;
  string name;
  Node* parent = nullptr;
  int invocations;
  time_point<high_resolution_clock> startTime;
  duration<long long int, nano> totalTime;
  duration<long long int, nano> overhead;

  unordered_map<string, Node*> children;
  vector<Node*> childrenVec;
};

struct Manager {
  Node* curNode;
  duration<long long int, nano> overhead;
  vector<unique_ptr<Node>> nodeList;

  ~Manager() {}
  static Manager* Get() {
    static Manager m;
    return &m;
  }

 private:
  Manager() {
    auto node = make_unique<Node>();
    curNode = node.get();
    curNode->name = "root";
    nodeList.emplace_back(move(node));
  }
};

}  // namespace Profiler

using namespace Profiler;

#define LevelMarker (reinterpret_cast<Node*>(0x7fffffff))

void profileReport() {
  Manager* manager = Manager::Get();
  printf("(Overhead: %.1fms)\n", (double)manager->overhead.count() / 1e6);
  vector<Node*> stack;
  stack.push_back(manager->curNode->childrenVec[0]);
  int level = 0;
  while (!stack.empty()) {
    Node* node = stack.back();
    stack.pop_back();
    if (node == LevelMarker) {
      level -= 4;
      continue;
    }

    long long int nano = node->totalTime.count();
    double ftime = (double)nano / 1e6;
    if (ftime < 100)
      continue;

    for (int i = 0; i < level; ++i) {
      putc(' ', stdout);
    }
#ifdef _MSC_VER
    printf("%.1fms (%d times) %s (%s)\n", ftime, node->invocations,
           node->name.c_str(), node->id.c_str());
#else
    printf(
        "\033[0;95m%.1fms\033[0m \033[0;92m(%d times)\033[0m "
        "\033[0;96m%s\033[0m (%s)\n",
        ftime, node->invocations, node->name.c_str(), node->id.c_str());
#endif
    level += 4;
    stack.push_back(LevelMarker);
    for (auto it = node->childrenVec.rbegin(); it != node->childrenVec.rend();
         ++it) {
      stack.push_back(*it);
    }
  }
}

ProfileScopeImpl* profileSectionFunc(const char* file,
                                     int line,
                                     const char* name) {
  auto blockBegin = high_resolution_clock::now();

  char buffer[256];
  snprintf(buffer, 256, "%s:%d", file, line);
  string id(buffer);

  Manager* manager = Manager::Get();
  Node* curNode = manager->curNode;
  auto it = curNode->children.find(id);
  Node* child = nullptr;
  if (it == curNode->children.end()) {
    auto newNode = make_unique<Node>();
    child = newNode.get();
    child->parent = curNode;
    child->id = id;
    child->name = string(name);
    curNode->children.insert(make_pair(id, child));
    curNode->childrenVec.push_back(child);
    manager->nodeList.emplace_back(move(newNode));
  } else {
    child = it->second;
  }

  ++child->invocations;
  manager->curNode = child;

  auto blockEnd = high_resolution_clock::now();
  manager->overhead += blockEnd - blockBegin;
  child->overhead += blockEnd - blockBegin;
  child->startTime = blockEnd;
  return reinterpret_cast<ProfileScopeImpl*>(child);
}

void profileSectionEndFunc(ProfileScopeImpl* node) {
  auto endTime = high_resolution_clock::now();
  Manager* manager = Manager::Get();
  Node* curNode = reinterpret_cast<Node*>(node);
  curNode->totalTime += endTime - curNode->startTime - curNode->overhead;
  curNode->parent->overhead += curNode->overhead;
  curNode->overhead = duration<long long int, nano>::zero();
  manager->curNode = curNode->parent;
}
