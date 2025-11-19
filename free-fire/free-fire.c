#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item inventario[MAX_ITENS];
int totalItens = 0;
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\nA mochila está cheia! Remova algo antes de adicionar novos itens.\n");
        return;
    }

    Item novo;

    printf("\n--- Cadastro de Item ---\n");

    printf("Nome do item: ");
    scanf("%s", novo.nome);

    printf("Tipo (arma, municao, cura...): ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    inventario[totalItens] = novo;
    totalItens++;

    printf("\nItem cadastrado com sucesso!\n");
}
void listarItens() {
    printf("\n--- Itens na Mochila ---\n");
    if (totalItens == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
            i + 1, inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
}

void buscarItem() {
    char buscado[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf("%s", buscado);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(inventario[i].nome, buscado) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
            return;
        }
    }

    printf("\nO item não foi encontrado na mochila.\n");
}
void removerItem() {
    char removido[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf("%s", removido);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(inventario[i].nome, removido) == 0) {

            // Desloca os itens para preencher o espaço
            for (int j = i; j < totalItens - 1; j++) {
                inventario[j] = inventario[j + 1];
            }

            totalItens--;
            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nO item não foi encontrado.\n");
}

int main() {
    int opcao;

    do {
        printf("\n======= Sistema de Inventário do Jogador =======\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("\nEncerrando o sistema...\n"); break;
            default: printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
