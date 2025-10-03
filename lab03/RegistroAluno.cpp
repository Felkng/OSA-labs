#include "RegistroAluno.h"
#include "Buffer.h"
#include "constantes.h"
#include "formato.h"
#include <cstring>
#include <string>

using namespace std;

RegistroAluno::RegistroAluno(string nome, int matricula, string curso)
    : nome(nome), matricula(matricula), curso(curso) {}

void RegistroAluno::pack(Buffer &buffer, Formato formato) {
  switch (formato) {
  case FIXO: {
    buffer.pack_fixo(this->nome, NOME_FIXO);
    string matricula_str = to_string(this->matricula);
    buffer.pack_fixo(matricula_str, MATRICULA_FIXO);
    buffer.pack_fixo(this->curso, CURSO_FIXO);
    break;
  }
  case COMPRIMENTO:
    break;
  case DELIMITADO:
    break;
  default:
    cerr << "Formato de registro não identificado." << endl;
    return;
  }
}

void RegistroAluno::unpack(Buffer &buffer, Formato formato) {
  switch (formato) {
  case FIXO: {
    this->nome = buffer.unpack_fixo(NOME_FIXO);
    this->matricula = stoi(buffer.unpack_fixo(MATRICULA_FIXO));
    this->curso = buffer.unpack_fixo(CURSO_FIXO);
    break;
  }
  case COMPRIMENTO:
    break;
  case DELIMITADO:
    break;
  default:
    cerr << "Formato de registro não identificado." << endl;
    return;
  }
}

string RegistroAluno::get_chave() { return ""; }

int RegistroAluno::get_tamanho_fixo() { return 0; }
