#include "funcoes.hpp"
#include <string>
#include <vector>

int main() {

  vector<string> nomes;
  populate_vector_with_file(nomes, "nomes.txt");
  write_file(nomes, "saida.txt");

  return 0;
}
