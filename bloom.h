#ifndef BLOOM.H
#define BLOOM.H

#include <stdint.h>

typedef struct filtrobloom{ 
    uint8_t *vetor_bits;
    int tam_vetor;
    int qtd_hashs;
} filtroBloom;



#endif