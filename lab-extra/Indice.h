#ifndef INDICE_H
#define INDICE_H

class Indice {
public:
    int matricula;
    long byte_offset;
    
    Indice();
    
    Indice(int mat, long offset);
    
    bool operator<(const Indice& outro) const;
};

#endif
