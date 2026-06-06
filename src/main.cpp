// Copyright 2022 NNTU-CS
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

int getFactorial(int n) {
  int res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

int main() {
  std::vector<char> test_in = {'1', '2', '3'};
  PMTree test_tree(test_in);

  std::cout << "Test getPerm1(1): ";
  for (char c : getPerm1(test_tree, 1)) std::cout << c;
  std::cout << "\nTest getPerm2(2): ";
  for (char c : getPerm2(test_tree, 2)) std::cout << c;
  std::cout << "\n\n";

  std::ofstream outFile("result/experiment_data.csv");
  if (!outFile.is_open()) {
    std::cerr << "Error: Can't open file in result/" << std::endl;
    return 1;
  }
  outFile << "N,GetAll_ns,GetPerm1_ns,GetPerm2_ns\n";

  std::mt19937 gen(42);

  for (int n = 3; n <= 8; ++n) {
    std::vector<char> alphabet;
    for (int i = 0; i < n; ++i) {
      alphabet.push_back('A' + i);
    }

    PMTree tree(alphabet);
    int max_perms = getFactorial(n);
    std::uniform_int_distribution<> dist(1, max_perms);
    int random_num = dist(gen);

    auto start = std::chrono::high_resolution_clock::now();
    volatile auto all = getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_all =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    start = std::chrono::high_resolution_clock::now();
    volatile auto p1 = getPerm1(tree, random_num);
    end = std::chrono::high_resolution_clock::now();
    auto time_p1 =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    start = std::chrono::high_resolution_clock::now();
    volatile auto p2 = getPerm2(tree, random_num);
    end = std::chrono::high_resolution_clock::now();
    auto time_p2 =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    outFile << n << "," << time_all.count() << "," << time_p1.count() << ","
            << time_p2.count() << "\n";
  }

  outFile.close();
  std::cout << "Experiment data saved.\n";
  return 0;
}
