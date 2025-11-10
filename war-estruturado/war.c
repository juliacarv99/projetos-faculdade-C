#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios dinamicamente
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %9s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibir os dados dos territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== Dados dos Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exército: %s\n", mapa[i].cor);
        printf("Quantidade de tropas: %d\n", mapa[i].tropas);
    }
}

// Função ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- Simulação de Ataque ---\n");
    printf("%s (%s) está atacando %s (%s)!\n", 
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Gera valores aleatórios de 1 a 6 simulando dados 
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Resultado 
    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu a batalha!\n");

        // Transfere a cor e metade das tropas ao defensor
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

        printf("%s agora pertence ao exército %s!\n", defensor->nome, defensor->cor);
    } else {
        printf("O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Função para liberar memória 
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}

int main() {
    srand(time(NULL)); // aleatoriedade dos dados

    int n;
    printf("Digite o número total de territórios: ");
    scanf("%d", &n);

    // Alocação dinâmica dos territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("\n=== Cadastro de Territórios ===\n");
    cadastrarTerritorios(mapa, n);

    printf("\n=== Territórios Cadastrados ===\n");
    exibirTerritorios(mapa, n);

    // Simulação de ataque
    int atacante, defensor;
    printf("\n=== Fase de Ataque ===\n");
    printf("Escolha o número do território atacante (1 a %d): ", n);
    scanf("%d", &atacante);
    printf("Escolha o número do território defensor (1 a %d): ", n);
    scanf("%d", &defensor);

    // Validação básica
    if (atacante < 1 || atacante > n || defensor < 1 || defensor > n || atacante == defensor) {
        printf("\nSeleção inválida de territórios!\n");
    } else if (strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0) {
        printf("\nVocê não pode atacar um território do mesmo exército!\n");
    } else {
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
    }

    printf("\n=== Estado Final dos Territórios ===\n");
    exibirTerritorios(mapa, n);

    liberarMemoria(mapa);
    printf("\nPrograma encerrado com sucesso!\n");

    return 0;
}

