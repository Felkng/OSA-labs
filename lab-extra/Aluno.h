#ifndef ALUNO_H
#define ALUNO_H

class Aluno {
public:
    int matricula;
    char nome[50];
    char curso[30];
    
    Aluno();
    
    Aluno(int mat, const char* n, const char* c);
};

#endif
