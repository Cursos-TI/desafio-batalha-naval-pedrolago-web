#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
int posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
int posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
int posicionarNavioDiagonalDireita(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
int posicionarNavioDiagonalEsquerda(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
int verificarSobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int direcao);
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void aplicarHabilidadeTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                               int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                               int centro_linha, int centro_coluna);
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);

int main() {
    
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
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
    
    printf("\nCriando habilidades especiais...\n");
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    printf("Aplicando habilidades no tabuleiro...\n");
    
    aplicarHabilidadeTabuleiro(tabuleiro, cone, 4, 4);
    printf("Habilidade Cone aplicada no centro (4,4)\n");
    
    aplicarHabilidadeTabuleiro(tabuleiro, cruz, 7, 2);
    printf("Habilidade Cruz aplicada no centro (7,2)\n");
    
    aplicarHabilidadeTabuleiro(tabuleiro, octaedro, 2, 6);
    printf("Habilidade Octaedro aplicada no centro (2,6)\n");
    
    printf("\nTabuleiro do Batalha Naval com Habilidades Especiais:\n");
    printf("Legenda: 0=Agua, 3=Navio, 5=Area da Habilidade\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}

/**
 * @param tabuleiro Matriz 10x10 representando o tabuleiro
 */
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
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
            case 0: 
                posC = coluna + i;
                break;
            case 1: 
                posL = linha + i;
                break;
            case 2: 
                posL = linha + i;
                posC = coluna + i;
                break;
            case 3: 
                posL = linha + i;
                posC = coluna - i;
                break;
        }
        
        if (tabuleiro[posL][posC] != AGUA) {
            return 0; 
        }
    }
    return 1; 
}

/**
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
        tabuleiro[linha][coluna + i] = NAVIO;
    }
    
    return 1;
}

/**
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
        return 0;
    }
    
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }
    
    return 1;
}

/**
 * @param tabuleiro Matriz do tabuleiro
 * @param linha Linha inicial do navio
 * @param coluna Coluna inicial do navio
 * @return 1 se posicionamento bem-sucedido, 0 se falhou
 */
int posicionarNavioDiagonalDireita(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
   
    if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna + TAM_NAVIO > TAM_TABULEIRO) {
        return 0;
    }
    
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0;
    }
    
    if (!verificarSobreposicao(tabuleiro, linha, coluna, 2)) {
        return 0;
    }
    
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = NAVIO;
    }
    
    return 1;
}

/**
 * @param tabuleiro Matriz do tabuleiro
 * @param linha Linha inicial do navio
 * @param coluna Coluna inicial do navio
 * @return 1 se posicionamento bem-sucedido, 0 se falhou
 */
int posicionarNavioDiagonalEsquerda(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {

    if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna - (TAM_NAVIO - 1) < 0) {
        return 0;
    }
    
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0;
    }
    
    if (!verificarSobreposicao(tabuleiro, linha, coluna, 3)) {
        return 0;
    }
    

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = NAVIO;
    }
    
    return 1;
}

/**
 * @param habilidade Matriz 5x5 para armazenar o padrão do cone
 */
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            if (i == 0 && j == 2) {
                habilidade[i][j] = 1; 
            }
            else if (i == 1 && j >= 1 && j <= 3) {
                habilidade[i][j] = 1; 
            }
            else if (i == 2 && j >= 0 && j <= 4) {
                habilidade[i][j] = 1; 
            }
            else if (i == 3 && j >= 1 && j <= 3) {
                habilidade[i][j] = 1; 
            }
            else if (i == 4 && j == 2) {
                habilidade[i][j] = 1; 
        }
    }
}

/**
 * @param habilidade Matriz 5x5 para armazenar o padrão da cruz
 */
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            if (i == 2 || j == 2) { // Linha do meio ou coluna do meio
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * @param habilidade Matriz 5x5 para armazenar o padrão do octaedro
 */
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            if (i == 0 && j == 2) {
                habilidade[i][j] = 1; 
            }
            else if (i == 1 && (j == 1 || j == 2 || j == 3)) {
                habilidade[i][j] = 1; 
            }
            else if (i == 2) {
                habilidade[i][j] = 1; 
            }
            else if (i == 3 && (j == 1 || j == 2 || j == 3)) {
                habilidade[i][j] = 1; 
            }
            else if (i == 4 && j == 2) {
                habilidade[i][j] = 1; 
            }
        }
    }
}

/**
 * @param tabuleiro Matriz do tabuleiro
 * @param habilidade Matriz da habilidade a ser aplicada
 * @param centro_linha Linha do centro da habilidade
 * @param centro_coluna Coluna do centro da habilidade
 */
void aplicarHabilidadeTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                               int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                               int centro_linha, int centro_coluna) {
    
    int offset = TAM_HABILIDADE / 2; // 2 para matriz 5x5
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            int tab_linha = centro_linha - offset + i;
            int tab_coluna = centro_coluna - offset + j;
            
            if (tab_linha >= 0 && tab_linha < TAM_TABULEIRO && 
                tab_coluna >= 0 && tab_coluna < TAM_TABULEIRO) {
                
                if (habilidade[i][j] == 1) {
                    tabuleiro[tab_linha][tab_coluna] = HABILIDADE;
                }
            }
        }
    }
}

/**
 * @param tabuleiro Matriz 10x10 representando o tabuleiro
 */
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i); 
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}