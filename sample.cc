// Copyright (c) 2017 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <iostream>
#include "conhash.h"

int main() {
  ConHash conhash;
  Node n1("spanner", 12);
  Node n2("bigtable", 16);
  Node n3("mapreduce", 14);
  Node n4("chubby", 15);
  Node n5("gfs", 10);
  conhash.AddNode(n1);
  conhash.AddNode(n2);
  conhash.AddNode(n3);
  conhash.AddNode(n4);
  conhash.AddNode(n5);
  for (int i = 0; i < 20; ++i) {
    char buf[32];
    snprintf(buf, sizeof(buf), "megastore#%d", i);
    Node node;
    if (conhash.Lookup(buf, &node)) {
      std::cout << node.identify << std::endl;
    } else {
      std::cout << "No server" << std::endl;
    }
  }
  std::cout << "\n";
  conhash.RemoveNode(n3);
  for (int i = 0; i < 20; ++i) {
    char buf[32];
    snprintf(buf, sizeof(buf), "megastore#%d", i);
    Node node;
    if (conhash.Lookup(buf, &node)) {
      std::cout << node.identify << std::endl;
    } else {
      std::cout << "No server" << std::endl;
    }
  }

  return 0;
}
