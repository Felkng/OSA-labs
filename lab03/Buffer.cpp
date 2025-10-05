#include "Buffer.h"
#include <string>
using namespace std;

Buffer::Buffer(vector<char> data, int pointer) : data(data), pointer(pointer) {}

Buffer::Buffer() : data(vector<char>()), pointer(0) {}

void Buffer::pack_fixo(string &str, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    if (i < (int)str.length()) {
      this->data.push_back(str[i]);
    } else {
      this->data.push_back('\0');
    }
  }
  this->pointer += tamanho;
}

string Buffer::unpack_fixo(int tamanho) {
  string field = "";
  for (int i = 0; i < tamanho; i++) {
    if (this->data[this->pointer] != '\0') {
      field += this->data[this->pointer];
    }
    this->pointer++;
  }
  return field;
}

void Buffer::pack_delimitado(string &str, char delimitador) {
  for (unsigned long long int i = 0; i < str.length(); i++) {
    this->data.push_back(str[i]);
    this->pointer++;
  }
  this->data.push_back(delimitador);
  this->pointer++;
}

string Buffer::unpack_delimitado(char delimitador) {
  string field = "";
  for (unsigned long long int i = this->pointer;
       i < this->data.size() && this->data[i] != delimitador; i++) {
    field += this->data[i];
    this->pointer++;
  }
  this->pointer++;
  return field;
}

void Buffer::pack_comprimento(string &str) {
  int field_size = str.length();
  string field_size_str = to_string(field_size);
  for (unsigned long long int i = 0; i < field_size_str.length(); i++) {
    this->data.push_back(field_size_str[i]);
    this->pointer++;
  }
  // indica o final de um contador de tamanho do campo
  this->data.push_back(' ');
  this->pointer++;
  for (unsigned long long int i = 0; i < str.length(); i++) {
    this->data.push_back(str[i]);
    this->pointer++;
  }
}

string Buffer::unpack_comprimento() {
  string field_size_str;
  while (this->pointer < (int)this->data.size() && this->data[this->pointer] != ' ') {
    char c = this->data[this->pointer];
    if (c >= '0' && c <= '9') {
      field_size_str += c;
    }
    this->pointer++;
  }
  
  if (this->pointer >= (int)this->data.size()) {
    return "";
  }
  
  this->pointer++; // pula o espaço
  
  if (field_size_str.empty()) {
    return "";
  }
  
  int field_size = stoi(field_size_str);
  string field = "";
  for (int i = 0; i < field_size && this->pointer < (int)this->data.size(); i++) {
    field += this->data[this->pointer];
    this->pointer++;
  }
  return field;
}

void Buffer::pack(int valor) {
  char* bytes = reinterpret_cast<char*>(&valor);
  for (size_t i = 0; i < sizeof(int); i++) {
    this->data.push_back(bytes[i]);
  }
  this->pointer += sizeof(int);
}

int Buffer::unpack() {
  int valor = 0;
  char* bytes = reinterpret_cast<char*>(&valor);
  for (size_t i = 0; i < sizeof(int); i++) {
    bytes[i] = this->data[this->pointer + i];
  }
  this->pointer += sizeof(int);
  return valor;
}

bool Buffer::read(fstream &istream, int tamanho) {
  this->data.resize(tamanho);
  istream.read(this->data.data(), tamanho);
  if (istream.gcount() != tamanho)
    return false;
  return true;
}

void Buffer::write(fstream &ostream) {
  ostream.write(this->data.data(), this->data.size());
}

void Buffer::clear() {
  this->data = vector<char>();
  this->pointer = 0;
}
