#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NOME_MAX 60
#define PISTA_MAX 120

/* -------------------------
   Estruturas de dados
   ------------------------- */

/* Sala: nó da árvore binária que representa os cômodos */
typedef struct Sala {
    char nome[NOME_MAX];
    char pista[PISTA_MAX];   // string vazia se não houver pista
    struct Sala *esq;
    struct Sala *dir;
} Sala;

/* PistaNode: nó da BST que guarda as pistas coletadas */
typedef struct PistaNode {
    char pista[PISTA_MAX];
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;

/* -------------------------
   Protótipos de funções
   ------------------------- */
Sala* criarSala(const char *nome, const char *pista);
void explorarSalasComPistas(Sala *inicio, PistaNode **raizPistas);
PistaNode* inserirPista(PistaNode *raiz, const char *pista);
int buscarPista(PistaNode *raiz, const char *pista); // 1 se encontrada, 0 se não
void exibirPistas(PistaNode *raiz);
void liberarPistas(PistaNode *raiz);
void liberarSalas(Sala *raiz);

/* -------------------------
   Implementações
   ------------------------- */

/* criarSala: cria dinamicamente uma sala com nome e pista (pode ser NULL ou "") */
Sala* criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memória para sala.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(nova->nome, nome, NOME_MAX-1);
    nova->nome[NOME_MAX-1] = '\0';
    if (pista != NULL && pista[0] != '\0') {
        strncpy(nova->pista, pista, PISTA_MAX-1);
        nova->pista[PISTA_MAX-1] = '\0';
    } else {
        nova->pista[0] = '\0';
    }
    nova->esq = nova->dir = NULL;
    return nova;
}

/* buscarPista: verifica se uma pista já está presente na BST (evita duplicatas) */
int buscarPista(PistaNode *raiz, const char *pista) {
    if (raiz == NULL) return 0;
    int cmp = strcmp(pista, raiz->pista);
    if (cmp == 0) return 1;
    if (cmp < 0) return buscarPista(raiz->esq, pista);
    return buscarPista(raiz->dir, pista);
}

/* inserirPista: insere uma pista na BST (mantém ordem alfabética) */
PistaNode* inserirPista(PistaNode *raiz, const char *pista) {
    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));
        if (novo == NULL) {
            fprintf(stderr, "Erro: falha ao alocar memória para pista.\n");
            exit(EXIT_FAILURE);
        }
        strncpy(novo->pista, pista, PISTA_MAX-1);
        novo->pista[PISTA_MAX-1] = '\0';
        novo->esq = novo->dir = NULL;
        return novo;
    }
    int cmp = strcmp(pista, raiz->pista);
    if (cmp < 0) {
        raiz->esq = inserirPista(raiz->esq, pista);
    } else if (cmp > 0) {
        raiz->dir = inserirPista(raiz->dir, pista);
    }
    /* se cmp == 0 (igual), não inserir duplicata */
    return raiz;
}

/* exibirPistas: imprime as pistas em ordem alfabética (in-order traversal) */
void exibirPistas(PistaNode *raiz) {
    if (raiz == NULL) return;
    exibirPistas(raiz->esq);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->dir);
}

/* liberarPistas: libera memória da BST de pistas */
void liberarPistas(PistaNode *raiz) {
    if (raiz == NULL) return;
    liberarPistas(raiz->esq);
    liberarPistas(raiz->dir);
    free(raiz);
}

/* liberarSalas: libera memória da árvore de salas (mapa) */
void liberarSalas(Sala *raiz) {
    if (raiz == NULL) return;
    liberarSalas(raiz->esq);
    liberarSalas(raiz->dir);
    free(raiz);
}

/* explorarSalasComPistas: navega pela árvore de salas e coleta pistas automaticamente */
void explorarSalasComPistas(Sala *inicio, PistaNode **raizPistas) {
    if (inicio == NULL) return;

    Sala *atual = inicio;
    char opcao;

    printf("=== Detective Quest: coleta de pistas ===\n");
    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);

        /* se a sala tem pista, tenta coletá-la (verifica duplicata antes) */
        if (atual->pista[0] != '\0') {
            if (!buscarPista(*raizPistas, atual->pista)) {
                *raizPistas = inserirPista(*raizPistas, atual->pista);
                printf("Você encontrou uma pista: \"%s\"  (adicionada ao inventário)\n", atual->pista);
            } else {
                printf("Pista já coletada anteriormente: \"%s\"\n", atual->pista);
            }
        } else {
            printf("Nenhuma pista nesta sala.\n");
        }

        printf("Escolha um caminho: (e) esquerda, (d) direita, (s) sair\n");
        printf("-> ");
        if (scanf(" %c", &opcao) != 1) {
            /* entrada inválida: limpa stdin e continua */
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }

        if (opcao == 'e') {
            if (atual->esq != NULL) {
                atual = atual->esq;
            } else {
                printf("Não existe caminho à esquerda!\n");
            }
        } else if (opcao == 'd') {
            if (atual->dir != NULL) {
                atual = atual->dir;
            } else {
                printf("Não existe caminho à direita!\n");
            }
        } else if (opcao == 's') {
            printf("Encerrando exploração...\n");
            return;
        } else {
            printf("Opção inválida! Use 'e', 'd' ou 's'.\n");
        }
    }

    /* se saiu do loop porque atual == NULL, significa que alcançou um ponteiro nulo
       (normalmente não acontece se respeitamos as verificações), mas apenas finalizamos. */
}

/* -------------------------
   main: monta o mapa (fixo) e inicia exploração
   ------------------------- */
int main(void) {
  
    Sala *hall = criarSala("Hall de Entrada", "bilhete com parte do nome do suspeito");
    hall->esq = criarSala("Sala de Estar", "luva com manchas");
    hall->dir = criarSala("Cozinha", "marca de barro próximo à porta");

    hall->esq->esq = criarSala("Biblioteca", "nota rasgada com endereço");
    hall->esq->dir = criarSala("Jardim", "pegada de bota");
    hall->dir->dir = criarSala("Despensa", "chave oxidada");

    PistaNode *raizPistas = NULL;

    explorarSalasComPistas(hall, &raizPistas);

    printf("\n--- Pistas coletadas (ordem alfabética) ---\n");
    if (raizPistas == NULL) {
        printf("Nenhuma pista coletada.\n");
    } else {
        exibirPistas(raizPistas);
    }

    /* liberar memória antes de encerrar */
    liberarPistas(raizPistas);
    liberarSalas(hall);

    return 0;
}
