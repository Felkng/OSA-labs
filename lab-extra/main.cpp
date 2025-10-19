#include "SistemaGerenciador.h"
#include <iostream>

using namespace std;

int main() {
    SistemaGerenciador sistema("alunos.csv", "alunos.dat", "indices.dat");
    
    sistema.iniciar();
    
    return 0;
}
