#include "Buffer.h"
#include "Registro.h"

using namespace std;

void Buffer::write_fixed_registro(Registro &reg, ofstream &out) {
  char *buffer = reg.pack_fixed();
  out.write(buffer, PACKET_SIZE);
}

Registro Buffer::read_fixed_registro(ifstream &in) {
  char buffer[PACKET_SIZE];
  if (in.read(buffer, PACKET_SIZE)) {
    Registro reg;
    reg.unpack_fixed(buffer);
    return reg;
  }
  return Registro();
}

Registro Buffer::read_line_csv(ifstream &in, char delimter) {
  string line;
  if (getline(in, line)) {
    string name = line.substr(0, line.find(delimter));
    string age = line.substr(line.find(delimter) + 1, line.length());
    Registro reg = Registro(name, age);
    return reg;
  }
  return Registro();
}
