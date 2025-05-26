#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para posicionar um navio horizontalmente
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int colunaInicial) {
    if (colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0; // Fora do limite do tabuleiro
    }

    // Verifica sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][colunaInicial + i] != AGUA) {
            return 0; // Já tem outro navio aqui
        }
    }

    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][colunaInicial + i] = NAVIO;
    }

    return 1; // Sucesso
}

// Função para posicionar um navio verticalmente
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int coluna) {
    if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0; // Fora do limite do tabuleiro
    }

    // Verifica sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linhaInicial + i][coluna] != AGUA) {
            return 0; // Já tem outro navio aqui
        }
    }

    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaInicial + i][coluna] = NAVIO;
    }

    return 1;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função principal
int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro (0)
    inicializarTabuleiro(tabuleiro);

    // Coordenadas dos navios
    int linhaHorizontal = 2;
    int colunaHorizontal = 4;

    int linhaVertical = 5;
    int colunaVertical = 7;

    // Posiciona navios e valida
    if (!posicionarNavioHorizontal(tabuleiro, linhaHorizontal, colunaHorizontal)) {
        printf("Erro ao posicionar navio horizontal.\n");
    }

    if (!posicionarNavioVertical(tabuleiro, linhaVertical, colunaVertical)) {
        printf("Erro ao posicionar navio vertical.\n");
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
