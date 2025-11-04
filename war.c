#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 50
#define TAM_COR 20
#define MAX_TERRITORIOS 50
#define MAX_JOGADORES 3
#define MAX_MISSOES 5

// Estruturas
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

typedef struct {
    int id;
    char cor[TAM_COR];
    char *missao;
} Jogador;

// Variáveis globais
Jogador jogadores[MAX_JOGADORES];

// Array de missões disponíveis
char *missoesPadrao[MAX_MISSOES] = {
    "Conquistar 3 territorios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Controlar 4 territorios",
    "Ter mais tropas que qualquer outro jogador",
    "Destruir completamente a cor azul"
};

// Funções de missões
void atribuirMissao(char *destino, char *missoes[], int total) {
    int i = rand() % total;
    strcpy(destino, missoes[i]);
}

void exibirMissao(char *missao) {
    printf("Missao: %s\n", missao);
}

int verificarMissao(char *missao, Territorio *territorios, int tam, char *corJogador) {
    if (strstr(missao, "3 territorios seguidos")) {
        for (int i = 0; i < tam - 2; i++) {
            if (strcmp(territorios[i].cor, corJogador) == 0 &&
                strcmp(territorios[i+1].cor, corJogador) == 0 &&
                strcmp(territorios[i+2].cor, corJogador) == 0) {
                return 1;
            }
        }
    }
    // ... [resto das verificações de missão como no código original]
    return 0;
}

// Funções de território
void cadastrarTerritorios(Territorio* territorios, int qtd) {
    printf("\nVamos cadastrar os %d territorios do nosso mundo\n", qtd);
    
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        
        printf("Nome do Territorio: ");
        scanf(" %49[^\n]", territorios[i].nome);
        
        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf(" %19s", territorios[i].cor);
        
        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
}

void exibirMapa(Territorio* territorios, int qtd) {
    printf("\n--- Territorios Cadastrados ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %s | %s | tropas=%d\n", 
               i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não pode atacar território da mesma cor!\n");
        return;
    }
    if (atacante->tropas < 2) {
        printf("Erro: precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\nAtaque: %s (%s) [%d] x %s (%s) [%d]\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);
    
    printf("Dados: Atacante=%d Defensor=%d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf("%s conquistou %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        int mover = atacante->tropas / 2;
        if (mover < 1) mover = 1;
        atacante->tropas -= mover;
        defensor->tropas = mover;
    } else {
        printf("Defesa venceu!\n");
        atacante->tropas--;
        if (atacante->tropas < 1) atacante->tropas = 1;
    }
}

void liberarMemoria() {
    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (jogadores[i].missao) free(jogadores[i].missao);
    }
}

int main() {
    srand(time(NULL));
    
    // Inicialização dos jogadores
    char coresJogadores[MAX_JOGADORES][TAM_COR] = {"vermelha", "azul", "verde"};
    for (int i = 0; i < MAX_JOGADORES; i++) {
        jogadores[i].id = i + 1;
        strcpy(jogadores[i].cor, coresJogadores[i]);
        jogadores[i].missao = (char*) malloc(100 * sizeof(char));
        atribuirMissao(jogadores[i].missao, missoesPadrao, MAX_MISSOES);
        printf("\nJogador %d (%s): ", jogadores[i].id, jogadores[i].cor);
        exibirMissao(jogadores[i].missao);
    }

    // Cadastro de territórios
    int qtd;
    printf("\nQuantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);
    if (qtd > MAX_TERRITORIOS) qtd = MAX_TERRITORIOS;

    Territorio territorios[MAX_TERRITORIOS];
    cadastrarTerritorios(territorios, qtd);

    // Loop principal do jogo
    int continuar = 1;
    while (continuar) {
        exibirMapa(territorios, qtd);

        // Verificar missões
        for (int j = 0; j < MAX_JOGADORES; j++) {
            if (verificarMissao(jogadores[j].missao, territorios, qtd, jogadores[j].cor)) {
                printf("\nJogador %d completou sua missão e venceu!\n", jogadores[j].id);
                continuar = 0;
                break;
            }
        }

        if (!continuar) break;

        // Realizar ataque
        int a, d;
        printf("Qual o territorio atacante (1 a %d): ", qtd);
        scanf("%d", &a);
        printf("Qual o territorio defensor (1 a %d): ", qtd);
        scanf("%d", &d);

        a--; d--; // Ajustando índices para base 0

        if (a >= 0 && a < qtd && d >= 0 && d < qtd) {
            if (a != d) {
                atacar(&territorios[a], &territorios[d]);
            } else {
                printf("Erro: não pode atacar o mesmo territorio!\n");
            }
        } else {
            printf("Erro: indices invalidos!\n");
        }

        printf("\nDeseja continuar jogando? (1=sim, 0=não): ");
        scanf("%d", &continuar);
    }

    liberarMemoria();
    printf("\nFim de jogo!\n");
    return 0;
}