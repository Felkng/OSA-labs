#ifndef REGISTRO_H
#define REGISTRO_H
#include <string>
#define NAME_SIZE 40
using namespace std;

class Registro {
public:
  char name[40];
  byte idade;

  Registro(string &name, string &idade);
  Registro(char *name, byte idade);
  Registro();
  char *pack_fixed();
  void unpack_fixed(char *buffer);
  bool is_empty();
};

#endif
