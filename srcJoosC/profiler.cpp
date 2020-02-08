#include "profiler.h"

#include <string>
#include <chrono>
#include <memory>
#include <unordered_map>
#include <vector>

#include <assert.h>

using namespace std;
using namespace chrono;

namespace Profiler {

  struct Node {
    string id;
    string name;
    Node *parent = nullptr;
    int invocations;
    time_point<high_resolution_clock> startTime;
    duration<long long int, nano> totalTime;

    unordered_map<string, Node *> children;
    vector<Node *> childrenVec;
  };

#define LevelMarker (reinterpret_cast<Node *>(0x7fffffff))

  struct Manager {
    Node *curNode;
    duration<long long int, nano> overhead;
    vector<unique_ptr<Node>> nodeList;
    
    ~Manager() {
      printf("(Overhead: %.1fms)\n", (double)overhead.count()/1e6);
      vector<Node *> stack;
      stack.push_back(curNode->childrenVec[0]);
      int level = 0;
      while (!stack.empty()) {
        Node *node = stack.back();
        stack.pop_back();
        if (node == LevelMarker) {
          level -= 4;
          continue;
        }

        long long int nano = node->totalTime.count();
        double ftime = (double)nano / 1e6;
        if (ftime < 10)
          continue;

        for (int i = 0; i < level; ++i) {
          putc(' ', stdout);
        }
        
        printf("\033[0;95m%.1fms\033[0m \033[0;92m(%d times)\033[0m \033[0;96m%s\033[0m (%s)\n", ftime, node->invocations, node->name.c_str(), node->id.c_str());
        level += 4; 
        stack.push_back(LevelMarker);
        for (auto it = node->childrenVec.rbegin(); it != node->childrenVec.rend(); ++it) {
          stack.push_back(*it);
        }
      }
    }    
    static Manager *Get() {
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
  
} // namespace Profiler

using namespace Profiler;

ProfileScopeImpl* profileSectionFunc(const char *file, int line, const char *name) {
  auto blockBegin = high_resolution_clock::now();

  char buffer[256];
  snprintf(buffer, 256, "%s:%d", file, line);
  string id(buffer);

  Manager* manager = Manager::Get();
  Node *curNode = manager->curNode;
  auto it = curNode->children.find(id);
  Node *child = nullptr;
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
  manager->curNode->startTime = blockEnd;
  return reinterpret_cast<ProfileScopeImpl *>(child);
}

void profileSectionEndFunc(ProfileScopeImpl *node) {
  auto endTime = high_resolution_clock::now();
  Manager *manager = Manager::Get();
  Node *curNode = reinterpret_cast<Node *>(node);
  curNode->totalTime += static_cast<duration<long long int, nano>>(endTime - curNode->startTime);
  manager->curNode = curNode->parent;
}
