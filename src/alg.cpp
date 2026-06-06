// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <vector>
#include  "tree.h"

void PMTree::buildTree(Node* node, const std::vector<char>& remaining) {
  for (size_t i = 0; i < remaining.size(); ++i) {
    Node* child = new Node(remaining[i]);
    node->children.push_back(child);

    std::vector<char> next_remaining;
    for (size_t j = 0; j < remaining.size(); ++j) {
      if (i != j) {
        next_remaining.push_back(remaining[j]);
      }
    }
    buildTree(child, next_remaining);
  }
}

PMTree::PMTree(const std::vector<char>& in) {
  std::vector<char> sorted_in = in;
  std::sort(sorted_in.begin(), sorted_in.end());
  size = sorted_in.size();
  root = new Node('\0');
  buildTree(root, sorted_in);
}

void PMTree::destroyTree(Node* node) {
  if (!node) return;
  for (Node* child : node->children) {
    destroyTree(child);
  }
  delete node;
}

PMTree::~PMTree() {
  destroyTree(root);
}

PMTree::Node* PMTree::getRoot() const {
  return root;
}

int PMTree::getSize() const {
  return size;
}

void dfsAll(PMTree::Node* node, std::vector<char>& current,
            std::vector<std::vector<char>>& result) {
  if (node->children.empty()) {
    if (!current.empty()) result.push_back(current);
    return;
  }
  for (PMTree::Node* child : node->children) {
    current.push_back(child->value);
    dfsAll(child, current, result);
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;
  if (tree.getRoot()) {
    dfsAll(tree.getRoot(), current, result);
  }
  return result;
}

bool dfs1(PMTree::Node* node, std::vector<char>& current, int& count,
          int target, std::vector<char>& result) {
  if (node->children.empty()) {
    count++;
    if (count == target) {
      result = current;
      return true;
    }
    return false;
  }
  for (PMTree::Node* child : node->children) {
    current.push_back(child->value);
    if (dfs1(child, current, count, target, result)) return true;
    current.pop_back();
  }
  return false;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  std::vector<char> result;
  std::vector<char> current;
  int count = 0;
  if (tree.getRoot() && num > 0) {
    dfs1(tree.getRoot(), current, count, num, result);
  }
  return result;
}

int factorial(int n) {
  int res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  std::vector<char> result;
  int n = tree.getSize();
  if (num <= 0 || num > factorial(n)) return result;

  int target = num - 1;
  PMTree::Node* current_node = tree.getRoot();

  while (!current_node->children.empty()) {
    int fact = factorial(n - 1);
    int idx = target / fact;
    target %= fact;

    current_node = current_node->children[idx];
    result.push_back(current_node->value);
    n--;
  }
  return result;
}
