// Copyright (c) 2017 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONHASH_H_
#define CONHASH_H_

#include <stdint.h>
#include <map>
#include <string>

class Node {
 public:
  std::string identify;
  int replicas;
  Node() : identify(), replicas(0) { }
  Node(const std::string& s, int i) : identify(s), replicas(i) { }
};

class ConHash {
 public:
  ConHash();

  void AddNode(const Node& node);
  void RemoveNode(const Node& node);
  bool Lookup(const std::string& object, Node* node);

 private:
  uint32_t Hash(const std::string& identify, int i);

  std::map<uint32_t, Node> vnodes_;

  // No copying allowed
  ConHash(const ConHash&);
  void operator=(const ConHash&);
};

#endif  // CONHASH_H_
