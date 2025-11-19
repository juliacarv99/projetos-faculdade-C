#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5   // tamanho fixo da fila

typedef struct {
    char nome;   // tipo da peça: 'I', 'O', 'T', 'L'
    int id;      // identificador único
} Peca;

Peca fila[TAMANHO_FILA];
int inicio = 0;   // posição do primeiro elemento (dequeue)
int fim = 0;      // posição onde a próxima peça será inserida (enqueue)
int quantidade = 0; // quantidade de elementos na fila
int contadorID = 0; // gera IDs únicos

// ---------- FUNÇÃO PARA GERAR PEÇA NOVA ----------
Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4]; // escolhe um tipo aleatório
    nova.id = contadorID++;        // gera ID único
    return nova;
}
void enqueue() {
    if (quantidade == TAMANHO_FILA) {
        printf("\n❌ A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAMANHO_FILA;
    quantidade++;

    printf("\n✅ Nova peça inserida com sucesso!\n");
}

void dequeue() {
    if (quantidade == 0) {
        printf("\n❌ A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca jogada = fila[inicio];
    inicio = (inicio + 1) % TAMANHO_FILA;
    quantidade--;

    printf("\n🎮 Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
}

void exibirFila() {
    printf("\n===== Fila de peças =====\n");

    if (quantidade == 0) {
        printf("(vazia)\n");
        return;
    }

    int i, idx;
    for (i = 0; i < quantidade; i++) {
        idx = (inicio + i) % TAMANHO_FILA;
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
    }
    printf("\n==========================\n");
}

int main() {
    srand(time(NULL));

    // Inicializa fila com 5 peças
    printf("Inicializando fila com 5 peças...\n");
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        exibirFila();

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("-> Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;
            case 2:
                enqueue();
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\n❌ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
