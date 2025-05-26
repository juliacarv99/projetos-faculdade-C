#include <stdio.h>

// Constantes para o número de movimentos
#define MOVIMENTOS_TORRE 4
#define MOVIMENTOS_BISPO 4
#define MOVIMENTOS_RAINHA 8
#define MOVIMENTOS_CAVALO 1

// Função recursiva para mover a Torre
void moverTorre(int casas) {
    if (casas <= 0) return; // Caso base
    
    printf("Direita\n");
    moverTorre(casas - 1); // Chamada recursiva
}

// Função recursiva para mover o Bispo (diagonal superior direita)
void moverBispo(int casas) {
    if (casas <= 0) return; // Caso base
    
    printf("Cima\n");
    printf("Direita\n");
    moverBispo(casas - 1); // Chamada recursiva
}

// Função recursiva para mover a Rainha (combinação de Torre e Bispo)
void moverRainha(int casas) {
    if (casas <= 0) return; // Caso base
    
    printf("Direita\n");  // Movimento como Torre
    printf("Cima\n");     // Movimento como Bispo
    printf("Direita\n");  // Movimento como Bispo
    moverRainha(casas - 1); // Chamada recursiva
}

// Função para mover o Cavalo usando loops complexos
void moverCavalo() {
    // Movimento em L: 2 casas para cima e 1 para a direita
    for (int i = 1; i <= 2; i++) {
        if (i > 2) break; // Segurança extra
        
        for (int j = 1; j <= 1; j++) {
            if (i <= 2) {
                printf("Cima\n");
            } else {
                continue; // Nunca será executado neste caso
            }
        }
    }
    printf("Direita\n");
}

// Função adicional para mostrar o Bispo com loops aninhados
void bispoComLoopsAninhados() {
    // Loop externo para movimento vertical (cima)
    for (int vertical = 1; vertical <= 2; vertical++) {
        printf("Cima\n");
        
        // Loop interno para movimento horizontal (direita)
        for (int horizontal = 1; horizontal <= 2; horizontal++) {
            printf("Direita\n");
            break; // Apenas uma vez por loop vertical
        }
    }
}

int main() {
    printf("Movimento da Torre:\n");
    moverTorre(MOVIMENTOS_TORRE);
    
    printf("\nMovimento do Bispo (recursivo):\n");
    moverBispo(MOVIMENTOS_BISPO);
    
    printf("\nBispo com loops aninhados:\n");
    bispoComLoopsAninhados();
    
    printf("\nMovimento da Rainha:\n");
    moverRainha(MOVIMENTOS_RAINHA);
    
    printf("\nMovimento do Cavalo:\n");
    moverCavalo();
    
    return 0;
}