#include "Arquivo.h"
#include "Buffer.h"
#include <fstream>
#include <vector>
using namespace std;

Arquivo::Arquivo(string filename) : filename(filename) {}
void Arquivo::add_fixed_registro(Registro reg) {
  Buffer buffer;
  ofstream file(this->filename, ios::app);
  if (!file.is_open()) {
    cerr << "File is not open.";
    return;
  }
  buffer.write_fixed_registro(reg, file);
  file.close();
}

vector<Registro> Arquivo::read_fixed_registros() {
  Buffer buffer;
  ifstream file(this->filename, ios::in);
  if (!file.is_open()) {
    cerr << "File is not open.";
    return {};
  }

  vector<Registro> registros;
  while (true) {
    Registro reg = buffer.read_fixed_registro(file);
    if (reg.is_empty()) {
      break;
    }
    registros.push_back(reg);
  }
  return registros;
}
