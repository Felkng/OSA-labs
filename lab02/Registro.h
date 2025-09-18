#ifndef REGISTRO_H
#define REGISTRO_H
#include <string>
using namespace std;

class Registro {
public:
  char name[40];
  byte idade;

  char *pack_with_length();
  void unpack_with_length(char *data);
  char *pack_fixed();
  void unpack_fixed(char *buffer);
};

#endif
