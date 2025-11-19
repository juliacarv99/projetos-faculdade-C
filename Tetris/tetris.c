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

void exibir() {
    printf("\nFila: ");
    for (int i = 0; i < quantidade; i++) {
        int idx = (inicio + i) % TAM_FILA;
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
    }

    printf("\nPilha (Topo -> Base): ");
    if (topo == -1)
        printf("(vazia)");
    else
        for (int i = topo; i >= 0; i--)
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);

    printf("\n");
}

void jogarPeca() {
    if (quantidade == 0) return;
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;
    enqueueAuto();
    quantidade++;
}

void reservarPeca() {
    if (quantidade == 0) return;
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

void usarPecaReservada() {
    if (topo == -1) {
        printf("Pilha vazia.\n");
        return;
    }
    topo--;
}

void trocarSimples() {
    if (topo == -1) {
        printf("Pilha vazia.\n");
        return;
    }

    int idx = inicio;
    Peca temp = fila[idx];
    fila[idx] = pilha[topo];
    pilha[topo] = temp;
}

void trocarMultiplas() {
    if (quantidade < 3 || topo < 2) {
        printf("Ambas as estruturas devem ter pelo menos 3 peças.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idxFila = (inicio + i) % TAM_FILA;
        Peca temp = fila[idxFila];
        fila[idxFila] = pilha[topo - i];
        pilha[topo - i] = temp;
    }
}

int main() {
    srand((unsigned int)time(NULL));

    inicializarFila();

    int op;

    do {
        exibir();

        printf("\n1 - Jogar peça da fila\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar peça da fila com topo da pilha\n");
        printf("5 - Trocar 3 peças da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1: jogarPeca(); break;
            case 2: reservarPeca(); break;
            case 3: usarPecaReservada(); break;
            case 4: trocarSimples(); break;
            case 5: trocarMultiplas(); break;
            case 0: break;
            default: printf("Opção inválida.\n");
        }

    } while (op != 0);

    return 0;
}
