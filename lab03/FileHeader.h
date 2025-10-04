#ifndef CABECALHO_H
#define CABECALHO_H

#include "formato.h"
#include <ctime>

using namespace std;

class FileHeader {
public:
  FileHeader();
  FileHeader(Formato registro_formato, long long total_data_size,
             int num_registros, time_t last_modified);
  Formato registro_formato;
  long long total_data_size = 0;
  int num_registros = 0;
  time_t last_modified = 0;
};

#endif
