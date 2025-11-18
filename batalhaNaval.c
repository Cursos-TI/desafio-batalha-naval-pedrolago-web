#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
int posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
int posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
int posicionarNavioDiagonalDireita(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
int posicionarNavioDiagonalEsquerda(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
int verificarSobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int direcao);
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);

int main() {
    
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    
    inicializarTabuleiro(tabuleiro);
    
    printf("Posicionando navios...\n");
    
    if (posicionarNavioHorizontal(tabuleiro, 2, 1)) {
        printf("Navio horizontal posicionado com sucesso!\n");
    } else {
        printf("Erro: Posição inválida para navio horizontal!\n");
        return 1;
    }
    
    if (posicionarNavioVertical(tabuleiro, 1, 8)) {
        printf("Navio vertical posicionado com sucesso!\n");
    } else {
        printf("Erro: Posição inválida para navio vertical!\n");
        return 1;
    }
    
    if (posicionarNavioDiagonalDireita(tabuleiro, 5, 2)) {
        printf("Navio diagonal direita posicionado com sucesso!\n");
    } else {
        printf("Erro: Posição inválida para navio diagonal direita!\n");
        return 1;
    }
    
    if (posicionarNavioDiagonalEsquerda(tabuleiro, 4, 7)) {
        printf("Navio diagonal esquerda posicionado com sucesso!\n");
    } else {
        printf("Erro: Posição inválida para navio diagonal esquerda!\n");
        return 1;
    }
    
    printf("\nTabuleiro do Batalha Naval (com navios diagonais):\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}

/**
 * Inicializa todas as posições do tabuleiro com água (valor 0)
 * @param tabuleiro Matriz 10x10 representando o tabuleiro
 */
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; 
        }
    }
}

/**
 * Verifica se há sobreposição em uma determinada direção
 * @param tabuleiro Matriz do tabuleiro
 * @param linha Linha inicial
 * @param coluna Coluna inicial
 * @param direcao Direção do navio (0=horizontal, 1=vertical, 2=diagonal direita, 3=diagonal esquerda)
 * @return 1 se não há sobreposição, 0 se há sobreposição
 */
int verificarSobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int posL = linha, posC = coluna;
        
        switch (direcao) {
            case 0: // Horizontal
                posC = coluna + i;
                break;
            case 1: // Vertical
                posL = linha + i;
                break;
            case 2: // Diagonal direita
                posL = linha + i;
                posC = coluna + i;
                break;
            case 3: // Diagonal esquerda
                posL = linha + i;
                posC = coluna - i;
                break;
        }
        
        if (tabuleiro[posL][posC] != 0) {
            return 0; 
        }
    }
    return 1; 
}

/**
 * Posiciona um navio horizontalmente no tabuleiro
 * @param tabuleiro Matriz do tabuleiro
 * @param linha Linha inicial do navio
 * @param coluna Coluna inicial do navio
 * @return 1 se posicionamento bem-sucedido, 0 se falhou
 */
int posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    
    if (coluna + TAM_NAVIO > TAM_TABULEIRO) {
        return 0; 
    }
    
    
    if (linha < 0 || linha >= TAM_TABULEIRO) {
        return 0; 
    }
    
    if (!verificarSobreposicao(tabuleiro, linha, coluna, 0)) {
        return 0;
    }
    
    
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3; 
    }
    
    return 1;
}

/**
 * Posiciona um navio verticalmente no tabuleiro
 * @param tabuleiro Matriz do tabuleiro
 * @param linha Linha inicial do navio
 * @param coluna Coluna inicial do navio
 * @return 1 se posicionamento bem-sucedido, 0 se falhou
 */
int posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    
    if (linha + TAM_NAVIO > TAM_TABULEIRO) {
        return 0; 
    }
    
    
    if (coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0; 
    }
    
    if (!verificarSobreposicao(tabuleiro, linha, coluna, 1)) {
        return 0; // Há sobreposição
    }
    
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3; // 3 representa parte de um navio
    }
    
    return 1;
}

/**
 * Posiciona um navio na diagonal para baixo-direita
 * @param tabuleiro Matriz do tabuleiro
 * @param linha Linha inicial do navio
 * @param coluna Coluna inicial do navio
 * @return 1 se posicionamento bem-sucedido, 0 se falhou
 */
int posicionarNavioDiagonalDireita(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    
    if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna + TAM_NAVIO > TAM_TABULEIRO) {
        return 0; // Navio ultrapassa os limites do tabuleiro
    }
    
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0; // Coordenadas inválidas
    }

    if (!verificarSobreposicao(tabuleiro, linha, coluna, 2)) {
        return 0; // Há sobreposição
    }
    
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = 3; // 3 representa parte de um navio
    }
    
    return 1;
}

/**
 * Posiciona um navio na diagonal para baixo-esquerda
 * @param tabuleiro Matriz do tabuleiro
 * @param linha Linha inicial do navio
 * @param coluna Coluna inicial do navio
 * @return 1 se posicionamento bem-sucedido, 0 se falhou
 */
int posicionarNavioDiagonalEsquerda(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    
    if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna - (TAM_NAVIO - 1) < 0) {
        return 0; // Navio ultrapassa os limites do tabuleiro
    }
    
    
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0; // Coordenadas inválidas
    }
    
    if (!verificarSobreposicao(tabuleiro, linha, coluna, 3)) {
        return 0; // Há sobreposição
    }
    
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = 3; // 3 representa parte de um navio
    }
    
    return 1;
}

/**
 * Exibe o tabuleiro no console
 * @param tabuleiro Matriz 10x10 representando o tabuleiro
 */
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {

    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i); // Índice da linha
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}