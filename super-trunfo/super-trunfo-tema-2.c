#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    char estado [3], estado2 [3];
    char codigo [4], codigo2 [4];
    char cidade [70], cidade2 [70];
    int populacao, populacao2;
    int pontos, pontos2;
    float area, pib, area2, pib2;
    float densidade_populacional, densidade_populacional2;
    float pib_per_capita, pib_per_capita2, atributo1, atributo2;
    int escolha;
   

    //entrada e saida de dados carta 1
    printf("carta 1:\n");
     
    printf("\nestado: ");
    scanf("%s", estado);

    printf("código: ");
    scanf("%s", codigo);

    printf("nome da cidade: ");
    scanf(" %69[^\n]", cidade); 

    printf("população: ");
    scanf("%d", &populacao);

    printf("Área: ");
    scanf("%f", &area);

    printf("PIB: ");
    scanf("%f", &pib);

    printf("número de pontos turisticos: ");
    scanf("%d", &pontos);

     // Cálculos para a Carta 1
     densidade_populacional = populacao / area;
     pib_per_capita = pib / populacao;

    // Exibição dos dados da Carta 1
    printf("\nCarta 1\n");
    printf("Estado: %s\n", estado);
    printf("Código: %s\n", codigo);
    printf("Nome da Cidade: %s\n", cidade);
    printf("População: %d\n", populacao);
    printf("Área %.2f km²: \n", area);
    printf("PIB: %.2f\n", pib);
    printf("Número de Pontos Turísticos: %d\n", pontos);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade_populacional);
    printf("PIB per Capita: %.2f\n\n", pib_per_capita);


    //entrada e saida de dados carta 2
    
    printf("carta 2:\n");
    
    printf("estado: ");
    scanf("%s", estado2);

    printf("código: ");
    scanf("%s", codigo2);

    printf("nome da cidade: ");
    scanf(" %69[^\n]", cidade2); 

    printf("população: ");
    scanf("%d", &populacao2);

    printf("Área: ");
    scanf("%f", &area2);

    printf("PIB: ");
    scanf("%f", &pib2);

    printf("número de pontos turisticos: ");
    scanf("%d", &pontos2);

     // Cálculos para a Carta 2
     densidade_populacional2 = populacao2 / area2;
     pib_per_capita2 = pib2 / populacao2;

    // Exibição dos dados da Carta 2
    printf("\nCarta 2\n");
    printf("Estado: %s\n", estado2);
    printf("Código: %s\n", codigo2);
    printf("Nome da Cidade: %s\n", cidade2);
    printf("População: %d\n", populacao2); 
    printf("Área: %.2f km²\n", area2); 
    printf("PIB: %.2f\n", pib2);
    printf("Número de Pontos Turísticos: %d\n", pontos2);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade_populacional2);
    printf("PIB per Capita: %.2f\n\n", pib_per_capita2);
    
    // Menu interativo para escolher o atributo de comparação
    printf("Escolha o atributo para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Populacional\n");
    printf("6 - PIB per Capita\n");
    printf("Opção: ");
    scanf("%d", &escolha);

    // Comparação de atributos
    char n_atributo[50];

    switch (escolha) {
        case 1:
            atributo1 = populacao;
            atributo2 = populacao2;
            strcpy(n_atributo, "População");
            break;
        case 2:
            atributo1 = area;
            atributo2 = area2;
            strcpy(n_atributo, "Área");
            break;
        case 3:
            atributo1 = pib;
            atributo2 = pib2;
            strcpy(n_atributo, "PIB");
            break;
        case 4:
            atributo1 = pontos;
            atributo2 = pontos2;
            strcpy(n_atributo, "Pontos Turísticos");
            break;
        case 5:
            atributo1 = densidade_populacional;
            atributo2 = densidade_populacional2;
            strcpy(n_atributo, "Densidade Populacional");
            break;
        case 6:
            atributo1 = pib_per_capita;
            atributo2 = pib_per_capita2;
            strcpy(n_atributo, "PIB per Capita");
            break;
        default:
            printf("Opção inválida!\n");
            return 1;
    }
    // Exibição das cartas e comparativo
    printf("\nComparação de cartas (Atributo: %s):\n", n_atributo);
    printf("Carta 1 - %s (%s): %.2f\n", cidade, estado, atributo1);
    printf("Carta 2 - %s (%s): %.2f\n", cidade2, estado2, atributo2);

    // Lógica de comparação
    if (escolha == 5) {
        // Regra invertida para densidade populacional
        if (atributo1 < atributo2) {
            printf("Carta 1 (%s) venceu!\n", cidade);
        } else if (atributo1 > atributo2) {
            printf("Carta 2 (%s) venceu!\n", cidade2);
        } else {
            printf("Empate!\n");
        }
    } else {
        // Regra normal para os outros atributos
        if (atributo1 > atributo2) {
            printf("Carta 1 (%s) venceu!\n", cidade);
        } else if (atributo1 < atributo2) {
            printf("Carta 2 (%s) venceu!\n", cidade2);
        } else {
            printf("Empate!\n");
        }
    }

    return 0;
}