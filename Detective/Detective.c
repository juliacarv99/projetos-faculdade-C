#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_MAX 64
#define PISTA_MAX 128
#define HASH_SIZE 53   /* primo razoável para poucas pistas */

/* ----------------------------
   Estruturas
   ---------------------------- */

/* Sala: nó da árvore binária (mapa da mansão) */
typedef struct Sala {
    char nome[NOME_MAX];
    char pista[PISTA_MAX]; /* string vazia se não houver pista */
    struct Sala *esq;
    struct Sala *dir;
} Sala;

/* Nó da BST para pistas coletadas */
typedef struct PistaNode {
    char pista[PISTA_MAX];
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;

/* Entrada da tabela hash: mapeia pista -> suspeito */
typedef struct HashEntry {
    char pista[PISTA_MAX];
    char suspeito[NOME_MAX];
    struct HashEntry *prox;
} HashEntry;

/* ----------------------------
   Protótipos (documentados abaixo)
   ---------------------------- */

/* criarSala() – cria dinamicamente um cômodo com nome e pista (pista pode ser "") */
Sala* criarSala(const char *nome, const char *pista);

/* explorarSalas() – navega pela árvore e ativa o sistema de pistas */
void explorarSalas(Sala *inicio, PistaNode **raizPistas, HashEntry *tabela[]);

/* inserirPista() / buscarPista() – insere/consulta pista na BST (evita duplicatas) */
PistaNode* inserirPista(PistaNode *raiz, const char *pista);
int buscarPista(PistaNode *raiz, const char *pista);

/* exibirPistas() – imprime a BST em ordem alfabética */
void exibirPistas(PistaNode *raiz);

/* inserirNaHash() – insere associação pista->suspeito na tabela hash */
void inserirNaHash(HashEntry *tabela[], const char *pista, const char *suspeito);

/* encontrarSuspeito() – retorna o suspeito associado a uma pista (ou NULL se não achar) */
const char* encontrarSuspeito(HashEntry *tabela[], const char *pista);

/* verificarSuspeitoFinal() – conta quantas pistas coletadas apontam para o suspeito acusado */
int verificarSuspeitoFinal(PistaNode *raizPistas, HashEntry *tabela[], const char *acusado);

/* Funções utilitárias: liberar memória */
void liberarPistas(PistaNode *raiz);
void liberarSalas(Sala *raiz);
void liberarHash(HashEntry *tabela[]);

/* ----------------------------
   Implementação
   ---------------------------- */

/* Função de hash simples (djb2 mod HASH_SIZE) */
static unsigned int hash_str(const char *s) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*s++))
        hash = ((hash << 5) + hash) + c;
    return (unsigned int)(hash % HASH_SIZE);
}

/* criarSala() – cria dinamicamente um cômodo com nome e pista */
Sala* criarSala(const char *nome, const char *pista) {
    Sala *s = (Sala*) malloc(sizeof(Sala));
    if (!s) {
        fprintf(stderr, "Erro: falha ao alocar Sala\n");
        exit(EXIT_FAILURE);
    }
    strncpy(s->nome, nome, NOME_MAX-1);
    s->nome[NOME_MAX-1] = '\0';
    if (pista && pista[0] != '\0') {
        strncpy(s->pista, pista, PISTA_MAX-1);
        s->pista[PISTA_MAX-1] = '\0';
    } else {
        s->pista[0] = '\0';
    }
    s->esq = s->dir = NULL;
    return s;
}

/* buscarPista(): retorna 1 se encontrada, 0 se não */
int buscarPista(PistaNode *raiz, const char *pista) {
    if (raiz == NULL) return 0;
    int cmp = strcmp(pista, raiz->pista);
    if (cmp == 0) return 1;
    if (cmp < 0) return buscarPista(raiz->esq, pista);
    return buscarPista(raiz->dir, pista);
}

