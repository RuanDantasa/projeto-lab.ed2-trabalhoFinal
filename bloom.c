#include <stdio.h>
#include <stdlib.h>
#include "bloom.h"

void setar_bit(filtroBloom *filtro, int posicao) {
    int indice_byte = posicao / 8;
    int deslocamento_bit = posicao % 8;
    
    filtro->vetor_bits[indice_byte] |= (1 << deslocamento_bit);
}

int testar_bit(filtroBloom *filtro, int posicao) {
    int indice_byte = posicao / 8;
    int deslocamento_bit = posicao % 8;
    
    return (filtro->vetor_bits[indice_byte] & (1 << deslocamento_bit)) != 0;
}
