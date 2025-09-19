#ifndef REGISTRO_H
#define REGISTRO_H
#include <string>
using namespace std;

class Registro {
public:
  char name[40];
  byte idade;

  Registro(char *name, byte idade);
  Registro();
  char *pack_fixed();
  void unpack_fixed(char *buffer);
};

#endif
