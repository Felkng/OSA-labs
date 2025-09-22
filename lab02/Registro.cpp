#include "Registro.h"
#include "Buffer.h"
#include <cstring>

using namespace std;

Registro::Registro(char *name, byte idade) : idade(idade) {
  strncpy(this->name, name, NAME_SIZE);
  this->name[39] = '\0';
}

Registro::Registro(string &name, string &idade) {
  strncpy(this->name, name.c_str(), NAME_SIZE);
  this->name[39] = '\0';
  this->idade = (byte)stoi(idade);
}

Registro::Registro() {
  this->idade = (byte)0;
  memset(this->name, '\0', NAME_SIZE);
}

char *Registro::pack_fixed() {
  char *packet = new char[PACKET_SIZE];
  memset(packet, '\0', PACKET_SIZE);
  strncpy(packet, this->name, NAME_SIZE);
  packet[40] = (char)this->idade;
  return packet;
}

void Registro::unpack_fixed(char *buffer) {
  memset(this->name, '\0', sizeof(this->name));
  strncpy(this->name, buffer, NAME_SIZE);
  this->name[39] = '\0';
  this->idade = (byte)buffer[40];
}

bool Registro::is_empty() {
  for (int i = 0; i < PACKET_SIZE; i++) {
    if (this->name[i] != '\0') {
      return false;
    }
  }
  return true;
}
