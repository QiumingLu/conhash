#ifndef CONHASH_H_
#define CONHASH_H_

#include <map>
#include <string>

struct Node {
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
  size_t Hash(const std::string& identify, int i);

  std::map<size_t, Node> vnodes_;

  // No copying allowed
  ConHash(const ConHash&);
  void operator=(const ConHash&);
};

#endif  // CONHASH_H_
