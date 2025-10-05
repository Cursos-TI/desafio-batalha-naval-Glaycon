#include <stdio.h>

// Constantes para o tabuleiro e elementos do jogo
#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
    }
    printf("\n");
    printf("-------------------------\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d |", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            switch (tabuleiro[i][j]) {
                case AGUA:
                    printf(" ~");
                    break;
                case NAVIO:
                    printf(" N");
                    break;
                case HABILIDADE:
                    printf(" *");
                    break;
                default:
                    printf(" %d", tabuleiro[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Função para posicionar os navios iniciais
void posicionarNavios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Navio Horizontal (tamanho 3)
    tabuleiro[1][1] = NAVIO;
    tabuleiro[1][2] = NAVIO;
    tabuleiro[1][3] = NAVIO;

    // Navio Vertical (tamanho 3)
    tabuleiro[3][5] = NAVIO;
    tabuleiro[4][5] = NAVIO;
    tabuleiro[5][5] = NAVIO;

    // Navio Diagonal 1 (tamanho 3)
    tabuleiro[7][1] = NAVIO;
    tabuleiro[8][2] = NAVIO;
    tabuleiro[9][3] = NAVIO;
    
    // Navio Diagonal 2 (tamanho 3)
    tabuleiro[2][8] = NAVIO;
    tabuleiro[3][7] = NAVIO;
    tabuleiro[4][6] = NAVIO;
}

// Cria a matriz de habilidade em formato de Cone
void criarHabilidadeCone(int habilidade[5][5]) {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            // A condição define o formato de um cone que se expande para baixo
            if (j >= 2 - i && j <= 2 + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cria a matriz de habilidade em formato de Cruz
void criarHabilidadeCruz(int habilidade[5][5]) {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            // A condição preenche a linha e a coluna central
            if (i == 2 || j == 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cria a matriz de habilidade em formato de Octaedro (Losango)
void criarHabilidadeOctaedro(int habilidade[5][5]) {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            // A condição define a forma de um losango
            if (j >= 2 - i && j <= 2 + i && i <= 2) { // Parte de cima
                 habilidade[i][j] = 1;
            } else if (j >= i - 2 && j <= 6 - i && i > 2) { // Parte de baixo
                 habilidade[i][j] = 1;
            } else {
                 habilidade[i][j] = 0;
            }
        }
    }
}


// Sobrepõe a matriz de habilidade no tabuleiro principal
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[5][5], int linhaOrigem, int colunaOrigem) {
    int tamanhoHabilidade = 5;
    int offset = tamanhoHabilidade / 2;

    for (int i = 0; i < tamanhoHabilidade; i++) {
        for (int j = 0; j < tamanhoHabilidade; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = linhaOrigem - offset + i;
                int colunaTab = colunaOrigem - offset + j;

                // Verifica se a posição está dentro dos limites do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAMANHO_TABULEIRO && colunaTab >= 0 && colunaTab < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linhaTab][colunaTab] == AGUA) {
                         tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                    }
                }
            }
        }
    }
}


int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Matrizes para as habilidades
    int habilidadeCone[5][5];
    int habilidadeCruz[5][5];
    int habilidadeOctaedro[5][5];

    // Inicialização
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    printf("Tabuleiro Inicial com Navios:\n");
    exibirTabuleiro(tabuleiro);
    
    // Gerar e aplicar as habilidades
    criarHabilidadeCone(habilidadeCone);
    aplicarHabilidade(tabuleiro, habilidadeCone, 2, 2);

    criarHabilidadeCruz(habilidadeCruz);
    aplicarHabilidade(tabuleiro, habilidadeCruz, 8, 8);
    
    criarHabilidadeOctaedro(habilidadeOctaedro);
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 5, 5);


    printf("Tabuleiro Final com Habilidades Especiais:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}