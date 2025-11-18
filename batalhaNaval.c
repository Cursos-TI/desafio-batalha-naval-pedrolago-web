#include <stdio.h>

// Constantes para o tamanho do tabuleiro, navios e habilidades
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Constantes para representar os elementos no tabuleiro
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Protótipos das funções
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
    // Declaração do tabuleiro e matrizes de habilidades
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
    // Inicialização do tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);
    
    // Posicionamento dos quatro navios (coordenadas definidas no código)
    printf("Posicionando navios...\n");
    
    // Navio horizontal na linha 2, coluna 1
    if (posicionarNavioHorizontal(tabuleiro, 2, 1)) {
        printf("Navio horizontal posicionado com sucesso!\n");
    } else {
        printf("Erro: Posição inválida para navio horizontal!\n");
        return 1;
    }
    
    // Navio vertical na linha 1, coluna 8
    if (posicionarNavioVertical(tabuleiro, 1, 8)) {
        printf("Navio vertical posicionado com sucesso!\n");
    } else {
        printf("Erro: Posição inválida para navio vertical!\n");
        return 1;
    }
    
    // Navio diagonal para baixo-direita na linha 5, coluna 2
    if (posicionarNavioDiagonalDireita(tabuleiro, 5, 2)) {
        printf("Navio diagonal direita posicionado com sucesso!\n");
    } else {
        printf("Erro: Posição inválida para navio diagonal direita!\n");
        return 1;
    }
    
    // Navio diagonal para baixo-esquerda na linha 4, coluna 7
    if (posicionarNavioDiagonalEsquerda(tabuleiro, 4, 7)) {
        printf("Navio diagonal esquerda posicionado com sucesso!\n");
    } else {
        printf("Erro: Posição inválida para navio diagonal esquerda!\n");
        return 1;
    }
    
    // Criação das matrizes de habilidades
    printf("\nCriando habilidades especiais...\n");
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    // Aplicação das habilidades no tabuleiro (pontos de origem definidos no código)
    printf("Aplicando habilidades no tabuleiro...\n");
    
    // Aplicar habilidade Cone no centro (4, 4)
    aplicarHabilidadeTabuleiro(tabuleiro, cone, 4, 4);
    printf("Habilidade Cone aplicada no centro (4,4)\n");
    
    // Aplicar habilidade Cruz no centro (7, 2)
    aplicarHabilidadeTabuleiro(tabuleiro, cruz, 7, 2);
    printf("Habilidade Cruz aplicada no centro (7,2)\n");
    
    // Aplicar habilidade Octaedro no centro (2, 6)
    aplicarHabilidadeTabuleiro(tabuleiro, octaedro, 2, 6);
    printf("Habilidade Octaedro aplicada no centro (2,6)\n");
    
    // Exibição do tabuleiro
    printf("\nTabuleiro do Batalha Naval com Habilidades Especiais:\n");
    printf("Legenda: 0=Agua, 3=Navio, 5=Area da Habilidade\n");
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
            tabuleiro[i][j] = AGUA;
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
        
        if (tabuleiro[posL][posC] != AGUA) {
            return 0; // Encontrou sobreposição
        }
    }
    return 1; // Não há sobreposição
}

/**
 * Posiciona um navio horizontalmente no tabuleiro
 * @param tabuleiro Matriz do tabuleiro
 * @param linha Linha inicial do navio
 * @param coluna Coluna inicial do navio
 * @return 1 se posicionamento bem-sucedido, 0 se falhou
 */
int posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    // Verifica se o navio cabe horizontalmente a partir da coluna inicial
    if (coluna + TAM_NAVIO > TAM_TABULEIRO) {
        return 0;
    }
    
    // Verifica se a linha está dentro dos limites
    if (linha < 0 || linha >= TAM_TABULEIRO) {
        return 0;
    }
    
    // Verifica sobreposição com outros navios
    if (!verificarSobreposicao(tabuleiro, linha, coluna, 0)) {
        return 0;
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
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
    // Verifica se o navio cabe verticalmente a partir da linha inicial
    if (linha + TAM_NAVIO > TAM_TABULEIRO) {
        return 0;
    }
    
    // Verifica se a coluna está dentro dos limites
    if (coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0;
    }
    
    // Verifica sobreposição com outros navios
    if (!verificarSobreposicao(tabuleiro, linha, coluna, 1)) {
        return 0;
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
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
    // Verifica se o navio cabe na diagonal (linha e coluna aumentam)
    if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna + TAM_NAVIO > TAM_TABULEIRO) {
        return 0;
    }
    
    // Verifica se as coordenadas iniciais estão dentro dos limites
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0;
    }
    
    // Verifica sobreposição com outros navios
    if (!verificarSobreposicao(tabuleiro, linha, coluna, 2)) {
        return 0;
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = NAVIO;
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
    // Verifica se o navio cabe na diagonal (linha aumenta, coluna diminui)
    if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna - (TAM_NAVIO - 1) < 0) {
        return 0;
    }
    
    // Verifica se as coordenadas iniciais estão dentro dos limites
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0;
    }
    
    // Verifica sobreposição com outros navios
    if (!verificarSobreposicao(tabuleiro, linha, coluna, 3)) {
        return 0;
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = NAVIO;
    }
    
    return 1;
}

