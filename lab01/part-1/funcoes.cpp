#include "funcoes.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int write_file(vector<string> &input, string filename) {
  ofstream file;

  file.open(filename);

  if (!file.is_open()) {
    cerr << "Coudn't open file!\n";
    return 1;
  }

  for (auto x : input) {
    file << x << endl;
  }

  file.close();
  return 0;
}

int populate_vector_with_file(vector<string> &input, string filename) {
  ifstream file;
  file.open(filename);

  if (!file.is_open()) {
    cerr << "Coudn't open file!\n";
    return 1;
  }

  string line;
  while (getline(file, line)) {
    input.push_back(line);
  }

  file.close();
  return 0;
}
