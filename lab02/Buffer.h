#ifndef BUFFER_H
#define BUFFER_H
#include "Registro.h"
#include <fstream>

using namespace std;

class Buffer {
public:
  void write_fixed_registro(Registro reg, ofstream out);
  Registro read_fixed_registro(ifstream in);
};

#endif
