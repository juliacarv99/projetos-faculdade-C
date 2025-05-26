#include <stdio.h>

int main() {
        // Movimento da Torre (5 casas para a direita) usando FOR
        printf("Movimento da Torre:\n");
        for (int i = 1; i <= 5; i++) {
            printf("Direita\n");
        }
    
        // Movimento do Bispo (5 casas na diagonal para cima e à direita) usando WHILE
        printf("\nMovimento do Bispo:\n");
        int j = 1;
        while (j <= 5) {
            printf("Cima Direita\n");
            j++;
        }
    
        // Movimento da Rainha (8 casas para a esquerda) usando DO-WHILE
        printf("\nMovimento da Rainha:\n");
        int k = 1;
        do {
            printf("Esquerda\n");
            k++;
        } while (k <= 8);
            // Movimento do Cavalo: 2 para baixo e 1 para a esquerda (forma de "L")
    printf("\nMovimento do Cavalo:\n");

    const int casasBaixo = 2;
    const int casasEsquerda = 1;

    // Loop externo com for para as duas casas para baixo
    for (int m = 1; m <= casasBaixo; m++) {
        printf("Baixo\n");

        // Loop interno do-while apenas para demonstrar o uso aninhado
        // Aqui ele roda uma única vez quando m == casasBaixo
        if (m == casasBaixo) {
            int n = 0;
            do {
                printf("Esquerda\n");
                n++;
            } while (n < casasEsquerda);
        }
    }

    return 0;
}