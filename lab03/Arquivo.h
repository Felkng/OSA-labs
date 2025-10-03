#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "Registro.h"
#include "formato.h"
#include <string>
#include <vector>

using namespace std;

template <class T> class Arquivo {
public:
  string filename;
  Formato formato;

  Arquivo(string filename, Formato formato);
  void adicionar_registro(T &reg);
  vector<T> read_fixed_registros();
  vector<T> read_csv_file(char sep, int skiprows = 1);
};

#endif
