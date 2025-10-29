#include <stdio.h>
#include <string.h>

// Definição da estrutura para um território
typedef struct {
    char nome[50];
    char cor_exercito[20];
    int numero_tropas;
} Territorio;

int main() {
    // Declarando um array para 5 territórios
    Territorio territorios[5];
    int i;

    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo\n");

    // Loop para cadastrar os 5 territórios
    for (i = 0; i < 5; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        // Entrada do nome do território
        printf("Nome do Territorio: ");
        scanf("%s", territorios[i].nome);

        // Entrada da cor do exército
        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf("%s", territorios[i].cor_exercito);

        // Entrada do número de tropas
        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].numero_tropas);

        printf("\n");
    }

    //Visualização de dados cadastrados //
    printf("--- Territorios Cadastrados ---\n");
    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor_exercito);
        printf("  Tropas: %d\n", territorios[i].numero_tropas);
        printf("\n");
    }

    return 0;
}