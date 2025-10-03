#ifndef REGISTRO_H
#define REGISTRO_H
#include "Buffer.h"
#include "formato.h"
#include <string>
using namespace std;

class Registro {
public:
  virtual void pack(Buffer &buffer, Formato formato) = 0;
  virtual void unpack(Buffer &buffer, Formato formato) = 0;
  virtual string get_chave() = 0;
  virtual int get_tamanho_fixo() = 0;
};

#endif
