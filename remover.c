#include <stdio.h>
#include <stdlib.h>

/*NÃO SEI SE TA FUNCIONANDO, MAS SE FUNCIONAR, FALTA TRATAMENTO DE DADOS  OBS: O CHAT DIZ QUE FUNCIONA*/

#define MAX_PRODUTOS 100 // Limite máximo de produtos

typedef struct Produto{
  int id;
  char *nome;
  float preco;
  int quant_estoque;
}Produto;

Produto produtos[MAX_PRODUTOS]; // Lista de produtos
int totalProdutos = 0;

void remover(){
    if(totalProdutos == 0){
        printf("Nenhum produto cadastrado\n");
        return;
    }else{
        int id;
        printf("Digite o ID do produto que deseja remover: ");
        scanf("%d", &id);
        int indice = -1;
        for(int i = 0;i<totalProdutos;i++){
            if(produtos[i].id == id){
                indice = i;
                break;
            }
        }
        if(indice == -1){
            printf("\nProduto nao encontrado\n");
            return;
        }
        int quantre = 0;
        printf("ID: %d, Nome: %s, Preco: %f, Quantidade em estoque: %d\n", produtos[indice].id, produtos[indice].nome, produtos[indice].preco, produtos[indice].quant_estoque);
        while(quantre <= 0 || quantre > produtos[indice].quant_estoque){
            printf("Digite a quantidade que deseja remover: \n");
            scanf("%d", &quantre);
                if(quantre <= 0 || quantre > produtos[indice].quant_estoque){
                    printf("Quantidade invalida para remocao\n");
                    while(getchar() != '\n');
                }
        }
        produtos[indice].quant_estoque -= quantre;

        if(produtos[indice].quant_estoque == 0){
            for(int i = indice;i<totalProdutos-1;i++){
                produtos[i] = produtos[i+1];
            }
            totalProdutos--;
            printf("Produto removido da lista, pelo estoque ter sido zerado\n");
        }else{
            printf("Quantidade removida com sucesso");
        }
        salvarEmArquivo();
    }
}