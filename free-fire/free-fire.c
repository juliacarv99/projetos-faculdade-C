
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define STR_LEN 128

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1..10
} Componente;

// Vetor de componentes e contador
Componente componentes[MAX_COMPONENTES];
int totalComponentes = 0;

typedef enum {
    NENHUMA,
    POR_NOME,
    POR_TIPO,
    POR_PRIORIDADE
} UltimaOrdenacao;

UltimaOrdenacao ultimaOrdenacao = NENHUMA;

void trim_newline(char *s) {
    size_t len = strlen(s);
    if (len == 0) return;
    if (s[len - 1] == '\n') s[len - 1] = '\0';
}

void ler_string_segura(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    trim_newline(buffer);
}

void trocarComponentes(Componente *a, Componente *b) {
    Componente tmp = *a;
    *a = *b;
    *b = tmp;
}

/* mostrarComponentes: exibe vetor formatado; se chaveIndex >=0 marca componente-chave */
void mostrarComponentes(Componente arr[], int n, int chaveIndex) {
    if (n == 0) {
        printf("\n[Nenhum componente cadastrado]\n");
        return;
    }
    printf("\n--- Componentes (total: %d) ---\n", n);
    printf("%-3s | %-25s | %-12s | %-9s\n", "Id", "Nome", "Tipo", "Prioridade");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d | %-25s | %-12s | %-9d", i, arr[i].nome, arr[i].tipo, arr[i].prioridade);
        if (i == chaveIndex) printf("  <-- COMPONENTE-CHAVE");
        printf("\n");
    }
    printf("---------------------------------------------------------------\n");
}

void bubbleSortPorNome(Componente arr[], int n, long *comparacoes, double *tempo) {
    clock_t inicio = clock();
    long comps = 0;

    if (n <= 1) {
        *comparacoes = 0;
        *tempo = 0.0;
        ultimaOrdenacao = POR_NOME;
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            comps++;
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                trocarComponentes(&arr[j], &arr[j + 1]);
                trocou = 1;
            }
        }
        if (!trocou) break;
    }

    clock_t fim = clock();
    *comparacoes = comps;
    *tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    ultimaOrdenacao = POR_NOME;
}

/* insertionSortPorTipo: ordena por tipo (strcmp). Se tipos iguais, opcionalmente ordenar por nome. */
void insertionSortPorTipo(Componente arr[], int n, long *comparacoes, double *tempo) {
    clock_t inicio = clock();
    long comps = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = arr[i];
        int j = i - 1;
        // Move elementos maiores para a direita
        while (j >= 0) {
            comps++;
            int cmpTipo = strcmp(arr[j].tipo, chave.tipo);
            if (cmpTipo > 0) {
                arr[j + 1] = arr[j];
                j--;
            } else if (cmpTipo == 0) {
                // desempate por nome para estabilidade relativa
                comps++;
                if (strcmp(arr[j].nome, chave.nome) > 0) {
                    arr[j + 1] = arr[j];
                    j--;
                } else break;
            } else break;
        }
        arr[j + 1] = chave;
    }

    clock_t fim = clock();
    *comparacoes = comps;
    *tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    ultimaOrdenacao = POR_TIPO;
}

void selectionSortPrioridade(Componente arr[], int n, long *comparacoes, double *tempo) {
    clock_t inicio = clock();
    long comps = 0;

    for (int i = 0; i < n - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < n; j++) {
            comps++;
            if (arr[j].prioridade < arr[idxMin].prioridade) {
                idxMin = j;
            }
        }
        if (idxMin != i) trocarComponentes(&arr[i], &arr[idxMin]);
    }

    clock_t fim = clock();
    *comparacoes = comps;
    *tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    ultimaOrdenacao = POR_PRIORIDADE;
}

typedef void (*AlgoritmoOrdenacao)(Componente[], int, long*, double*);

void medirTempo(AlgoritmoOrdenacao algoritmo, Componente arr[], int n, long *comparacoes, double *tempo) {
    algoritmo(arr, n, comparacoes, tempo);
}

