#ifndef CABECALHO_H
#define CABECALHO_H

#include "formato.h"
#include <ctime>

using namespace std;

class FileHeader {
  // O cabeçalho foi criado basicamente para definir a quantidade de bytes que
  // lidos na função de "ler_registros" Nós não sabiamos como fazer a leitura,
  // visto que a função não recebia parâmetro, então a gente salva a quantidade
  // em bytes de todos os registros somados, para ler todos de uma única vez e
  // colocar na memória.
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
