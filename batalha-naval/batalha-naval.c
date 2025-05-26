#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AGUA 0
#define AREA_HABILIDADE 5

// Tamanho fixo das matrizes de habilidades (matriz 5x5 para simplicidade)
#define TAMANHO_HABILIDADE 5

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

// Função para posicionar um navio no tabuleiro (linha e coluna são arrays com coordenadas)
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhas[], int colunas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (estaDentroTabuleiro(linhas[i], colunas[i])) {
            tabuleiro[linhas[i]][colunas[i]] = NAVIO;
        }
    }
}

// Cria a matriz da habilidade "Cone" (5x5), com cone apontando para baixo
void criarMatrizCone(int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    /*
     * Exemplo visual da matriz (1 = área afetada):
     * 0 0 1 0 0
     * 0 1 1 1 0
     * 1 1 1 1 1
     * 0 0 0 0 0
     * 0 0 0 0 0
     */
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == 0 && j == 2) {
                cone[i][j] = 1;
            } else if (i == 1 && (j >= 1 && j <= 3)) {
                cone[i][j] = 1;
            } else if (i == 2) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }
}

// Cria a matriz da habilidade "Cruz" (5x5), cruz no centro
void criarMatrizCruz(int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    /*
     * Visual:
     * 0 0 1 0 0
     * 0 0 1 0 0
     * 1 1 1 1 1
     * 0 0 1 0 0
     * 0 0 1 0 0
     */
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j == 2 || i == 2) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// Cria a matriz da habilidade "Octaedro" (5x5), forma losangular
void criarMatrizOctaedro(int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    /*
     * Visual:
     * 0 0 1 0 0
     * 0 1 1 1 0
     * 1 1 1 1 1
     * 0 1 1 1 0
     * 0 0 1 0 0
     */
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Usando condição para formar losango:
            int distLinha = (i <= 2) ? i : 4 - i;
            int minJ = 2 - distLinha;
            int maxJ = 2 + distLinha;

            if (j >= minJ && j <= maxJ) {
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
            }
        }
    }
}

// Função para sobrepor a matriz de habilidade ao tabuleiro no ponto de origem (linhaOrigem, colOrigem)
void aplicarHabilidadeNoTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linhaOrigem, int colOrigem) {
    int meio = TAMANHO_HABILIDADE / 2;  // centro da matriz de habilidade (ex: 2 para 5x5)

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTabuleiro = linhaOrigem - meio + i;
                int colTabuleiro = colOrigem - meio + j;

                // Verifica limites para não sair do tabuleiro
                if (estaDentroTabuleiro(linhaTabuleiro, colTabuleiro)) {
                    // Apenas marca a área se não for navio (pode sobrepor área já afetada)
                    if (tabuleiro[linhaTabuleiro][colTabuleiro] == AGUA) {
                        tabuleiro[linhaTabuleiro][colTabuleiro] = AREA_HABILIDADE;
                    }
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro com Navios e Áreas de Habilidade:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf("0 ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf("3 ");
            } else if (tabuleiro[i][j] == AREA_HABILIDADE) {
                printf("5 ");
            } else {
                printf("? "); // Caso inesperado
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Definir navios (exemplo simples horizontal e vertical)
    int navioH_linhas[TAMANHO_NAVIO] = {2, 2, 2};
    int navioH_colunas[TAMANHO_NAVIO] = {1, 2, 3};

    int navioV_linhas[TAMANHO_NAVIO] = {5, 6, 7};
    int navioV_colunas[TAMANHO_NAVIO] = {5, 5, 5};

    posicionarNavio(tabuleiro, navioH_linhas, navioH_colunas, TAMANHO_NAVIO);
    posicionarNavio(tabuleiro, navioV_linhas, navioV_colunas, TAMANHO_NAVIO);

    // Criar matrizes para habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Definir pontos de origem das habilidades no tabuleiro
    int origemConeLinha = 1, origemConeColuna = 2;
    int origemCruzLinha = 6, origemCruzColuna = 5;
    int origemOctaedroLinha = 8, origemOctaedroColuna = 2;

    // Aplicar as habilidades no tabuleiro
    aplicarHabilidadeNoTabuleiro(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicarHabilidadeNoTabuleiro(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicarHabilidadeNoTabuleiro(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