/**
 * Cria a matriz de habilidade em formato de Cone
 * @param habilidade Matriz 5x5 para armazenar o padrão do cone
 */
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Inicializa toda a matriz com 0
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Define o padrão do cone usando condicionais
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Cone: expande horizontalmente conforme desce verticalmente
            if (i == 0 && j == 2) {
                habilidade[i][j] = 1; // Topo do cone
            }
            else if (i == 1 && j >= 1 && j <= 3) {
                habilidade[i][j] = 1; // Segunda linha
            }
            else if (i == 2 && j >= 0 && j <= 4) {
                habilidade[i][j] = 1; // Terceira linha (base mais larga)
            }
            else if (i == 3 && j >= 1 && j <= 3) {
                habilidade[i][j] = 1; // Quarta linha
            }
            else if (i == 4 && j == 2) {
                habilidade[i][j] = 1; // Ponta inferior
            }
        }
    }
}

/**
 * Cria a matriz de habilidade em formato de Cruz
 * @param habilidade Matriz 5x5 para armazenar o padrão da cruz
 */
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Inicializa toda a matriz com 0
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Define o padrão da cruz usando condicionais
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Cruz: linha horizontal e vertical central
            if (i == 2 || j == 2) { // Linha do meio ou coluna do meio
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * Cria a matriz de habilidade em formato de Octaedro (losango)
 * @param habilidade Matriz 5x5 para armazenar o padrão do octaedro
 */
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Inicializa toda a matriz com 0
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Define o padrão do octaedro (losango) usando condicionais
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Octaedro: formato de losango
            if (i == 0 && j == 2) {
                habilidade[i][j] = 1; // Topo
            }
            else if (i == 1 && (j == 1 || j == 2 || j == 3)) {
                habilidade[i][j] = 1; // Segunda linha
            }
            else if (i == 2) {
                habilidade[i][j] = 1; // Linha do meio (completa)
            }
            else if (i == 3 && (j == 1 || j == 2 || j == 3)) {
                habilidade[i][j] = 1; // Quarta linha
            }
            else if (i == 4 && j == 2) {
                habilidade[i][j] = 1; // Base
            }
        }
    }
}

/**
 * Aplica uma habilidade ao tabuleiro centrada em uma posição específica
 * @param tabuleiro Matriz do tabuleiro
 * @param habilidade Matriz da habilidade a ser aplicada
 * @param centro_linha Linha do centro da habilidade
 * @param centro_coluna Coluna do centro da habilidade
 */
void aplicarHabilidadeTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                               int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                               int centro_linha, int centro_coluna) {
    // Calcula o deslocamento para centralizar a habilidade 5x5
    int offset = TAM_HABILIDADE / 2; // 2 para matriz 5x5
    
    // Aplica a habilidade no tabuleiro
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Calcula as coordenadas no tabuleiro
            int tab_linha = centro_linha - offset + i;
            int tab_coluna = centro_coluna - offset + j;
            
            // Verifica se a posição está dentro dos limites do tabuleiro
            if (tab_linha >= 0 && tab_linha < TAM_TABULEIRO && 
                tab_coluna >= 0 && tab_coluna < TAM_TABULEIRO) {
                
                // Se a posição na matriz de habilidade for 1, marca no tabuleiro
                if (habilidade[i][j] == 1) {
                    tabuleiro[tab_linha][tab_coluna] = HABILIDADE;
                }
            }
        }
    }
}

/**
 * Exibe o tabuleiro no console
 * @param tabuleiro Matriz 10x10 representando o tabuleiro
 */
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    // Cabeçalho com índices das colunas
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Linhas do tabuleiro
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i); // Índice da linha
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}