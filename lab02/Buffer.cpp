#include "Buffer.h"
#include "Registro.h"

using namespace std;

void write_fixed_registro(Registro reg, ofstream &out) {
  char *buffer = reg.pack_fixed();
  out.write(buffer, PACKET_SIZE);
}

Registro Buffer::read_fixed_registro(ifstream &in) {
  if (!in.is_open()) {
    cerr << "File is not open.";
    return Registro();
  }
  char *buffer;
  if (in.read(buffer, PACKET_SIZE)) {
    Registro reg;
    reg.unpack_fixed(buffer);
    return reg;
  }
  return Registro();
}
