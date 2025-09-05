#include "pessoa.hpp"
#include "utils.hpp"
using namespace std;

int main() {
  vector<Pessoa *> pessoas;
  populate_pessoas_vector_from_file(
      pessoas, "Arquivos_Nomes e Idades/Nomes_Idades_1.csv", ",");

  populate_pessoas_vector_from_file(
      pessoas, "Arquivos_Nomes e Idades/Nomes_Idades_2.csv", ",");
  populate_pessoas_vector_from_file(
      pessoas, "Arquivos_Nomes e Idades/Nomes_Idades_3.csv", ",");
  populate_pessoas_vector_from_file(
      pessoas, "Arquivos_Nomes e Idades/Nomes_Idades_4.csv", ",");

  populate_pessoas_vector_from_file(
      pessoas, "Arquivos_Nomes e Idades/Nomes_Idades_5.csv", ",");

  print_pessoas_vector(pessoas);
  save_pessoas_vector_to_file(pessoas, "saida.txt");
  dealocate_pessoas(pessoas);
  return 0;
}
