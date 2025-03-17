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

    printf("c�digo: ");
    scanf("%s", codigo);

    printf("nome da cidade: ");
    scanf(" %69[^\n]", cidade); 

    printf("popula��o: ");
    scanf("%d", &populacao);

    printf("�rea: ");
    scanf("%f", &area);

    printf("PIB: ");
    scanf("%f", &pib);

    printf("n�mero de pontos turisticos: ");
    scanf("%d", &pontos);

     // C�lculos para a Carta 1
     densidade_populacional = populacao / area;
     pib_per_capita = pib / populacao;

    // Exibi��o dos dados da Carta 1
    printf("\nCarta 1\n");
    printf("Estado: %s\n", estado);
    printf("C�digo: %s\n", codigo);
    printf("Nome da Cidade: %s\n", cidade);
    printf("Popula��o: %d\n", populacao);
    printf("�rea %.2f km�: \n", area);
    printf("PIB: %.2f\n", pib);
    printf("N�mero de Pontos Tur�sticos: %d\n", pontos);
    printf("Densidade Populacional: %.2f hab/km�\n", densidade_populacional);
    printf("PIB per Capita: %.2f\n\n", pib_per_capita);


    //entrada e saida de dados carta 2
    
    printf("carta 2:\n");
    
    printf("estado: ");
    scanf("%s", estado2);

    printf("c�digo: ");
    scanf("%s", codigo2);

    printf("nome da cidade: ");
    scanf(" %69[^\n]", cidade2); 

    printf("popula��o: ");
    scanf("%d", &populacao2);

    printf("�rea: ");
    scanf("%f", &area2);

    printf("PIB: ");
    scanf("%f", &pib2);

    printf("n�mero de pontos turisticos: ");
    scanf("%d", &pontos2);

     // C�lculos para a Carta 2
     densidade_populacional2 = populacao2 / area2;
     pib_per_capita2 = pib2 / populacao2;

    // Exibi��o dos dados da Carta 2
    printf("\nCarta 2\n");
    printf("Estado: %s\n", estado2);
    printf("C�digo: %s\n", codigo2);
    printf("Nome da Cidade: %s\n", cidade2);
    printf("Popula��o: %d\n", populacao2); 
    printf("�rea: %.2f km�\n", area2); 
    printf("PIB: %.2f\n", pib2);
    printf("N�mero de Pontos Tur�sticos: %d\n", pontos2);
    printf("Densidade Populacional: %.2f hab/km�\n", densidade_populacional2);
    printf("PIB per Capita: %.2f\n\n", pib_per_capita2);
    
    // Menu interativo para escolher o atributo de compara��o
    printf("Escolha o atributo para comparar:\n");
    printf("1 - Popula��o\n");
    printf("2 - �rea\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Tur�sticos\n");
    printf("5 - Densidade Populacional\n");
    printf("6 - PIB per Capita\n");
    printf("Op��o: ");
    scanf("%d", &escolha);

    // Compara��o de atributos
    char n_atributo[50];

    switch (escolha) {
        case 1:
            atributo1 = populacao;
            atributo2 = populacao2;
            strcpy(n_atributo, "Popula��o");
            break;
        case 2:
            atributo1 = area;
            atributo2 = area2;
            strcpy(n_atributo, "�rea");
            break;
        case 3:
            atributo1 = pib;
            atributo2 = pib2;
            strcpy(n_atributo, "PIB");
            break;
        case 4:
            atributo1 = pontos;
            atributo2 = pontos2;
            strcpy(n_atributo, "Pontos Tur�sticos");
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
            printf("Op��o inv�lida!\n");
            return 1;
    }
    // Exibi��o das cartas e comparativo
    printf("\nCompara��o de cartas (Atributo: %s):\n", n_atributo);
    printf("Carta 1 - %s (%s): %.2f\n", cidade, estado, atributo1);
    printf("Carta 2 - %s (%s): %.2f\n", cidade2, estado2, atributo2);

    // L�gica de compara��o
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