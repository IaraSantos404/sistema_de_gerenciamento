#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    int id;
    char nome[51];
    float preco;
    int quant_estoque;
} Produto;

void add(void) {
    Produto novo;
    FILE *arquivo = fopen("teste.c", "rb+");

    if (arquivo == NULL) {
        // Se o arquivo não existir, cria-o
        arquivo = fopen("teste.c", "wb+");
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo.\n");
            return;
        }
    }

    Produto temp;
    int ultimo_id = 0;
    while (fread(&temp, sizeof(Produto), 1, arquivo) == 1) {
        ultimo_id = temp.id;
    }
    novo.id = ultimo_id + 1;

    printf("Digite o nome do produto (Ate 50 caracteres): ");
    scanf(" %50[^\n]", novo.nome);

    printf("Digite o preco do produto: ");
    scanf("%f", &novo.preco);

    printf("Digite a quantidade de produtos que vao entrar no estoque: ");
    scanf("%d", &novo.quant_estoque);

    fseek(arquivo, 0, SEEK_END);
    fwrite(&novo, sizeof(Produto), 1, arquivo);

    fclose(arquivo);
    printf("Produto cadastrado com ID %d.\n", novo.id);
}
