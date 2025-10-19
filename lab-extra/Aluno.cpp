#include "Aluno.h"
#include <cstring>

Aluno::Aluno() : matricula(0) {
    memset(nome, 0, sizeof(nome));
    memset(curso, 0, sizeof(curso));
}

Aluno::Aluno(int mat, const char* n, const char* c) : matricula(mat) {
    memset(nome, 0, sizeof(nome));
    memset(curso, 0, sizeof(curso));
    
    if (n) {
        strncpy(nome, n, sizeof(nome) - 1);
    }
    if (c) {
        strncpy(curso, c, sizeof(curso) - 1);
    }
}
