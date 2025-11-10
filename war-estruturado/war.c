// territorios.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

typedef struct {
    char nome[30];
    char cor[10];
    char *missao;    // dinamicamente alocada
    int missaoId;    // id da missão sorteada
} Jogador;

/* -------- Funções relacionadas a cadastro e exibição -------- */

// cadastra n territórios em mapa (memória já alocada)
void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %9s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// exibe o mapa atual
void exibirTerritorios(Territorio *mapa, int n) {
    printf("\n=== Mapa dos Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("%2d) % -20s | Exército: % -8s | Tropas: %3d\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/* -------- Funções de ataque e gerenciamento de memória -------- */

// simula um ataque entre dois territórios; usa ponteiros para alterar dados
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\n[ATAQUE] %s (%s, %d tropas) -> %s (%s, %d tropas)\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf("Resultado: atacante venceu!\n");
        // defensor muda de cor e recebe metade das tropas do atacante (inteiro)
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        // atacante mantém suas tropas (poderia ser ajustado conforme regra)
    } else {
        printf("Resultado: defensor resistiu!\n");
        atacante->tropas = (atacante->tropas > 0) ? atacante->tropas - 1 : 0;
    }
}

// libera mapa e missões dos jogadores
void liberarMemoria(Territorio *mapa, Jogador *jogadores, int numJogadores) {
    if (mapa) free(mapa);
    for (int i = 0; i < numJogadores; i++) {
        if (jogadores[i].missao) free(jogadores[i].missao);
    }
}

/* -------- Funções de missão (atribuir e verificar) -------- */

// retorna uma missão alocada dinamicamente e seta missão id via ponteiro
char* atribuirMissao(int *missaoId, char *missoes[], int totalMissoes) {
    int id = rand() % totalMissoes;
    *missaoId = id;
    size_t len = strlen(missoes[id]) + 1;
    char *dst = (char*) malloc(len);
    if (dst) strcpy(dst, missoes[id]);
    return dst;
}

// verifica se missão foi cumprida; lógica simples baseada em missaoId
// retorna 1 se cumpriu, 0 caso contrário
int verificarMissao(int missaoId, Jogador *j, Territorio *mapa, int tamanho) {
    // conta territórios e tropas do jogador
    int contaTerritorios = 0;
    int tropasTotais = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, j->cor) == 0) {
            contaTerritorios++;
            tropasTotais += mapa[i].tropas;
        }
    }

    switch (missaoId) {
        case 0:
            // Conquistar 3 territórios (possuir pelo menos 3 territórios)
            return (contaTerritorios >= 3) ? 1 : 0;
        case 1:
            // Eliminar todas as tropas da cor "vermelho"
            {
                int somaVermelho = 0;
                for (int i = 0; i < tamanho; i++)
                    if (strcmp(mapa[i].cor, "vermelho") == 0)
                        somaVermelho += mapa[i].tropas;
                return (somaVermelho == 0) ? 1 : 0;
            }
        case 2:
            // Possuir pelo menos um território com mais de 10 tropas
            for (int i = 0; i < tamanho; i++)
                if ((strcmp(mapa[i].cor, j->cor) == 0) && (mapa[i].tropas > 10))
                    return 1;
            return 0;
        case 3:
            // Controlar a maioria dos territórios (> total/2)
            return (contaTerritorios > (tamanho / 2)) ? 1 : 0;
        case 4:
            // Ter pelo menos 15 tropas no total
            return (tropasTotais >= 15) ? 1 : 0;
        default:
            return 0;
    }
}

/* -------- Função auxiliar para mostrar missão (passagem por valor) -------- */

void exibirMissao(const char *missaoTexto) {
    printf("\n--- Sua missão ---\n%s\n", missaoTexto);
}

/* -------- Main: fluxo do jogo simplificado -------- */

int main() {
    srand((unsigned) time(NULL));

    int n;
    printf("Digite o número total de territórios: ");
    scanf("%d", &n);
    if (n <= 0) return 0;

    // aloca dinamicamente mapa
    Territorio *mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    // cadastra territórios
    cadastrarTerritorios(mapa, n);

    // configura jogadores (2 jogadores para exemplo)
    int numJogadores = 2;
    Jogador jogadores[2];
    for (int i = 0; i < numJogadores; i++) {
        printf("\nNome do jogador %d: ", i+1);
        scanf(" %29[^\n]", jogadores[i].nome);
        printf("Cor do exército do jogador %d: ", i+1);
        scanf(" %9s", jogadores[i].cor);
        jogadores[i].missao = NULL;
        jogadores[i].missaoId = -1;
    }

    // vetor de missões possíveis
    char *missoes[] = {
        "Conquistar 3 territorios.",
        "Eliminar todas as tropas da cor vermelho.",
        "Possuir pelo menos um territorio com mais de 10 tropas.",
        "Controlar a maioria dos territorios.",
        "Ter ao menos 15 tropas no total."
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // atribui missão a cada jogador (dinamicamente)
    for (int i = 0; i < numJogadores; i++) {
        jogadores[i].missao = atribuirMissao(&jogadores[i].missaoId, missoes, totalMissoes);
        printf("\nJogador %s recebeu sua missão (visível apenas para ele):\n", jogadores[i].nome);
        exibirMissao(jogadores[i].missao); // exibe uma vez
    }

    // laço simples de turnos: cada jogador ataca uma vez por turno até alguém vencer ou jogador optar sair
    int turno = 0;
    int vencedor = -1;
    while (1) {
        int jogadorAtual = turno % numJogadores;
        printf("\n\n========== Turno do jogador: %s (%s) ==========\n", jogadores[jogadorAtual].nome, jogadores[jogadorAtual].cor);
        exibirTerritorios(mapa, n);

        // opções: atacar(1) ou sair(0)
        int opc;
        printf("\nEscolha: 1-Atacar, 0-Sair do jogo: ");
        scanf("%d", &opc);
        if (opc == 0) break;

        int a, d;
        printf("Escolha o numero do territorio atacante (1 a %d): ", n);
        scanf("%d", &a);
        printf("Escolha o numero do territorio defensor (1 a %d): ", n);
        scanf("%d", &d);

        if (a < 1 || a > n || d < 1 || d > n || a == d) {
            printf("Selecao invalida de territorios.\n");
        } else {
            Territorio *at = &mapa[a-1];
            Territorio *df = &mapa[d-1];
            if (strcmp(at->cor, jogadores[jogadorAtual].cor) != 0) {
                printf("Voce so pode atacar com um territorio que seja seu (cor %s).\n", jogadores[jogadorAtual].cor);
            } else if (strcmp(at->cor, df->cor) == 0) {
                printf("Nao e permitido atacar territorio do mesmo exército.\n");
            } else {
                atacar(at, df);
            }
        }

        // apos ataque, checar missões silenciosamente para todos os jogadores
        for (int i = 0; i < numJogadores; i++) {
            if (verificarMissao(jogadores[i].missaoId, &jogadores[i], mapa, n)) {
                vencedor = i;
                break;
            }
        }
        if (vencedor != -1) {
            printf("\n\n############################################\n");
            printf("Vencedor por missão: %s\nMissao: %s\n", jogadores[vencedor].nome, jogadores[vencedor].missao);
            printf("############################################\n");
            break;
        }

        turno++;
    }

    // estado final
    printf("\nEstado final do mapa:\n");
    exibirTerritorios(mapa, n);

    // liberar memórias dinamicamente alocadas
    liberarMemoria(mapa, jogadores, numJogadores);

    printf("\nPrograma encerrado.\n");
    return 0;
}
