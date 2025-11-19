#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

Peca fila[TAM_FILA];
Peca pilha[TAM_PILHA];

int inicio = 0;
int fim = 0;
int quantidade = 0;

int topo = -1;
int contadorID = 0;

Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = contadorID++;
    return p;
}

void enqueueAuto() {
    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAM_FILA;
}

void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        enqueueAuto();
        quantidade++;
    }
}

void exibirEstruturas() {
    int i;
    printf("\nFila: ");
    for (i = 0; i < quantidade; i++) {
        int idx = (inicio + i) % TAM_FILA;
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
    }

    printf("\nPilha (Topo -> Base): ");
    if (topo == -1)
        printf("(vazia)");
    else
        for (i = topo; i >= 0; i--)
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    
    printf("\n");
}

void jogarPeca() {
    if (quantidade == 0) {
        printf("Fila vazia.\n");
        return;
    }

    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;

    enqueueAuto();
    quantidade++;
}

void reservarPeca() {
    if (quantidade == 0) {
        printf("Fila vazia.\n");
        return;
    }
    if (topo == TAM_PILHA - 1) {
        printf("Pilha cheia.\n");
        return;
    }

    pilha[++topo] = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;

    enqueueAuto();
    quantidade++;
}

void usarReservada() {
    if (topo == -1) {
        printf("Pilha vazia.\n");
        return;
    }

    topo--;
}

int main() {
    srand((unsigned int)time(NULL));
    inicializarFila();

    int opcao;

    do {
        exibirEstruturas();

        printf("\n1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: jogarPeca(); break;
            case 2: reservarPeca(); break;
            case 3: usarReservada(); break;
            case 0: break;
            default: printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
