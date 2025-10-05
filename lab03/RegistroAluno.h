#ifndef REGISTRO_ALUNO_H
#define REGISTRO_ALUNO_H
#include "Buffer.h"
#include "Registro.h"
#include "formato.h"

class RegistroAluno : public Registro {
public:
  string nome;
  int matricula;
  string curso;

  RegistroAluno();
  RegistroAluno(string nome, int matricula, string curso);
  void pack(Buffer &buffer, Formato formato);
  void unpack(Buffer &buffer, Formato formato);
  // string get_chave();
  int get_tamanho_fixo();
  RegistroAluno parse_csv(string csv_data, char sep);
};

#endif
