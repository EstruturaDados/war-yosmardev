#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 50
#define TAM_COR  20
#define MAX_TERRITORIOS 50

// Definição da estrutura para um território
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// Função para cadastrar territórios
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

// Função para exibir o mapa
void exibirMapa(Territorio* territorios, int qtd) {
    printf("\n--- Territorios Cadastrados ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("\n");
    }
}

// Função de ataque
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

int main() {
    srand(time(NULL));
    
    int qtd;
    printf("Quantos territorios deseja cadastrar ?");
    scanf("%d", &qtd);

    if (qtd > MAX_TERRITORIOS) qtd = MAX_TERRITORIOS;

    Territorio territorios[MAX_TERRITORIOS];

    cadastrarTerritorios(territorios, qtd);
    
    int continuar = 1;
    while (continuar) {
        exibirMapa(territorios, qtd);

        int a, d;
        printf("Qual o número do territorio atacante (Ex: 1,2,3...): ");
        scanf("%d", &a);
        printf("Qual o número do territorio defensor (Ex: 1,2,3...): ");
        scanf("%d", &d);

        a--; // Ajustando índices para base 0
        d--;

        if (a >= 0 && a < qtd && d >= 0 && d < qtd) {
            if (a != d) {
                atacar(&territorios[a], &territorios[d]);
            } else {
                printf("Erro: não pode atacar o mesmo territorio!\n");
            }
        } else {
            printf("Erro: indices invalidos!\n");
        }

        printf("\nDeseja realizar outro ataque? (1=sim, 0=não): ");
        scanf("%d", &continuar);
    }

    printf("\nFim de jogo!\n");
    return 0;
}