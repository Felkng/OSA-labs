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
  return field;
}

// void Buffer::pack(int valor) {}
//
// int Buffer::unpack() { return 0; }

bool Buffer::read(fstream &istream, int tamanho) { return false; }

void Buffer::write(fstream &ostream) {}

void Buffer::clear() {}
