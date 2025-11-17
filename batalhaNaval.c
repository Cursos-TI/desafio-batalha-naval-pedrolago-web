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

    if (linha < 0 || linha >= TAM_TABULEIRO) {
        return 0; // Linha inválida
    }

     for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != 0) {
            return 0; // Já existe um navio nesta posição
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3; // 3 representa parte de um navio
    }
    
    return 1;
}

int posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    // Verificar se o navio cabe verticalmente a partir da linha inicial
    if (linha + TAM_NAVIO > TAM_TABULEIRO) {
        return 0;
    }

    if (coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0; 
    }
    
    // Verificar sobreposição com outros navios
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0) {
            return 0; 
        }
    }

    if (coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0; 
    }
    
    // Verifica sobreposição com outros navios
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0) {
            return 0;  
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3; 
    }
    
    return 1;
}

void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("   0 1 2 3 4 5 6 7 8 9\n"); // Índices das colunas
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%d  ", i); // Índice da linha
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}