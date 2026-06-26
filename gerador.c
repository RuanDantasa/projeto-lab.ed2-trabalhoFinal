#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função que gera um único usuário no formato [8 letras][3 números]
void gerar_usuario(FILE *arquivo) {
    // Gera 8 letras aleatórias
    for(int i = 0; i < 8; i++) {
        char letra = 'a' + (rand() % 26);
        fprintf(arquivo, "%c", letra);
    }
    
    // Gera 3 números aleatórios
    for(int i = 0; i < 3; i++) {
        char numero = '0' + (rand() % 10);
        fprintf(arquivo, "%c", numero);
    }
    
    fprintf(arquivo, "\n"); // Pula de linha para o próximo usuário
}

int main(int argc, char *argv[]) {
    // Pega a quantidade do terminal (ou usa 1000 como padrão)
    int quantidade = 1000; 
    if (argc > 1) {
        quantidade = atoi(argv[1]);
    }

    FILE *arquivo = fopen("usuarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

    // Inicializa a semente de aleatoriedade usando o relógio do PC
    srand(time(NULL));

    for(int i = 0; i < quantidade; i++) {
        gerar_usuario(arquivo);
    }

    fclose(arquivo);
    printf("Sucesso! Arquivo 'usuarios.txt' gerado com %d registros.\n", quantidade);
    
    return 0;
}