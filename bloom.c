#include <stdio.h>
#include <stdlib.h>
#include "bloom.h"

filtroBloom *criar_bloom(int n_esperado, double prob_falso_positivo)
{
    filtroBloom *novo_filtro = (filtroBloom *)malloc(sizeof(filtroBloom));
    if (!novo_filtro){
        return NULL;
    }
    double numerador_m = -(n_esperado * log(prob_falso_positivo));
    double denominador_m = pow(log(2), 2);
    int m = (int)ceil(numerador_m / denominador_m);

    int k = (int)round(((double)m / n_esperado) * log(2));

    novo_filtro->tam_vetor = m;
    novo_filtro->qtd_hashs = k;

    int tamanho_bytes = (m + 7) / 8;

    novo_filtro->vetor_bits = (uint8_t *)calloc(tamanho_bytes, sizeof(uint8_t));

    if (!novo_filtro->vetor_bits)
    {
        free(novo_filtro);
        return NULL;
    }

    printf("[DEBUG] Bloom criado: n=%d, p=%.2f | m=%d bits (~%d bytes), k=%d hashes\n",
           n_esperado, prob_falso_positivo, m, tamanho_bytes, k);

    return novo_filtro;
}

int consultar_bloom(filtroBloom *filtro, const char *usuario)
{
    
    for (int i = 0; i < filtro->qtd_hashs; i++)
    {
        
        uint32_t hash_gigante = hash_djb2_semeada(usuario, i);
        int posicao_no_vetor = hash_gigante % filtro->tam_vetor;
        
        if (testar_bit(filtro, posicao_no_vetor) == 0)
        {
            return 0;
        }
    }
    
    return 1;
}

void inserir_bloom(filtroBloom *filtro, const char *usuario)
{
    for (int i = 0; i < filtro->qtd_hashs; i++)
    {
        uint32_t hash_gigante = hash_djb2_semeada(usuario, i);
        int posicao_no_vetor = hash_gigante % filtro->tam_vetor;
        setar_bit(filtro, posicao_no_vetor);
    }
}

void liberar_bloom(filtroBloom *filtro)
{
    if (filtro)
    {
        if (filtro->vetor_bits)
        {
            free(filtro->vetor_bits);
        }
        free(filtro);
    }
}

void setar_bit(filtroBloom *filtro, int posicao)
{
    int indice_byte = posicao / 8;
    int deslocamento_bit = posicao % 8;

    filtro->vetor_bits[indice_byte] |= (1 << deslocamento_bit);
}

int testar_bit(filtroBloom *filtro, int posicao)
{
    int indice_byte = posicao / 8;
    int deslocamento_bit = posicao % 8;

    return (filtro->vetor_bits[indice_byte] & (1 << deslocamento_bit)) != 0;
}

uint32_t hash_djb2_semeada(const char *str, int semente) {
    unsigned long hash = 5381;
    hash += semente; 
    int caractere;

    while ((caractere = *str++)) {
        hash = ((hash << 5) + hash) + caractere;
    }
    return (uint32_t)hash;
}