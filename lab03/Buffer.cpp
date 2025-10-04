#include "Buffer.h"
#include <string>
using namespace std;

Buffer::Buffer(vector<char> data, int pointer) : data(data), pointer(pointer) {}

Buffer::Buffer() : data(vector<char>()), pointer(0) {}

void Buffer::pack_fixo(string &str, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    if (i >= str.length()) {
      this->data.push_back('\0');
    }
    this->data.push_back(str[i]);
  }
  this->pointer += tamanho;
}

string Buffer::unpack_fixo(int tamanho) {
  string field;
  for (int i = 0; i < tamanho; i++) {
    field += this->data[this->pointer++];
  }
  return field;
}

void Buffer::pack_delimitado(string &str, char delimitador) {}

string Buffer::unpack_delimitado(char delimitador) { return ""; }

void Buffer::pack_comprimento(string &str) {
  int field_size = str.length();
  string field_size_str = to_string(field_size);
  for (int i = 0; i < field_size_str.length(); i++) {
    this->data.push_back(field_size_str[i]);
    this->pointer++;
  }
  // indica o final de um contador de tamanho do campo
  this->data.push_back(' ');
  this->pointer++;
}

string Buffer::unpack_comprimento() {
  string field_size_str;
  for (int i = this->pointer; this->data[i] != ' '; i++) {
    field_size_str += this->data[i];
    this->pointer++;
  }
  this->pointer++;
  int field_size = stoi(field_size_str);
  string field;
  for (int i = this->pointer; i < field_size; i++) {
    field += this->data[i];
  }
  this->pointer += field_size;
  return field;
}

// muito provavelmente será usado para escolher qual tipo de registro será
// utilizado no arquivo para tornar o salvamento/recuperação mais abstrato
// ou necessário para o cabeçalho
//
// void Buffer::pack(int valor) {}
//
// int Buffer::unpack() { return 0; }

bool Buffer::read(fstream &istream, int tamanho) {
  char *stream;
  istream.read(stream, tamanho);
  if (istream.gcount() != tamanho)
    return false;
  this->data.assign(stream, stream + tamanho);
  return true;
}

void Buffer::write(fstream &ostream) {
  ostream.write(this->data.data(), this->data.size());
}

void Buffer::clear() {
  this->data = vector<char>();
  this->pointer = 0;
}
