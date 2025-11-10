#include <stdio.h>
#include <string.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    struct Territorio territorios[5]; // Vetor para armazenar 5 territórios
    int i;

    printf("=== Cadastro de Territórios ===\n");

    // Entrada dos dados dos 5 territórios
    for (i = 0; i < 5; i++) {
        printf("\n--- Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %29[^\n]", territorios[i].nome); // lê string com espaços

        printf("Digite a cor do exército: ");
        scanf(" %9s", territorios[i].cor); // lê string sem espaços

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n=== Dados dos Territórios Cadastrados ===\n");
    for (i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    printf("\nCadastro concluído com sucesso!\n");

    return 0;
}
