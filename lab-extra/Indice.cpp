#include "Indice.h"

Indice::Indice() : matricula(0), byte_offset(0) {}

Indice::Indice(int mat, long offset) : matricula(mat), byte_offset(offset) {}

bool Indice::operator<(const Indice& outro) const {
    return matricula < outro.matricula;
}