/* inserirPista() – insere a pista na BST (mantém ordem e evita duplicatas) */
PistaNode* inserirPista(PistaNode *raiz, const char *pista) {
    if (raiz == NULL) {
        PistaNode *n = (PistaNode*) malloc(sizeof(PistaNode));
        if (!n) { fprintf(stderr, "Erro: falha ao alocar PistaNode\n"); exit(EXIT_FAILURE); }
        strncpy(n->pista, pista, PISTA_MAX-1);
        n->pista[PISTA_MAX-1] = '\0';
        n->esq = n->dir = NULL;
        return n;
    }
    int cmp = strcmp(pista, raiz->pista);
    if (cmp < 0) raiz->esq = inserirPista(raiz->esq, pista);
    else if (cmp > 0) raiz->dir = inserirPista(raiz->dir, pista);
    /* se igual, não insere duplicata */
    return raiz;
}

/* exibirPistas() – percurso in-order para imprimir em ordem alfabética */
void exibirPistas(PistaNode *raiz) {
    if (!raiz) return;
    exibirPistas(raiz->esq);
    printf(" - %s\n", raiz->pista);
    exibirPistas(raiz->dir);
}

/* inserirNaHash() – insere associação pista->suspeito (encadeamento) */
void inserirNaHash(HashEntry *tabela[], const char *pista, const char *suspeito) {
    unsigned int h = hash_str(pista);
    HashEntry *e = (HashEntry*) malloc(sizeof(HashEntry));
    if (!e) { fprintf(stderr, "Erro: falha ao alocar HashEntry\n"); exit(EXIT_FAILURE); }
    strncpy(e->pista, pista, PISTA_MAX-1);
    e->pista[PISTA_MAX-1] = '\0';
    strncpy(e->suspeito, suspeito, NOME_MAX-1);
    e->suspeito[NOME_MAX-1] = '\0';
    e->prox = tabela[h];
    tabela[h] = e;
}

/* encontrarSuspeito() – retorna ponteiro para nome do suspeito ou NULL */
const char* encontrarSuspeito(HashEntry *tabela[], const char *pista) {
    unsigned int h = hash_str(pista);
    HashEntry *at = tabela[h];
    while (at) {
        if (strcmp(at->pista, pista) == 0) return at->suspeito;
        at = at->prox;
    }
    return NULL;
}

/* verificarSuspeitoFinal() – conta quantas pistas apontam para 'acusado' */
int verificarSuspeitoFinal(PistaNode *raizPistas, HashEntry *tabela[], const char *acusado) {
    if (!raizPistas) return 0;
    int count = 0;
    /* percorre a BST e incrementa quando a pista aponta para acusado */
    /* usaremos uma pilha recursiva simples */
    if (raizPistas->esq) count += verificarSuspeitoFinal(raizPistas->esq, tabela, acusado);
    const char *s = encontrarSuspeito(tabela, raizPistas->pista);
    if (s && strcmp(s, acusado) == 0) count++;
    if (raizPistas->dir) count += verificarSuspeitoFinal(raizPistas->dir, tabela, acusado);
    return count;
}

/* explorarSalas() – navega e coleta pistas automaticamente */
void explorarSalas(Sala *inicio, PistaNode **raizPistas, HashEntry *tabela[]) {
    if (!inicio) return;
    Sala *at = inicio;
    char opc;
    printf("=== Início da exploração ===\n");
    while (1) {
        printf("\nVocê está em: %s\n", at->nome);
        if (at->pista[0] != '\0') {
            if (!buscarPista(*raizPistas, at->pista)) {
                *raizPistas = inserirPista(*raizPistas, at->pista);
                printf("  -> Pista coletada: \"%s\"\n", at->pista);
                const char *s = encontrarSuspeito(tabela, at->pista);
                if (s) printf("     (esta pista está associada ao suspeito: %s)\n", s);
            } else {
                printf("  -> Pista nesta sala já coletada anteriormente: \"%s\"\n", at->pista);
            }
        } else {
            printf("  -> Nenhuma pista nesta sala.\n");
        }

        /* opções: esquerda (e), direita (d), sair (s) */
        printf("Escolha: (e) esquerda, (d) direita, (s) sair\n-> ");
        if (scanf(" %c", &opc) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrada inválida.\n");
            continue;
        }
        if (opc == 'e') {
            if (at->esq) at = at->esq;
            else printf("Não há caminho à esquerda.\n");
        } else if (opc == 'd') {
            if (at->dir) at = at->dir;
            else printf("Não há caminho à direita.\n");
        } else if (opc == 's') {
            printf("Exploração encerrada pelo jogador.\n");
            return;
        } else {
            printf("Opção inválida. Use 'e', 'd' ou 's'.\n");
        }
    }
}

