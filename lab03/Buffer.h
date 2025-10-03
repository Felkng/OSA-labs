#ifndef BUFFER_H
#define BUFFER_H
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Buffer {
public:
  vector<char> data;
  int pointer;

  Buffer(vector<char> data, int pointer);
  Buffer();
  void pack_fixo(string &str, int tamanho);
  string unpack_fixo(int tamanho);
  void pack_delimitado(string &str, char delimitador);
  string unpack_delimitado(char delimitador);
  void pack_comprimento(string &str);
  string unpack_comprimento();
  void pack(int valor);
  int unpack();

  bool read(fstream &istream, int tamanho);
  void write(fstream &ostream);
  void clear();
};

#endif
