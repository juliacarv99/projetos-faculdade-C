#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    
    // Declara��o das vari�veis da carta 1
    char estado[50], cidade[50], codigo[10];
    int populacao, pontos;
    float area, pib, densidade_populacional, pib_per_capita;

    // Declara��o das vari�veis da carta 2
    char estado2[50], cidade2[50], codigo2[10];
    int populacao2, pontos2;
    float area2, pib2, densidade_populacional2, pib_per_capita2;

    //entrada de dados carta 1
    printf("Digite os dados da carta 1:\n");
    printf("Estado: "); gets(estado);
    printf("C�digo: "); gets(codigo);
    printf("Nome da Cidade: "); gets(cidade);
    printf("Popula��o: "); scanf("%d", &populacao);
    printf("�rea (em km�): "); scanf("%f", &area);
    printf("PIB: "); scanf("%f", &pib);
    printf("N�mero de Pontos Tur�sticos: "); scanf("%d", &pontos);

     // C�lculos para a Carta 1
     densidade_populacional = populacao / area;
     pib_per_capita = pib / populacao;

     getchar(); // Para limpar buffer do teclado

    // Entrada de dados da Carta 2
    printf("\nDigite os dados da carta 2:\n");
    printf("Estado: "); gets(estado2);
    printf("C�digo: "); gets(codigo2);
    printf("Nome da Cidade: "); gets(cidade2);
    printf("Popula��o: "); scanf("%d", &populacao2);
    printf("�rea (em km�): "); scanf("%f", &area2);
    printf("PIB: "); scanf("%f", &pib2);
    printf("N�mero de Pontos Tur�sticos: "); scanf("%d", &pontos2);

     // C�lculos para a Carta 2
     densidade_populacional2 = populacao2 / area2;
     pib_per_capita2 = pib2 / populacao2;
    
     // Menu de escolha de atributos
    int escolha1, escolha2;
    float atributo1_carta1, atributo1_carta2, atributo2_carta1, atributo2_carta2;
    float soma1, soma2;
    char nome1[50], nome2[50];
    
    printf("\nEscolha o primeiro atributo para comparar:\n");
    printf("1 - Popula��o\n2 - �rea\n3 - PIB\n4 - Pontos Tur�sticos\n5 - Densidade Populacional\n6 - PIB per Capita\n");
    printf("Op��o: ");
    scanf("%d", &escolha1);

    // escolha de atributos
    switch (escolha1) {
        case 1: atributo1_carta1 = populacao; atributo1_carta2 = populacao2; strcpy(nome1, "Popula��o"); break;
        case 2: atributo1_carta1 = area; atributo1_carta2 = area2; strcpy(nome1, "�rea"); break;
        case 3: atributo1_carta1 = pib; atributo1_carta2 = pib2; strcpy(nome1, "PIB"); break;
        case 4: atributo1_carta1 = pontos; atributo1_carta2 = pontos2; strcpy(nome1, "Pontos Tur�sticos"); break;
        case 5: atributo1_carta1 = densidade_populacional; atributo1_carta2 = densidade_populacional2; strcpy(nome1, "Densidade Populacional"); break;
        case 6: atributo1_carta1 = pib_per_capita; atributo1_carta2 = pib_per_capita2; strcpy(nome1, "PIB per Capita"); break;
        default: printf("Op��o inv�lida!\n"); return 1;
    }
    do {
        printf("\nEscolha o segundo atributo (diferente do primeiro):\n");
        printf("1 - Popula��o\n2 - �rea\n3 - PIB\n4 - Pontos Tur�sticos\n5 - Densidade Populacional\n6 - PIB per Capita\n");
        printf("Op��o: ");
        scanf("%d", &escolha2);

        if (escolha2 == escolha1 || escolha2 < 1 || escolha2 > 6) {
            printf("Atributo inv�lido ou j� escolhido. Tente novamente.\n");
        }
    } while (escolha2 == escolha1 || escolha2 < 1 || escolha2 > 6);

    switch (escolha2) {
        case 1: atributo2_carta1 = populacao; atributo2_carta2 = populacao2; strcpy(nome2, "Popula��o"); break;
        case 2: atributo2_carta1 = area; atributo2_carta2 = area2; strcpy(nome2, "�rea"); break;
        case 3: atributo2_carta1 = pib; atributo2_carta2 = pib2; strcpy(nome2, "PIB"); break;
        case 4: atributo2_carta1 = pontos; atributo2_carta2 = pontos2; strcpy(nome2, "Pontos Tur�sticos"); break;
        case 5: atributo2_carta1 = densidade_populacional; atributo2_carta2 = densidade_populacional2; strcpy(nome2, "Densidade Populacional"); break;
        case 6: atributo2_carta1 = pib_per_capita; atributo2_carta2 = pib_per_capita2; strcpy(nome2, "PIB per Capita"); break;
        default: printf("Op��o inv�lida!\n"); return 1;
    }

    // Compara��o de atributos
    float pontos_rodada1 = 0, pontos_rodada2 = 0;

    // Primeiro atributo
    if (escolha1 == 5) {
        if (atributo1_carta1 < atributo1_carta2) pontos_rodada1++;
        else if (atributo1_carta1 > atributo1_carta2) pontos_rodada2++;
    } else {
        if (atributo1_carta1 > atributo1_carta2) pontos_rodada1++;
        else if (atributo1_carta1 < atributo1_carta2) pontos_rodada2++;
    }

    // Segundo atributo
    if (escolha2 == 5) {
        if (atributo2_carta1 < atributo2_carta2) pontos_rodada1++;
        else if (atributo2_carta1 > atributo2_carta2) pontos_rodada2++;
    } else {
        if (atributo2_carta1 > atributo2_carta2) pontos_rodada1++;
        else if (atributo2_carta1 < atributo2_carta2) pontos_rodada2++;
    }

    // Soma dos atributos
    soma1 = atributo1_carta1 + atributo2_carta1;
    soma2 = atributo1_carta2 + atributo2_carta2;

    // Exibi��o dos resultados
    printf("\nCompara��o de cartas usando atributos: %s e %s\n", nome1, nome2);
    printf("\nCarta 1 - %s (%s):\n", cidade, estado);
    printf("%s: %.2f | %s: %.2f | Soma: %.2f\n", nome1, atributo1_carta1, nome2, atributo2_carta1, soma1);

    printf("\nCarta 2 - %s (%s):\n", cidade2, estado2);
    printf("%s: %.2f | %s: %.2f | Soma: %.2f\n", nome1, atributo1_carta2, nome2, atributo2_carta2, soma2);

    if (soma1 > soma2) {
        printf("\nResultado: Carta 1 venceu!\n");
    } else if (soma2 > soma1) {
        printf("\nResultado: Carta 2 venceu!\n");
    } else {
        printf("\nResultado: Empate!\n");
    }



    return 0;
}