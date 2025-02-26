#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int id;
    char nome[51];
    float preco;
    int quant_estoque;
} Produto;

void addProduto() {
    Produto novo;
    FILE *arquivo;
    int last_id = 0;
    //buffer para leituras temporarias (usado pra impedir q o usuario seja burro)
    char buffer[50];

    // Recupera o último ID registrado (se houver)
    FILE *f = fopen("produto.txt", "r");
    if (f != NULL) {
        Produto temp;
        while (fscanf(f, "%d\t%50[^\t]\t%f\t%d\n", &temp.id, temp.nome, &temp.preco, &temp.quant_estoque) != EOF) {
            last_id = temp.id;
        }
        fclose(f);
    }
    novo.id = last_id + 1;

    // Leitura e validação do nome (somente letras e espaços)
    while (1) {
        printf("Se for escrever numero, escreva por extenso\n");
        printf("Digite o nome do produto (ate 50 caracteres, apenas letras e espacos): ");
        if (fgets(novo.nome, sizeof(novo.nome), stdin) == NULL) continue;
        size_t len = strlen(novo.nome);
        if (len > 0 && novo.nome[len - 1] == '\n') {
            novo.nome[len - 1] = '\0';
        }
        if (strlen(novo.nome) == 0) {
            printf("\nNome nao pode ser vazio.\n\n");
            continue;
        }
        int valido = 1;
        int contemLetra = 0;
        for (size_t i = 0; i < strlen(novo.nome); i++) {
            if (!isalpha(novo.nome[i]) && novo.nome[i] != ' ') {
                valido = 0;
                printf("\nNome invalido. Use apenas letras e espacos.\n\n");
                break;
            }
            if (isalpha(novo.nome[i])) {
                contemLetra = 1;
            }
        }
        if (!contemLetra) {
            valido = 0;
            printf("\nNome invalido. O nome deve conter ao menos uma letra.\n\n");
        }
        if (valido)
            break;

    }

    // Leitura e validação do preco, vai cair em loop ate o usuario digitar um numero válido
    // while(1) = while TRUE esse sscanf tenta pegar um float do buffer e armazena no novo.preco
    while (1) {
        printf("Digite o preco do produto: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (sscanf(buffer, "%f", &novo.preco) == 1)
            break;
        else
            printf("\nEntrada invalida. Digite um numero.\n\n");
    }

    // Leitura e validação da quantidade 
    while (1) {
        printf("Digite a quantidade de produtos no estoque: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (sscanf(buffer, "%d", &novo.quant_estoque) == 1)
            break;
        else
            printf("\nEntrada invalida. Digite um numero inteiro.\n\n");
    }

    // Salva os dados no arquivo produto.txt
    arquivo = fopen("produto.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(arquivo, "%d\t%s\t%.2f\t%d\n", novo.id, novo.nome, novo.preco, novo.quant_estoque);
    fclose(arquivo);
    printf("Produto cadastrado com ID %d.\n", novo.id);
}

void listarProdutos() {
    FILE *arquivo = fopen("produto.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }
    Produto produto;
    int encontrou = 0;
    printf("\n=== Lista de produtos ===\n");
    while (fscanf(arquivo, "%d\t%50[^\t]\t%f\t%d\n", &produto.id, produto.nome, &produto.preco, &produto.quant_estoque) != EOF) {
        encontrou = 1;
        printf("ID: %d\n", produto.id);
        printf("Nome: %s\n", produto.nome);
        printf("Preco: R$%.2f\n", produto.preco);
        printf("Quantidade no Estoque: %d\n", produto.quant_estoque);
        printf("--------------------------\n");
    }
    if (!encontrou) {
        printf("Nenhum produto encontrado.\n");
    }
    fclose(arquivo);
}

void updateProduto() {
    int id;
    char buffer[50];
    while(1){
        printf("Digite o ID do produto a ser atualizado: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) return;
        if (sscanf(buffer, "%d", &id) == 1)
            break;
        else
            printf("\nEntrada invalida. Digite um numero inteiro.\n\n");
        }
    
    // if (fgets(buffer, sizeof(buffer), stdin) == NULL) return;
    // sscanf(buffer, "%d", &id);

    

    FILE *arquivo = fopen("produto.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    //cria arquivo temporario para auxiliar na atualização
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    Produto prod;
    int encontrado = 0;
    //ler os dados do arquivo produto.txt linha por linha assumindo que estão da forma: id nome preço quantidade
    while (fscanf(arquivo, "%d\t%50[^\t]\t%f\t%d\n", &prod.id, prod.nome, &prod.preco, &prod.quant_estoque) != EOF) {
        if (prod.id == id) {
            encontrado = 1;
            printf("\nProduto encontrado:\n");
            printf("ID: %d\n", prod.id);
            printf("Nome: %s\n", prod.nome);
            printf("Preco: %.2f\n", prod.preco);
            printf("Quantidade: %d\n", prod.quant_estoque);

            // Atualizando os dados do produto
            while (1) {
                printf("Digite o novo nome (somente letras e espacos): ");
                if (fgets(prod.nome, sizeof(prod.nome), stdin) == NULL) continue;
                size_t len = strlen(prod.nome);
                if (len > 0 && prod.nome[len - 1] == '\n') {
                    prod.nome[len - 1] = '\0';
                }
                if (strlen(prod.nome) == 0) {
                    printf("\nNome nao pode ser vazio.\n\n");
                    continue;
                }
                int valido = 1;
                int contemLetra = 0;
                for (size_t i = 0; i < strlen(prod.nome); i++) {
                    if (!isalpha(prod.nome[i]) && prod.nome[i] != ' ') {
                        valido = 0;
                        printf("\nNome invalido. Use apenas letras e espacos.\n\n");
                        break;
                    }
                    if (isalpha(prod.nome[i])) {
                        contemLetra = 1;
                    }
                }
                if (!contemLetra) {
                    valido = 0;
                    printf("\nNome invalido. O nome deve conter ao menos uma letra.\n\n");
                }

                if (valido) break;
            }

            // Preco
            while (1) {
                printf("Digite o novo preco: ");
                if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
                if (sscanf(buffer, "%f", &prod.preco) == 1)
                    break;
                else
                    printf("\nEntrada invalida. Digite um numero.\n\n");
            }

            // Quantidade
            while (1) {
                printf("Digite a nova quantidade: ");
                if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
                if (sscanf(buffer, "%d", &prod.quant_estoque) == 1)
                    break;
                else
                    printf("\nEntrada invalida. Digite um numero inteiro.\n\n");
            }
        }
        fprintf(tempFile, "%d\t%s\t%.2f\t%d\n", prod.id, prod.nome, prod.preco, prod.quant_estoque);
    }

    fclose(arquivo);
    fclose(tempFile);

    if (!encontrado) {
        printf("Produto com ID %d nao encontrado.\n", id);
        remove("temp.txt");
    } else {
        remove("produto.txt");
        rename("temp.txt", "produto.txt");
        printf("Produto atualizado com sucesso.\n");
    }
}


void removeProduto() {
    int id;
    char buffer[50];
    
    // Solicita o ID do produto
    while(1){
        printf("Digite o ID do produto a ser removido: ");
        if(fgets(buffer, sizeof(buffer), stdin) == NULL)
            return;
        if(sscanf(buffer, "%d", &id) == 1)
            break;
        else
            printf("\nEntrada invalida. Digite um numero.\n");
        
    }
    

    FILE *arquivo = fopen("produto.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    // Cria um arquivo temporário para escrever como vai ficar o produto dps da remoção
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    Produto prod;
    int encontrado = 0;
    int removalDone = 0;
    
    // Lê todas as linhas do arquivo
    while (fscanf(arquivo, "%d\t%50[^\t]\t%f\t%d\n", 
                &prod.id, prod.nome, &prod.preco, &prod.quant_estoque) != EOF) {
        // Se o produto com o ID informado for encontrado e ainda não tiver sido processado
        if (prod.id == id && !removalDone) {
            encontrado = 1;
            printf("Produto encontrado:\n");
            printf("ID: %d, Nome: %s, Preco: %.2f, Quantidade: %d\n", 
                prod.id, prod.nome, prod.preco, prod.quant_estoque);
            
            int quantre = 0;
            // Loop para garantir que a quantidade a remover é válida
            while (quantre <= 0 || quantre > prod.quant_estoque) {
                printf("Digite a quantidade que deseja remover: ");
                if (fgets(buffer, sizeof(buffer), stdin) == NULL)
                    break;
                sscanf(buffer, "%d", &quantre);
                if (quantre <= 0 || quantre > prod.quant_estoque) {
                    printf("Quantidade invalida para remocao.\n");
                }
            }
            
            prod.quant_estoque -= quantre;
            // Se o estoque for zerado, não escreve o produto no arquivo temporário
            if (prod.quant_estoque == 0) {
                printf("Produto removido da lista, pelo estoque ter sido zerado.\n");
            } else {
                printf("Quantidade removida com sucesso.\n");
                fprintf(tempFile, "%d\t%s\t%.2f\t%d\n", 
                        prod.id, prod.nome, prod.preco, prod.quant_estoque);
            }
            removalDone = 1;
        } else {
            // Para os demais produtos, apenas regrava os dados no arquivo temporário
            fprintf(tempFile, "%d\t%s\t%.2f\t%d\n", 
                    prod.id, prod.nome, prod.preco, prod.quant_estoque);
        }
    }

    fclose(arquivo);
    fclose(tempFile);

    if (!encontrado) {
        printf("Produto com ID %d nao encontrado.\n", id);
        remove("temp.txt");
    } else {
        remove("produto.txt");
        rename("temp.txt", "produto.txt");
    }
}

void menu(){
    printf("\nMenu:\n");
    printf("1 - Adicionar produto\n");
    printf("2 - Atualizar produto\n");
    printf("3 - Remover produto\n");
    printf("4 - Listar produtos\n");
    printf("5 - Sair\n");
    printf("Escolha uma opcao: ");
}
int main() {
    int opcao;
    char buffer[10];

    do {
        menu();
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (sscanf(buffer, "%d", &opcao) != 1){
            printf("Opcao invalida.\n");
            continue;
        }else{

            switch (opcao) {
                case 1:
                    addProduto();
                    break;
                case 2:
                    updateProduto();
                    break;
                case 3:
                    removeProduto();
                    break;
                case 4:
                    listarProdutos();
                    break;
                case 5:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opcao invalida.\n");
            }
        }
    } while (opcao != 5);

    return 0;
}
