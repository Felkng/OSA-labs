#include "Arquivo.h"
#include "Buffer.h"
#include "FileHeader.h"
#include "Registro.h"
#include "RegistroAluno.h"
#include "constantes.h"
#include <fstream>
using namespace std;

template <>
Arquivo<Registro>::Arquivo(string filename, Formato formato)
    : filename(filename), formato(formato) {}

template <> void Arquivo<Registro>::adicionar_registro(Registro &reg) {
  fstream file(this->filename, ios::in | ios::out | ios::binary);

  if (!file.is_open()) {
    cerr << "Couldn't open the file \"" << this->filename << "\"." << endl;
    return;
  }

  FileHeader header;
  bool header_read_success = read_header(file, header);

  if (!header_read_success) {
    // inicializa novo cabeçalho
    header.registro_formato = this->formato;
    header.num_registros = 0;
    header.total_data_size = 0;
    header.last_modified = time(nullptr);
  }

  file.seekp(HEADER_SIZE + header.total_data_size, ios::beg);
  Buffer buffer;
  reg.pack(buffer, this->formato);
  long long record_size = buffer.data.size();
  buffer.write(file);

  header.num_registros++;
  header.total_data_size += record_size;
  header.last_modified = time(nullptr);

  if (!write_header(file, header)) {
    cerr << "Couldn't update the header file." << endl;
  }
  file.close();
}

template <> vector<Registro> Arquivo<Registro>::ler_registros() {
  fstream file(this->filename, ios::in | ios::binary);
  vector<Registro> registros;

  if (!file.is_open()) {
    cerr << "Couldn't open the file \"" << this->filename << "\"." << endl;
    return registros;
  }

  FileHeader header;
  if (!read_header(file, header)) {
    cerr << "Couldn't read the header." << endl;
    return registros;
  }

  Buffer buffer;
  file.seekg(HEADER_SIZE, ios::beg);
  if (!buffer.read(file, header.total_data_size)) {
    cerr << "Couldn't read file data." << endl;
    return registros;
  };

  for (int i = 0; i < header.num_registros; ++i) {
    // PRECISA ESPECIALIZAR PARA PODER UTILIZAR MÉTODOS DE PACK E UNPACK
    RegistroAluno reg_aluno;
    reg_aluno.unpack(buffer, this->formato);
    registros.push_back(reg_aluno);
  }
  return registros;
}

template <class T> vector<T> Arquivo<T>::read_csv_file(char sep, int skiprows) {
  return vector<T>();
}

template <class T>
bool Arquivo<T>::read_header(std::fstream &file, FileHeader &header) {
  file.seekg(0, std::ios::beg);
  file.read(reinterpret_cast<char *>(&header), HEADER_SIZE);
  return file.gcount() == HEADER_SIZE;
}

template <class T>
bool Arquivo<T>::write_header(std::fstream &file, const FileHeader &header) {
  file.seekp(0, std::ios::beg);
  file.write(reinterpret_cast<const char *>(&header), HEADER_SIZE);
  return file.good();
}
