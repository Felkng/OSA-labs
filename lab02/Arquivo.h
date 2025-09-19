#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "Registro.h"
#include <string>
#include <vector>

using namespace std;

class Arquivo {
public:
  string filename;

  Arquivo(string filename);
  void add_fixed_registro(Registro reg);
  vector<Registro> read_fixed_registros();
};

#endif
