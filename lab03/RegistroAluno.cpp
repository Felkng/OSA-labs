#include "RegistroAluno.h"
#include "Buffer.h"
#include "constantes.h"
#include "formato.h"
#include <cstring>
#include <sstream>
#include <string>

using namespace std;

RegistroAluno::RegistroAluno(string nome, int matricula, string curso)
    : nome(nome), matricula(matricula), curso(curso) {}

RegistroAluno::RegistroAluno() : nome(""), matricula(0), curso("") {}

void RegistroAluno::pack(Buffer &buffer, Formato formato) {
  switch (formato) {
  case FIXO: {
    buffer.pack_fixo(this->nome, NOME_FIXO);
    string matricula_str = to_string(this->matricula);
    buffer.pack_fixo(matricula_str, MATRICULA_FIXO);
    buffer.pack_fixo(this->curso, CURSO_FIXO);
    break;
  }
  case COMPRIMENTO: {
    buffer.pack_comprimento(this->nome);
    string matricula_str = to_string(this->matricula);
    buffer.pack_comprimento(matricula_str);
    buffer.pack_comprimento(this->curso);
    break;
  }
  case DELIMITADO: {
    buffer.pack_delimitado(this->nome, ';');
    string matricula_str = to_string(this->matricula);
    buffer.pack_delimitado(matricula_str, ';');
    buffer.pack_delimitado(this->curso, ';');
    break;
  }
  default:
    cerr << "Formato de registro não identificado." << endl;
    return;
  }
}

void RegistroAluno::unpack(Buffer &buffer, Formato formato) {
  switch (formato) {
  case FIXO: {
    this->nome = buffer.unpack_fixo(NOME_FIXO);
    string matricula_str = buffer.unpack_fixo(MATRICULA_FIXO);
    this->matricula = (matricula_str.empty()) ? 0 : stoi(matricula_str);
    this->curso = buffer.unpack_fixo(CURSO_FIXO);
    break;
  }
  case COMPRIMENTO: {
    this->nome = buffer.unpack_comprimento();
    string matricula_str = buffer.unpack_comprimento();
    this->matricula = (matricula_str.empty()) ? 0 : stoi(matricula_str);
    this->curso = buffer.unpack_comprimento();
    break;
  }
  case DELIMITADO: {
    this->nome = buffer.unpack_delimitado(';');
    string matricula_str = buffer.unpack_delimitado(';');
    this->matricula = (matricula_str.empty()) ? 0 : stoi(matricula_str);
    this->curso = buffer.unpack_delimitado(';');
    break;
  }
  default:
    cerr << "Formato de registro não identificado." << endl;
    return;
  }
}

// string RegistroAluno::get_chave() { return ""; }
//
int RegistroAluno::get_tamanho_fixo() {
  return sizeof(this->nome) + sizeof(this->matricula) + sizeof(this->curso);
}

RegistroAluno RegistroAluno::parse_csv(string csv_data, char sep) {
  RegistroAluno reg;
  stringstream ss(csv_data);

  getline(ss, reg.nome, sep);

  string matricula_str;
  getline(ss, matricula_str, sep);
  reg.matricula = stoi(matricula_str);

  getline(ss, reg.curso, sep);
  return reg;
}
