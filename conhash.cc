#include "conhash.h"
#include <assert.h>
#include <stdio.h>
#include <functional>

ConHash::ConHash() {
}

void ConHash::AddNode(const Node& node) {
  assert(node.replicas > 0);
  for (int i = 0; i < node.replicas; ++i) {
    int key = Hash(node.identify, i);
    vnodes_.insert(std::make_pair(key, node));
  }
}

void ConHash::RemoveNode(const Node& node) {
  for (int i = 0; i < node.replicas; ++i) {
    int key = Hash(node.identify, i);
    vnodes_.erase(key);
  }
}

bool ConHash::Lookup(const std::string& object, Node* node) {
  if (vnodes_.empty()) {
    return false;
  }
  std::hash<std::string> h;
  int key = static_cast<int>(h(object));
  std::map<int, Node>::iterator it = vnodes_.upper_bound(key);
  if (it == vnodes_.end()) {
    *node = vnodes_.begin()->second;
  } else {
    *node = it->second;
  }
  return true;
}

int ConHash::Hash(const std::string& identify, int i) {
  char buf[128];
  snprintf(buf, sizeof(buf), "%s#%d", identify.c_str(), i);
  std::hash<std::string> h;
  return static_cast<int>(h(std::string(buf)));
}
