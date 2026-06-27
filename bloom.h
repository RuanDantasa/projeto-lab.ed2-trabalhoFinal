#ifndef BLOOM.H
#define BLOOM.H

#include <stdint.h>

typedef struct filtrobloom {
    uint8_t *vetor_bits;  
    int tam_vetor;        
    int qtd_hashs;        
} filtroBloom;

void setar_bit(filtroBloom *filtro, int posicao);
int testar_bit(filtroBloom *filtro, int posicao);
uint32_t hash_djb2_semeada(const char *str, int semente);
int consultar_bloom(filtroBloom *filtro, const char *usuario);
void inserir_bloom(filtroBloom *filtro, const char *usuario);
filtroBloom *criar_bloom(int n_esperado, double prob_falso_positivo);
void liberar_bloom(filtroBloom *filtro);


#endif