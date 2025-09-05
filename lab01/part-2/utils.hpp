#ifndef UTILS_H
#define UTILS_H
#include "pessoa.hpp"
#include <string>
#include <vector>
using namespace std;

int populate_pessoas_vector_from_file(vector<Pessoa *> &pessoas,
                                      string filename, string delimter,
                                      int skiprows = 1);

void dealocate_pessoas(vector<Pessoa *> &pessoas);

void print_pessoas_vector(vector<Pessoa *> &pessoas);

int save_pessoas_vector_to_file(vector<Pessoa *> &pessoas, string filename);

#endif
