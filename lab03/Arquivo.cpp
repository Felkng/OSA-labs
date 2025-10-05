#include "Arquivo.h"
#include "Buffer.h"
#include "FileHeader.h"
#include "Registro.h"
#include "RegistroAluno.h"
#include "constantes.h"
#include <fstream>
#include <memory>
using namespace std;

template <>
Arquivo<Registro>::Arquivo(string filename, Formato formato)
    : filename(filename), formato(formato) {}

template <> void Arquivo<Registro>::adicionar_registro(Registro &reg) {
  fstream file(this->filename, ios::in | ios::out | ios::binary);

  bool is_new_file = false;
  
  if (!file.is_open()) {
    // Tenta criar o arquivo se não existir
    file.open(this->filename, ios::out | ios::binary);
    if (!file.is_open()) {
      cerr << "Não foi possível abrir o arquivo: \"" << this->filename << "\"."
           << endl;
      return;
    }
    is_new_file = true;
    file.close();
    file.open(this->filename, ios::in | ios::out | ios::binary);
  }

  FileHeader header;
  bool header_read_success = false;
  
  if (!is_new_file) {
    header_read_success = read_header(file, header);
  }

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
  file.flush();

  header.num_registros++;
  header.total_data_size += record_size;
  header.last_modified = time(nullptr);


  file.seekp(0, ios::beg);
  file.write(reinterpret_cast<const char *>(&header), HEADER_SIZE);
  file.flush();
  
  file.close();
}

template <> vector<unique_ptr<Registro>> Arquivo<Registro>::ler_registros() {
  fstream file(this->filename, ios::in | ios::binary);
  vector<unique_ptr<Registro>> registros;

  if (!file.is_open()) {
    cerr << "Não foi possível abrir o arquivo: \"" << this->filename << "\"."
         << endl;
    return registros;
  }

  FileHeader header;
  if (!read_header(file, header)) {
    cerr << "Não foi possível ler o cabeçalho do arquivo." << endl;
    file.close();
    return registros;
  }

  Buffer buffer;
  file.seekg(HEADER_SIZE, ios::beg);
  if (!buffer.read(file, header.total_data_size)) {
    cerr << "Não foi possível ler o conteúdo do arquivo." << endl;
    return registros;
  };

  buffer.pointer = 0;

  for (int i = 0; i < header.num_registros; ++i) {
    // PRECISA ESPECIALIZAR PARA PODER UTILIZAR MÉTODOS DE PACK E UNPACK
    unique_ptr<RegistroAluno> reg_aluno = make_unique<RegistroAluno>();
    reg_aluno->unpack(buffer, this->formato);
    registros.push_back(std::move(reg_aluno));
  }
  file.close();
  return registros;
}

template <>
vector<unique_ptr<Registro>> Arquivo<Registro>::read_csv_file(char sep,
                                                              int skiprows) {
  Buffer buffer;
  fstream file(this->filename, ios::in);
  if (!file.is_open()) {
    cerr << "Não foi possível abrir o arquivo: \"" << this->filename << "\"."
         << endl;
    return {};
  }

  string line;
  while (skiprows > 0) {
    getline(file, line);
    skiprows--;
  }

  vector<unique_ptr<Registro>> registros;
  while (getline(file, line)) {
    Buffer buffer;
    unique_ptr<RegistroAluno> reg = make_unique<RegistroAluno>();
    *reg = reg->parse_csv(line, sep);
    registros.push_back(std::move(reg));
  }
  file.close();
  return registros;
}

template <class T>
bool Arquivo<T>::read_header(std::fstream &file, FileHeader &header) {
  file.seekg(0, std::ios::beg);
  if (file.fail()) return false;
  
  file.read(reinterpret_cast<char *>(&header), HEADER_SIZE);
  return file.gcount() == HEADER_SIZE && file.good();
}

template <class T>
bool Arquivo<T>::write_header(std::fstream &file, const FileHeader &header) {
  file.seekp(0, std::ios::beg);
  if (file.fail()) return false;
  
  file.write(reinterpret_cast<const char *>(&header), HEADER_SIZE);
  file.flush();
  return file.good();
}