/* liberarPistas() – libera memória da BST de pistas */
void liberarPistas(PistaNode *raiz) {
    if (!raiz) return;
    liberarPistas(raiz->esq);
    liberarPistas(raiz->dir);
    free(raiz);
}

/* liberarSalas() – libera memória da árvore de salas */
void liberarSalas(Sala *raiz) {
    if (!raiz) return;
    liberarSalas(raiz->esq);
    liberarSalas(raiz->dir);
    free(raiz);
}

/* liberarHash() – libera toda a tabela hash */
void liberarHash(HashEntry *tabela[]) {
    for (int i = 0; i < HASH_SIZE; ++i) {
        HashEntry *at = tabela[i];
        while (at) {
            HashEntry *next = at->prox;
            free(at);
            at = next;
        }
        tabela[i] = NULL;
    }
}

/* ----------------------------
   main: monta mapa, tabela hash, e inicia exploração/julgamento
   ---------------------------- */
int main(void) {
    /* Montagem fixa do mapa (árvore de salas).
       Cada sala tem um nome único e possivelmente uma pista.
       As pistas escolhidas abaixo serão as chaves na tabela hash.
    */
    Sala *hall = criarSala("Hall de Entrada", "bilhete: parte do nome");
    hall->esq = criarSala("Sala de Estar", "luva com manchas");
    hall->dir = criarSala("Cozinha", "pegada de barro");

    hall->esq->esq = criarSala("Biblioteca", "nota rasgada com endereço");
    hall->esq->dir = criarSala("Jardim", "pegada de bota");
    hall->dir->dir = criarSala("Despensa", "chave oxidada");

    /* Inicializa tabela hash vazia */
    HashEntry *tabela[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; ++i) tabela[i] = NULL;

    /* Insere associações pista -> suspeito (fixas) */
    inserirNaHash(tabela, "bilhete: parte do nome", "Sr. Verde");
    inserirNaHash(tabela, "luva com manchas", "Sr. Verde");
    inserirNaHash(tabela, "pegada de barro", "Sra. Rosa");
    inserirNaHash(tabela, "nota rasgada com endereço", "Sra. Rosa");
    inserirNaHash(tabela, "pegada de bota", "Sr. Azul");
    inserirNaHash(tabela, "chave oxidada", "Sr. Azul");
    /* Note: várias pistas podem apontar para mesmo suspeito. */

    PistaNode *raizPistas = NULL;

    /* Exploração interativa */
    explorarSalas(hall, &raizPistas, tabela);

    /* Fase final: mostra pistas coletadas e solicita acusação */
    printf("\n=== Pistas coletadas (ordem alfabética) ===\n");
    if (raizPistas == NULL) {
        printf("Nenhuma pista coletada.\n");
    } else {
        exibirPistas(raizPistas);
    }

    /* Solicitar acusação */
    char acusado[NOME_MAX];
    printf("\nQuem você acusa? Digite o nome do suspeito: ");
    /* Limpa stdin antes (por segurança) */
    int c; while ((c = getchar()) != '\n' && c != EOF);
    if (fgets(acusado, NOME_MAX, stdin) == NULL) {
        printf("Entrada inválida. Encerrando.\n");
    } else {
        /* remove newline */
        size_t L = strlen(acusado);
        if (L > 0 && acusado[L-1] == '\n') acusado[L-1] = '\0';
        if (strlen(acusado) == 0) {
            printf("Nenhum nome fornecido. Encerrando.\n");
        } else {
            int cont = verificarSuspeitoFinal(raizPistas, tabela, acusado);
            printf("\nVocê acusou: %s\n", acusado);
            printf("Pistas que apontam para %s: %d\n", acusado, cont);
            if (cont >= 2) {
                printf("Resultado: Há evidências suficientes. Acusação válida!\n");
            } else {
                printf("Resultado: Evidências insuficientes. Acusação fraca.\n");
            }
        }
    }

    /* Liberar memória */
    liberarPistas(raizPistas);
    liberarHash(tabela);
    liberarSalas(hall);

    return 0;
}
