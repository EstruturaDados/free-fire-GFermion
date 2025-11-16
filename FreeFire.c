#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 100

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} item;

void cadastroItem(item *inventario, int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("Inventário cheio! Não é possível cadastrar mais itens.\n\n");
        return;
    }
    
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", inventario[*contador].nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", inventario[*contador].tipo);
    printf("Digite a quantidade do item: ");
    
    // Verifica se a leitura da quantidade foi bem-sucedida
    if (scanf("%d", &inventario[*contador].quantidade) != 1) {
        printf("Erro: Quantidade inválida!\n\n");
        // Limpa o buffer de entrada
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    
    (*contador)++;
    printf("Item cadastrado com sucesso!\n\n");
}

void listarItens(item *inventario, int contador) {
    if (contador == 0) {
        printf("Inventário vazio.\n\n");
        return;
    }
    
    printf("\nInventário de Itens:\n");
    for (int i = 0; i < contador; i++) {
        printf("Item %d:\n", i + 1);
        printf("Nome: %s\n", inventario[i].nome);
        printf("Tipo: %s\n", inventario[i].tipo);
        printf("Quantidade: %d\n\n", inventario[i].quantidade);
    }
}

void buscarItem(item *inventario, int contador) {
    if (contador == 0) {
        printf("Inventário vazio.\n\n");
        return;
    }
    
    char nomeBusca[30];
    printf("Digite o nome do item a ser buscado: ");
    scanf(" %[^\n]", nomeBusca);
    
    int encontrado = 0;
    for (int i = 0; i < contador; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s\n", inventario[i].nome);
            printf("Tipo: %s\n", inventario[i].tipo);
            printf("Quantidade: %d\n\n", inventario[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item não encontrado.\n\n");
    }
}

void removerItem(item *inventario, int *contador) {
    if (*contador == 0) {
        printf("Inventário vazio.\n\n");
        return;
    }
    
    char nomeRemover[30];
    printf("Digite o nome do item a ser removido: ");
    scanf(" %[^\n]", nomeRemover);
    
    for (int i = 0; i < *contador; i++) {
        if (strcmp(inventario[i].nome, nomeRemover) == 0) {
            for (int j = i; j < *contador - 1; j++) {
                inventario[j] = inventario[j + 1];
            }
            (*contador)--;
            printf("Item removido com sucesso.\n\n");
            return;
        }
    }
    printf("Item não encontrado.\n\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pressioneEnter() {
    printf("Pressione Enter para continuar...");
    limparBuffer();
    getchar();
}

int main() {
    item *inventario = malloc(MAX_ITENS * sizeof(item));
    
    // Verifica se a alocação de memória foi bem-sucedida
    if (inventario == NULL) {
        printf("Erro: Não foi possível alocar memória!\n");
        return 1;
    }
    
    int contador = 0;
    int opcao;

    do {
        printf("Menu de Inventário:\n");
        printf("1. Cadastrar Item\n");
        printf("2. Listar Itens\n");
        printf("3. Buscar Item\n");
        printf("4. Remover Item\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        
        // Verifica se a leitura da opção foi bem-sucedida
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida. Tente novamente.\n\n");
            // Limpa o buffer de entrada
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1:
                cadastroItem(inventario, &contador);
                pressioneEnter();
                break;
            case 2:
                listarItens(inventario, contador);
                pressioneEnter();
                break;
            case 3:
                buscarItem(inventario, contador);
                pressioneEnter();
                break;
            case 4:
                removerItem(inventario, &contador);
                pressioneEnter();
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                pressioneEnter();
        }
    } while (opcao != 5);

    free(inventario);
    return 0;
}
