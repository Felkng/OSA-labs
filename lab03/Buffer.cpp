#include "Buffer.h"
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

void Buffer::pack_comprimento(string &str) {}

string Buffer::unpack_comprimento() { return ""; }

void Buffer::pack(int valor) {}

int Buffer::unpack() { return 0; }

bool Buffer::read(fstream &istream, int tamanho) { return false; }

void Buffer::write(fstream &ostream) {}

void Buffer::clear() {}
