#include "Arquivo.h"
#include "Buffer.h"
#include "Registro.h"
#include <vector>

using namespace std;

int main() {
  vector<Registro> registros;
  string file_csv = "./Arquivos_Nomes e Idades/Nomes_Idades_1.csv";
  Arquivo arquivo_csv(file_csv);
  registros = arquivo_csv.read_csv_file(',');
  cout << "Arquivo csv '" << file_csv << "' lido com sucesso!" << endl;

  string filename = "saida.bin";
  Arquivo arquivo_regs(filename);
  for (auto reg : registros) {
    arquivo_regs.add_fixed_registro(reg);
  }

  cout << "Conteúdo de '" << file_csv << "' salvo em: " << filename << endl;

  registros = arquivo_regs.read_fixed_registros();

  cout << "Arquivo '" << filename << "' lido com sucesso." << endl
       << "Conteudo: " << endl;

  for (auto reg : registros) {
    cout << "Nome: " << reg.name << " | " << "Idade: " << (int)reg.idade
         << endl;
  }

  return 0;
}