int buscaBinariaPorNome(Componente arr[], int n, const char target[], long *comparacoes) {
    if (n == 0) {
        *comparacoes = 0;
        return -1;
    }

    int inicio = 0, fim = n - 1;
    long comps = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        comps++;
        int cmp = strcmp(target, arr[meio].nome);
        if (cmp == 0) {
            *comparacoes = comps;
            return meio;
        } else if (cmp > 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    *comparacoes = comps;
    return -1;
}
void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\n[ERRO] Capacidade máxima atingida (%d componentes).\n", MAX_COMPONENTES);
        return;
    }

    char buffer[STR_LEN];
    Componente c;

    printf("\n-- Cadastro de Componente --\n");
    printf("Nome: ");
    ler_string_segura(buffer, STR_LEN);
    while (strlen(buffer) == 0) {
        printf("Nome não pode ser vazio. Digite novamente: ");
        ler_string_segura(buffer, STR_LEN);
    }
    strncpy(c.nome, buffer, sizeof(c.nome));
    c.nome[sizeof(c.nome)-1] = '\0';

    printf("Tipo (ex: controle, suporte, propulsao): ");
    ler_string_segura(buffer, STR_LEN);
    while (strlen(buffer) == 0) {
        printf("Tipo não pode ser vazio. Digite novamente: ");
        ler_string_segura(buffer, STR_LEN);
    }
    strncpy(c.tipo, buffer, sizeof(c.tipo));
    c.tipo[sizeof(c.tipo)-1] = '\0';

    printf("Prioridade (1-10, 1 = mais crítico): ");
    ler_string_segura(buffer, STR_LEN);
    int p = atoi(buffer);
    while (p < 1 || p > 10) {
        printf("Prioridade inválida. Informe valor entre 1 e 10: ");
        ler_string_segura(buffer, STR_LEN);
        p = atoi(buffer);
    }
    c.prioridade = p;

    componentes[totalComponentes++] = c;
    ultimaOrdenacao = NENHUMA;
    printf("\n[OK] Componente '%s' cadastrado com sucesso.\n", c.nome);
}
void removerComponentePorNome() {
    if (totalComponentes == 0) {
        printf("\n[INFO] Nenhum componente para remover.\n");
        return;
    }

    char buffer[STR_LEN];
    printf("\nDigite o nome do componente a remover: ");
    ler_string_segura(buffer, STR_LEN);

    int idx = -1;
    for (int i = 0; i < totalComponentes; i++) {
        if (strcmp(componentes[i].nome, buffer) == 0) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("\n[ERRO] Componente não encontrado.\n");
        return;
    }

    for (int j = idx; j < totalComponentes - 1; j++) {
        componentes[j] = componentes[j + 1];
    }
    totalComponentes--;
    ultimaOrdenacao = NENHUMA;
    printf("\n[OK] Componente removido.\n");
}
void buscarSequencialPorNome() {
    if (totalComponentes == 0) {
        printf("\n[INFO] Nenhum componente cadastrado.\n");
        return;
    }
    char buffer[STR_LEN];
    printf("\nDigite o nome a buscar (busca sequencial): ");
    ler_string_segura(buffer, STR_LEN);

    long comps = 0;
    for (int i = 0; i < totalComponentes; i++) {
        comps++;
        if (strcmp(componentes[i].nome, buffer) == 0) {
            printf("\n[OK] Encontrado no índice %d:\n", i);
            printf("Nome: %s | Tipo: %s | Prioridade: %d\n", componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
            printf("Comparações na busca sequencial: %ld\n", comps);
            return;
        }
    }
    printf("\n[INFO] Componente não encontrado.\n");
    printf("Comparações na busca sequencial: %ld\n", comps);
}

void executarOrdenacao() {
    if (totalComponentes == 0) {
        printf("\n[INFO] Não há componentes para ordenar.\n");
        return;
    }

    printf("\nEscolha o algoritmo de ordenação:\n");
    printf("1 - Bubble Sort por NOME (strings)\n");
    printf("2 - Insertion Sort por TIPO (strings)\n");
    printf("3 - Selection Sort por PRIORIDADE (inteiro)\n");
    printf("Opção: ");
    char buf[STR_LEN];
    ler_string_segura(buf, STR_LEN);
    int op = atoi(buf);

    long comps = 0;
    double tempo = 0.0;

    switch (op) {
        case 1:
            printf("\nExecutando Bubble Sort por NOME...\n");
            medirTempo(bubbleSortPorNome, componentes, totalComponentes, &comps, &tempo);
            printf("[RESULTADO] Bubble Sort finalizado.\n");
            printf("Comparações: %ld | Tempo: %.6f s\n", comps, tempo);
            mostrarComponentes(componentes, totalComponentes, -1);
            break;
        case 2:
            printf("\nExecutando Insertion Sort por TIPO...\n");
            medirTempo(insertionSortPorTipo, componentes, totalComponentes, &comps, &tempo);
            printf("[RESULTADO] Insertion Sort finalizado.\n");
            printf("Comparações: %ld | Tempo: %.6f s\n", comps, tempo);
            mostrarComponentes(componentes, totalComponentes, -1);
            break;
        case 3:
            printf("\nExecutando Selection Sort por PRIORIDADE...\n");
            medirTempo(selectionSortPrioridade, componentes, totalComponentes, &comps, &tempo);
            printf("[RESULTADO] Selection Sort finalizado.\n");
            printf("Comparações: %ld | Tempo: %.6f s\n", comps, tempo);
            mostrarComponentes(componentes, totalComponentes, -1);
            break;
        default:
            printf("\nOpção inválida.\n");
            break;
    }
}

void buscaBinariaInterativa() {
    if (totalComponentes == 0) {
        printf("\n[INFO] Nenhum componente cadastrado.\n");
        return;
    }

    if (ultimaOrdenacao != POR_NOME) {
        printf("\n[Atenção] A busca binária requer que o vetor esteja ordenado por NOME.\n");
        printf("Deseja ordenar por NOME agora com Bubble Sort? (s/n): ");
        char buf[STR_LEN];
        ler_string_segura(buf, STR_LEN);
        if (buf[0] == 's' || buf[0] == 'S') {
            long compsTmp = 0; double tempoTmp = 0.0;
            medirTempo(bubbleSortPorNome, componentes, totalComponentes, &compsTmp, &tempoTmp);
            printf("[INFO] Ordenado por nome. Comparações: %ld | Tempo: %.6f s\n", compsTmp, tempoTmp);
        } else {
            printf("[INFO] Operação de busca binária cancelada.\n");
            return;
        }
    }

    char chave[STR_LEN];
    printf("\nDigite o NOME do componente-chave para busca binária: ");
    ler_string_segura(chave, STR_LEN);

    long compsBin = 0;
    int idx = buscaBinariaPorNome(componentes, totalComponentes, chave, &compsBin);

    if (idx >= 0) {
        printf("\n[OK] Componente encontrado no índice %d.\n", idx);
        mostrarComponentes(componentes, totalComponentes, idx);
    } else {
        printf("\n[INFO] Componente não encontrado pela busca binária.\n");
    }
    printf("Comparações na busca binária: %ld\n", compsBin);
}

/* menu principal */
void menuPrincipal() {
    int sair = 0;
    char buf[STR_LEN];

    while (!sair) {
        printf("\n===== MÓDULO: MONTAGEM DA TORRE DE RESGATE =====\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Remover componente por nome\n");
        printf("3 - Listar componentes\n");
        printf("4 - Ordenar / Avaliar algoritmos\n");
        printf("5 - Buscar componente (Sequencial)\n");
        printf("6 - Buscar componente (Binária) [exige ordenação por nome]\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        ler_string_segura(buf, STR_LEN);
        int opc = atoi(buf);

        switch (opc) {
            case 1: cadastrarComponente(); break;
            case 2: removerComponentePorNome(); break;
            case 3: mostrarComponentes(componentes, totalComponentes, -1); break;
            case 4: executarOrdenacao(); break;
            case 5: buscarSequencialPorNome(); break;
            case 6: buscaBinariaInterativa(); break;
            case 0: sair = 1; break;
            default: printf("\nOpção inválida.\n"); break;
        }
    }
}

int main() {
    printf("=== Módulo Avançado: Priorização e Montagem da Torre ===\n");
    printf("Max componentes = %d\n", MAX_COMPONENTES);
    menuPrincipal();
    printf("\nEncerrando sistema. Boa sorte na fuga!\n");
    return 0;
}
