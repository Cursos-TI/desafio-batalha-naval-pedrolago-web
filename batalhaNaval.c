#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
int posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
int posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);

int main() {

    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    inicializarTabuleiro(tabuleiro);

    printf("Posicionando navios...\n");

if (posicionarNavioHorizontal(tabuleiro, 2, 3)) {
        printf("Navio horizontal posicionado com sucesso!\n");
    } else {
        printf("Erro: Posição inválida para navio horizontal!\n");
        return 1;
    }

if (posicionarNavioVertical(tabuleiro, 5, 7)) {
        printf("Navio vertical posicionado com sucesso!\n");
    } else {
        printf("Erro: Posição inválida para navio vertical!\n");
        return 1;
    }

 printf("\nTabuleiro do Batalha Naval:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; 
        }
    }
}

int posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    // Verifica se o navio cabe horizontalmente a partir da coluna inicial
    if (coluna + TAM_NAVIO > TAM_TABULEIRO) {
        return 0; // Navio ultrapassa o limite direito do tabuleiro
    }