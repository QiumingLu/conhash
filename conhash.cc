// Copyright (c) 2017 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "conhash.h"
#include <assert.h>
#include <stdio.h>
#include "murmurhash3.h"

ConHash::ConHash() {
}

void ConHash::AddNode(const Node& node) {
  assert(node.replicas > 0);
  for (int i = 0; i < node.replicas; ++i) {
    uint32_t key = Hash(node.identify, i);
    vnodes_.insert(std::make_pair(key, node));
  }
}

void ConHash::RemoveNode(const Node& node) {
  for (int i = 0; i < node.replicas; ++i) {
    uint32_t key = Hash(node.identify, i);
    vnodes_.erase(key);
  }
}

bool ConHash::Lookup(const std::string& object, Node* node) {
  if (vnodes_.empty()) {
    return false;
  }
  
  uint32_t key;
  MurmurHash3_x86_32(object.c_str(), static_cast<int>(object.size()), 0, &key);

  std::map<uint32_t, Node>::iterator it = vnodes_.upper_bound(key);
  if (it == vnodes_.end()) {
    *node = vnodes_.begin()->second;
  } else {
    *node = it->second;
  }
  return true;
}

uint32_t ConHash::Hash(const std::string& identify, int i) {
  char buf[128];
  int len = snprintf(buf, sizeof(buf), "%s#%d", identify.c_str(), i);
  assert(len > 0);
  uint32_t out;
  MurmurHash3_x86_32(buf, len, 0, &out);
  return out;
}
