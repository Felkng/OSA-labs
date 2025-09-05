#include "utils.hpp"
#include "pessoa.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int populate_pessoas_vector_from_file(vector<Pessoa *> &pessoas,
                                      string filename, string delimter,
                                      int skiprows) {
  ifstream file;
  file.open(filename);

  if (!file.is_open()) {
    cerr << "Coudn't open file!\n";
    return 1;
  }

  string line;
  while (getline(file, line)) {
    if (skiprows > 0) {
      skiprows--;
      continue;
    }
    string name = line.substr(0, line.find(delimter));
    string age = line.substr(line.find(delimter) + 1, line.length());
    pessoas.push_back(Pessoa::convert_string_to_registro(age, name));
  }

  file.close();
  return 0;
}

void dealocate_pessoas(vector<Pessoa *> &pessoas) {
  for (auto &x : pessoas) {
    delete x;
  }
}

void print_pessoas_vector(vector<Pessoa *> &pessoas) {
  for (auto &x : pessoas) {
    cout << x->to_string() << endl;
  }
}

int save_pessoas_vector_to_file(vector<Pessoa *> &pessoas, string filename) {
  ofstream file;
  file.open(filename);
  if (!file.is_open()) {
    cerr << "Couldn't open file." << endl;
    return 1;
  }
  for (auto &x : pessoas) {
    file << x->name << "," << x->age << endl;
  }

  return 0;
}
