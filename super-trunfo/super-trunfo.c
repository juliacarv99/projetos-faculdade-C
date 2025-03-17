#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    char estado [3], estado2 [3];
    char codigo [4], codigo2 [4];
    char cidade [70], cidade2 [70];
    unsigned long int populacao, populacao2;
    int pontos, pontos2, vencedor_pop, vencedor_area, vencedor_densidade, vencedor_pib, vencedor_pib_per, vencedor_pontos, vencedor_superpoder;
    float area, pib, area2, pib2;
    float densidade_populacional, densidade_populacional2;
    float pib_per_capita, pib_per_capita2;
    float superpoder, superpoder2;
    float inverso_densidade, inverso_densidade2;

    //entrada e saida de dados carta 1
    printf("carta 1:\n");
     
    printf("\nestado: ");
    scanf("%s", estado);

    printf("c�digo: ");
    scanf("%s", codigo);

    printf("nome da cidade: ");
    scanf(" %69[^\n]", cidade); 

    printf("popula��o: ");
    scanf("%lu", &populacao);

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
    printf("Popula��o: %lu\n", populacao);
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
    scanf("%lu", &populacao2);

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
    printf("Popula��o: %lu\n", populacao2);
    printf("�rea %.2f km�: \n", area2);
    printf("PIB: %.2f\n", pib2);
    printf("N�mero de Pontos Tur�sticos: %d\n\n", pontos2);
    printf("Densidade Populacional: %.2f hab/km�\n", densidade_populacional2);
    printf("PIB per Capita: %.2f\n\n", pib_per_capita2);

    //inverso densidade populacional
    inverso_densidade = area / populacao;
    inverso_densidade2 = area2 / populacao2;
    
    //calculo super poder
    superpoder = (float)populacao + (float)area + pib + (float)pontos + pib_per_capita + inverso_densidade;
    superpoder2 = (float)populacao2 + (float)area2 + pib2 + (float)pontos2 + pib_per_capita2 + inverso_densidade2;

    //compara��o de cartas

    vencedor_pop = (populacao > populacao2);
    vencedor_area = (area > area2);
    vencedor_pib = (pib > pib2);
    vencedor_pontos = (pontos > pontos2);
    vencedor_densidade = (densidade_populacional < densidade_populacional2);
    vencedor_pib_per = (pib_per_capita > pib_per_capita2);
    vencedor_superpoder = (superpoder > superpoder2);

    printf("popula��o: carta %d venceu(%d)\n", 2 - vencedor_pop, vencedor_pop);
    printf("�rea: Carta %d venceu (%d)\n", 2 - vencedor_pop, vencedor_pop);
    printf("PIB: Carta %d venceu (%d)\n", 2 - vencedor_pib, vencedor_pib);
    printf("Pontos Tur�sticos: Carta %d venceu (%d)\n", vencedor_pontos, vencedor_pontos);
    printf("Densidade Populacional: Carta %d venceu (%d)\n", 2 -  vencedor_densidade, vencedor_densidade);
    printf("PIB per Capita: Carta %d venceu (%d)\n", 2 - vencedor_pib_per, vencedor_pib_per);
    printf("Super Poder: Carta %d venceu (%d)\n", 2 - vencedor_superpoder, vencedor_superpoder);


    return 0;




}