#include "Registro.h"
#include <cstring>

using namespace std;

Registro::Registro(char *name, byte idade) : idade(idade) {
  strncpy(this->name, name, 40);
  this->name[39] = '\0';
}

Registro::Registro() {
  this->idade = (byte)0;
  memset(this->name, '\0', sizeof(this->name));
}

char *Registro::pack_fixed() {
  char *packet = new char[41];
  memset(packet, '\0', 41);
  strncpy(packet, this->name, 40);
  packet[40] = (char)this->idade;
  return packet;
}

void Registro::unpack_fixed(char *buffer) {
  memset(this->name, '\0', sizeof(this->name));
  strncpy(this->name, buffer, 40);
  this->name[39] = '\0';
  this->idade = (byte)buffer[40];
}
