#include "Arquivo.h"
#include "Registro.h"
#include "RegistroAluno.h"
#include "formato.h"
#include <vector>

using namespace std;

void test_delimitado(vector<unique_ptr<Registro>> &registros, string file_csv) {
  string filename = "saida_delimitado.bin";
  Arquivo<Registro> arquivo_regs(filename, Formato::DELIMITADO);
  for (const auto &reg_ptr : registros) {
    arquivo_regs.adicionar_registro(*reg_ptr);
  }

  cout << "Conteúdo de '" << file_csv << "' salvo em: " << filename << endl;

  registros = arquivo_regs.ler_registros();
  cout << "----------------------------------------------------------------------------------------------------" << endl; 
  cout << "Arquivo '" << filename << "' lido com sucesso." << endl
       << "Conteudo: " << endl;
  cout << registros.size() << " registros encontrados." << endl;
  for (const auto &reg_ptr : registros) {
    RegistroAluno *aluno = dynamic_cast<RegistroAluno *>(reg_ptr.get());
    cout << "Nome: " << aluno->nome << " | "
         << "Matricula: " << aluno->matricula << " | "
         << "Curso: " << aluno->curso << endl;
  }
}

void test_fixo(vector<unique_ptr<Registro>> &registros, string file_csv) {
  string filename = "saida_fixo.bin";
  Arquivo<Registro> arquivo_regs(filename, Formato::FIXO);
  for (const auto &reg_ptr : registros) {
    arquivo_regs.adicionar_registro(*reg_ptr);
  }

  cout << "Conteúdo de '" << file_csv << "' salvo em: " << filename << endl;

  registros = arquivo_regs.ler_registros();
  cout << "----------------------------------------------------------------------------------------------------" << endl; 
  cout << "Arquivo '" << filename << "' lido com sucesso." << endl
       << "Conteudo: " << endl;
  cout << registros.size() << " registros encontrados." << endl;
  for (const auto &reg_ptr : registros) {
    RegistroAluno *aluno = dynamic_cast<RegistroAluno *>(reg_ptr.get());
    cout << "Nome: " << aluno->nome << " | "
         << "Matricula: " << aluno->matricula << " | "
         << "Curso: " << aluno->curso << endl;
  }
}

void test_comprimento(vector<unique_ptr<Registro>> &registros,
                      string file_csv) {
  string filename = "saida_comprimento.bin";
  Arquivo<Registro> arquivo_regs(filename, Formato::COMPRIMENTO);
  for (const auto &reg_ptr : registros) {
    arquivo_regs.adicionar_registro(*reg_ptr);
  }

  cout << "Conteúdo de '" << file_csv << "' salvo em: " << filename << endl;

  registros = arquivo_regs.ler_registros();
  cout << "----------------------------------------------------------------------------------------------------" << endl; 
  cout << "Arquivo '" << filename << "' lido com sucesso." << endl
       << "Conteudo: " << endl;
  cout << registros.size() << " registros encontrados." << endl;
  for (const auto &reg_ptr : registros) {
    RegistroAluno *aluno = dynamic_cast<RegistroAluno *>(reg_ptr.get());
    cout << "Nome: " << aluno->nome << " | "
         << "Matricula: " << aluno->matricula << " | "
         << "Curso: " << aluno->curso << endl;
  }
}

int main() {
  vector<unique_ptr<Registro>> registros;
  string file_csv = "./dados.csv";
  Arquivo<Registro> arquivo_csv(file_csv, Formato::DELIMITADO);
  registros = arquivo_csv.read_csv_file(';');
  cout << "Arquivo csv '" << file_csv << "' lido com sucesso!" << endl;

  cout << "----------------------------------------------------------------------------------------------------" << endl;
  cout << "Conteúdo do arquivo CSV lido:" << endl;
  cout << registros.size() << " registros encontrados." << endl;
  test_fixo(registros, file_csv);
  test_comprimento(registros, file_csv);
  test_delimitado(registros, file_csv);

  return 0;
}
