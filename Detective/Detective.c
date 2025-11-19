#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// --------------------------------------------------------

Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro: não foi possível criar a sala.\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

// --------------------------------------------------------

void explorarSalas(Sala *atual) {
    char opcao;

    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Caso seja nó-folha
        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Não há mais caminhos a seguir. Fim da exploração!\n");
            return;
        }

        printf("Escolha um caminho: (e) esquerda, (d) direita, (s) sair\n");
        printf("-> ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esq != NULL)
                atual = atual->esq;
            else
                printf("Não existe caminho à esquerda!\n");

        } else if (opcao == 'd') {
            if (atual->dir != NULL)
                atual = atual->dir;
            else
                printf("Não existe caminho à direita!\n");

        } else if (opcao == 's') {
            printf("Encerrando exploração...\n");
            return;

        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// --------------------------------------------------------

int main() {

    // Construindo manualmente a árvore:

    Sala *hall = criarSala("Hall de Entrada");
    hall->esq = criarSala("Sala de Estar");
    hall->dir = criarSala("Cozinha");

    hall->esq->esq = criarSala("Biblioteca");
    hall->esq->dir = criarSala("Jardim");

    hall->dir->dir = criarSala("Despensa");

    printf("=== Detective Quest: Exploração da Mansão ===\n");
    explorarSalas(hall);

    return 0;
}

