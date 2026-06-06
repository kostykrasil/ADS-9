// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>

class PMTree {
 public:
  struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char val) : value(val) {}
  };

  explicit PMTree(const std::vector<char>& in);
  ~PMTree();

  Node* getRoot() const;
  int getSize() const;

 private:
  Node* root;
  int size;

  void buildTree(Node* node, const std::vector<char>& remaining);
  void destroyTree(Node* node);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
