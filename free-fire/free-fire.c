#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// VETOR
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

// LISTA
No* inicioLista = NULL;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// Inserir item no vetor
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("\n[Mochila cheia] Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\nNome do item: ");
    scanf("%s", novo.nome);

    printf("Tipo do item: ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalVetor] = novo;
    totalVetor++;

    printf("\nItem adicionado ao vetor!\n");
}

// Listar itens do vetor
void listarItensVetor() {
    printf("\n--- Itens no Vetor ---\n");
    if (totalVetor == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < totalVetor; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

// Remover item por nome do vetor
void removerItemVetor() {
    char nome[30];
    printf("\nNome do item a remover: ");
    scanf("%s", nome);

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {

            for (int j = i; j < totalVetor - 1; j++)
                mochilaVetor[j] = mochilaVetor[j + 1];

            totalVetor--;
            printf("\nItem removido!\n");
            return;
        }
    }

    printf("\nItem não encontrado.\n");
}

// Busca sequencial no vetor
void buscarSequencialVetor() {
    char nome[30];
    printf("\nNome do item a buscar: ");
    scanf("%s", nome);

    comparacoesSequencial = 0;

    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações feitas: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("\nItem não encontrado.\n");
    printf("Comparações feitas: %d\n", comparacoesSequencial);
}

// Ordenar vetor (Bubble Sort)
void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }

    printf("\nVetor ordenado alfabeticamente por nome!\n");
}

// Busca binária no vetor
void buscarBinariaVetor() {
    if (totalVetor == 0) {
        printf("\nO vetor está vazio.\n");
        return;
    }

    char nome[30];
    printf("\nNome do item para busca binária: ");
    scanf("%s", nome);

    int inicio = 0, fim = totalVetor - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(nome, mochilaVetor[meio].nome);

        if (cmp == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[meio].nome,
                   mochilaVetor[meio].tipo,
                   mochilaVetor[meio].quantidade);
            printf("Comparações feitas (binária): %d\n", comparacoesBinaria);
            return;
        }
        else if (cmp > 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    printf("\nItem não encontrado.\n");
    printf("Comparações feitas (binária): %d\n", comparacoesBinaria);
}
// Inserir item na lista
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));

    printf("\nNome do item: ");
    scanf("%s", novo->dados.nome);

    printf("Tipo do item: ");
    scanf("%s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicioLista;
    inicioLista = novo;

    printf("\nItem inserido na lista encadeada!\n");
}

// Listar itens da lista
void listarItensLista() {
    if (inicioLista == NULL) {
        printf("\nLista vazia.\n");
        return;
    }

    printf("\n--- Itens na Lista Encadeada ---\n");

    No* aux = inicioLista;
    int i = 1;

    while (aux != NULL) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
               i, aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
        i++;
    }
}

// Remover item da lista
void removerItemLista() {
    char nome[30];
    printf("\nNome do item a remover: ");
    scanf("%s", nome);

    No *aux = inicioLista, *ant = NULL;

    while (aux != NULL) {
        if (strcmp(aux->dados.nome, nome) == 0) {

            if (ant == NULL)
                inicioLista = aux->proximo;
            else
                ant->proximo = aux->proximo;

            free(aux);
            printf("\nItem removido da lista!\n");
            return;
        }

        ant = aux;
        aux = aux->proximo;
    }

    printf("\nItem não encontrado.\n");
}

// Busca na lista
void buscarSequencialLista() {
    char nome[30];
    printf("\nNome do item a buscar: ");
    scanf("%s", nome);

    comparacoesSequencial = 0;

    No* aux = inicioLista;
    while (aux != NULL) {
        comparacoesSequencial++;

        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
            printf("Comparações feitas: %d\n", comparacoesSequencial);
            return;
        }
        aux = aux->proximo;
    }

    printf("\nItem não encontrado.\n");
    printf("Comparações feitas: %d\n", comparacoesSequencial);
}
void menuVetor() {
    int op;
    do {
        printf("\n=== Mochila com Vetor ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar sequencial\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Buscar binária (após ordenar)\n");
        printf("0 - Voltar\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;
        }

    } while (op != 0);
}

void menuLista() {
    int op;
    do {
        printf("\n=== Mochila com Lista Encadeada ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar sequencial\n");
        printf("0 - Voltar\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
        }

    } while (op != 0);
}
int main() {
    int escolha;

    do {
        printf("\n======= Sistema de Mochila =======\n");
        printf("1 - Usar mochila com Vetor\n");
        printf("2 - Usar mochila com Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1) menuVetor();
        if (escolha == 2) menuLista();

    } while (escolha != 0);

    printf("\nEncerrando o sistema...\n");
    return 0;
}
