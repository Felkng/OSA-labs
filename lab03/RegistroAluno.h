#ifndef REGISTRO_ALUNO_H
#define REGISTRO_ALUNO_H
#include "Buffer.h"
#include "Registro.h"
#include "formato.h"

class RegistroAluno : public Registro {
public:
  int matricula;
  string nome;
  string curso;

  RegistroAluno(string nome, int matricula, string curso);
  void pack(Buffer &buffer, Formato formato);
  void unpack(Buffer &buffer, Formato formato);
  string get_chave();
  int get_tamanho_fixo();
};

#endif
