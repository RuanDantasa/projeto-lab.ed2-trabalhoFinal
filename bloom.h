#ifndef BLOOM.H
#define BLOOM.H

#include <stdint.h>

typedef struct filtrobloom{ 
    uint8_t *vetor_bits;
    int tam_vetor;
    int qtd_hashs;
} filtroBloom;

void setar_bit(filtroBloom *filtro, int posicao);
int testar_bit(filtroBloom *filtro, int posicao);
uint32_t hash_fnv1a(const char *str, int semente);
int consultar_bloom(filtroBloom *filtro, const char *usuario);
void inserir_bloom(filtroBloom *filtro, const char *usuario);
filtroBloom* criar_bloom(int tamanho_bits, int quantidade_hashes);
void liberar_bloom(filtroBloom *filtro);


#endif