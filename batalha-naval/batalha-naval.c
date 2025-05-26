#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AGUA 0

// Função para inicializar o tabuleiro com água (zeros)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se a posição está dentro do tabuleiro
int estaDentroTabuleiro(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para verificar se o espaço está livre para posicionar o navio
int espacoLivre(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhas[], int colunas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (!estaDentroTabuleiro(linhas[i], colunas[i])) {
            return 0; // Fora do tabuleiro
        }
        if (tabuleiro[linhas[i]][colunas[i]] == NAVIO) {
            return 0; // Espaço ocupado
        }
    }
    return 1; // Espaço livre
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhas[], int colunas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[linhas[i]][colunas[i]] = NAVIO;
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Navios: tamanho fixo 3
    // Definindo coordenadas para os navios (linhas e colunas)

    // Navio horizontal: linha 2, colunas 1 a 3
    int navioH_linhas[TAMANHO_NAVIO] = {2, 2, 2};
    int navioH_colunas[TAMANHO_NAVIO] = {1, 2, 3};

    // Navio vertical: col 5, linhas 5 a 7
    int navioV_linhas[TAMANHO_NAVIO] = {5, 6, 7};
    int navioV_colunas[TAMANHO_NAVIO] = {5, 5, 5};

    // Navio diagonal principal: começa na (0,0) diagonal para (2,2)
    int navioD1_linhas[TAMANHO_NAVIO] = {0, 1, 2};
    int navioD1_colunas[TAMANHO_NAVIO] = {0, 1, 2};

    // Navio diagonal secundária: começa na (7,2) diagonal para (9,4)
    int navioD2_linhas[TAMANHO_NAVIO] = {7, 8, 9};
    int navioD2_colunas[TAMANHO_NAVIO] = {2, 3, 4};

    // Verificar e posicionar cada navio, com validação simples
    if (espacoLivre(tabuleiro, navioH_linhas, navioH_colunas, TAMANHO_NAVIO)) {
        posicionarNavio(tabuleiro, navioH_linhas, navioH_colunas, TAMANHO_NAVIO);
    } else {
        printf("Não foi possível posicionar o navio horizontal.\n");
    }

    if (espacoLivre(tabuleiro, navioV_linhas, navioV_colunas, TAMANHO_NAVIO)) {
        posicionarNavio(tabuleiro, navioV_linhas, navioV_colunas, TAMANHO_NAVIO);
    } else {
        printf("Não foi possível posicionar o navio vertical.\n");
    }

    if (espacoLivre(tabuleiro, navioD1_linhas, navioD1_colunas, TAMANHO_NAVIO)) {
        posicionarNavio(tabuleiro, navioD1_linhas, navioD1_colunas, TAMANHO_NAVIO);
    } else {
        printf("Não foi possível posicionar o navio diagonal principal.\n");
    }

    if (espacoLivre(tabuleiro, navioD2_linhas, navioD2_colunas, TAMANHO_NAVIO)) {
        posicionarNavio(tabuleiro, navioD2_linhas, navioD2_colunas, TAMANHO_NAVIO);
    } else {
        printf("Não foi possível posicionar o navio diagonal secundária.\n");
    }

    // Exibir tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
