#include <stdio.h>
#include <stdbool.h>

#define BOARD 8
// Desafio de Xadrez - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de movimentação das peças de xadrez.
// O objetivo é utilizar estruturas de repetição e funções para determinar os limites de movimentação dentro do jogo.
void printBoard(int b[BOARD][BOARD]) {
    printf("\n  ");
    for (int c = 0; c < BOARD; c++) printf(" %d", c);
    printf("\n");
    for (int r = 0; r < BOARD; r++) {
        printf("%d ", r);
        for (int c = 0; c < BOARD; c++) {
            if (b[r][c] == 0) printf(" .");
            else if (b[r][c] == 9) printf(" P"); // peça (origem)
            else if (b[r][c] == 1) printf(" *"); // alcance
            else printf(" ?");
        }
        printf("\n");
    }
}

// ================================
// NÍVEL MESTRE: Movimentação Recursiva do Bispo
// Implementação de Movimentação do Bispo
// Sugestão: Utilize uma estrutura de repetição para simular a movimentação do Bispo em diagonal.
// Aqui implementamos como função recursiva que percorre em uma direção diagonal até borda.
// ================================
void exploreDiagonalRecursive(int board[BOARD][BOARD], int r, int c, int dr, int dc) {
    int nr = r + dr;
    int nc = c + dc;
    // Termina se sair do tabuleiro
    if (nr < 0 || nr >= BOARD || nc < 0 || nc >= BOARD) return;
    // Marca como alcançável
    board[nr][nc] = 1;
    // Continua recursivamente na mesma direção
    exploreDiagonalRecursive(board, nr, nc, dr, dc);
}

// ================================
// NÍVEL NOVATO: Movimentação da Torre (loops)
// Implementação de Movimentação da Torre
// Sugestão: Utilize uma estrutura de repetição para simular a movimentação da Torre para a direita (e demais direções).
// ================================
void rookMoves(int board[BOARD][BOARD], int r, int c) {
    // Direções: cima, baixo, esquerda, direita
    int drs[4] = {-1, 1, 0, 0};
    int dcs[4] = {0, 0, -1, 1};

    for (int d = 0; d < 4; d++) {
        int dr = drs[d];
        int dc = dcs[d];
        int nr = r + dr;
        int nc = c + dc;
        // percorre até borda (exemplo de uso de break)
        while (nr >= 0 && nr < BOARD && nc >= 0 && nc < BOARD) {
            board[nr][nc] = 1;
            // neste exemplo não há peças bloqueando; se houvesse, usaríamos:
            // if (occupied) break;
            nr += dr;
            nc += dc;
        }
    }
}

// ================================
// NÍVEL AVENTUREIRO: Movimentação do Cavalo (loops aninhados)
// Sugestão: Utilize loops aninhados para simular a movimentação do Cavalo em L.
// ================================
void knightMoves(int board[BOARD][BOARD], int r, int c) {
    // Todos os 8 movimentos relativos do cavalo
    int moves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    for (int i = 0; i < 8; i++) {
        int nr = r + moves[i][0];
        int nc = c + moves[i][1];
        if (nr < 0 || nr >= BOARD || nc < 0 || nc >= BOARD) continue; // exemplo de continue
        board[nr][nc] = 1;
    }
}

// ================================
// Movimentação da Rainha: combinação de rook + bishop
// Implementação de Movimentação da Rainha
// Sugestão: Utilize uma estrutura de repetição para simular a movimentação da Rainha para a esquerda (e demais direções).
// ================================
void queenMoves(int board[BOARD][BOARD], int r, int c) {
    // Rook-like moves
    rookMoves(board, r, c);
    // Bishop-like moves (diagonais)
    // usar loops em vez de recursão para variar a abordagem
    int drs[4] = {-1, -1, 1, 1};
    int dcs[4] = {-1, 1, -1, 1};
    for (int d = 0; d < 4; d++) {
        int nr = r + drs[d];
        int nc = c + dcs[d];
        while (nr >= 0 && nr < BOARD && nc >= 0 && nc < BOARD) {
            board[nr][nc] = 1;
            nr += drs[d];
            nc += dcs[d];
        }
    }
}

// Função utilitária para zerar o tabuleiro
void clearBoard(int board[BOARD][BOARD]) {
    for (int i = 0; i < BOARD; i++)
        for (int j = 0; j < BOARD; j++)
            board[i][j] = 0;
}


int main(void){
    printf("Desafio Jogo de Xadrez\n");

    // Nível Novato - Movimentação das Peças
    // Sugestão: Declare variáveis constantes para representar o número de casas que cada peça pode se mover.
    // Sugestão: Declare variáveis constantes para representar o número de casas que cada peça pode se mover.
    
    const int maxStepsBishop = BOARD - 1;
    const int maxStepsRook  = BOARD - 1;
    const int maxStepsQueen = BOARD - 1;

    int board[BOARD][BOARD];
    int r = 3, c = 3; // posição inicial exemplo (linha 3, coluna 3)

    // Implementação de Movimentação do Bispo
    // Sugestão: Utilize uma estrutura de repetição para simular a movimentação do Bispo em diagonal.
    // -------------------------
    // 1) BISPO - usando função recursiva
    // -------------------------
    clearBoard(board);
    board[r][c] = 9; // marca a peça de origem
    // Explorar as quatro diagonais recursivamente (↘ ↙ ↖ ↗)
    exploreDiagonalRecursive(board, r, c,  1,  1); // ↘
    exploreDiagonalRecursive(board, r, c,  1, -1); // ↙
    exploreDiagonalRecursive(board, r, c, -1,  1); // ↗
    exploreDiagonalRecursive(board, r, c, -1, -1); // ↖

    printf("\n-- Bispo (recursivo) partindo de (%d,%d) --", r, c);
    printBoard(board);


    // Implementação de Movimentação da Torre
    // Sugestão: Utilize uma estrutura de repetição para simular a movimentação da Torre para a direita.
    // -------------------------
    // 2) TORRE - usando loops (direita, esquerda, cima, baixo)
    // -------------------------
    clearBoard(board);
    board[r][c] = 9;
    rookMoves(board, r, c);

    printf("\n-- Torre (loops) partindo de (%d,%d) --", r, c);
    printBoard(board);

    // Implementação de Movimentação da Rainha
    // Sugestão: Utilize uma estrutura de repetição para simular a movimentação da Rainha para a esquerda.
     // -------------------------
    // 3) RAINHA - combinação (rooks + bishop)
    // -------------------------
    clearBoard(board);
    board[r][c] = 9;
    queenMoves(board, r, c);

    printf("\n-- Rainha (combinação) partindo de (%d,%d) --", r, c);
    printBoard(board);

    // Nível Aventureiro - Movimentação do Cavalo
    // Sugestão: Utilize loops aninhados para simular a movimentação do Cavalo em L.
    // Um loop pode representar a movimentação horizontal e outro vertical.
    // -------------------------
    // 4) CAVALO - loops aninhados / offsets
    // -------------------------
    clearBoard(board);
    board[r][c] = 9;
    knightMoves(board, r, c);

    printf("\n-- Cavalo (L-moves) partindo de (%d,%d) --", r, c);
    printBoard(board);

    // Nível Mestre - Funções Recursivas e Loops Aninhados
    // Sugestão: Substitua as movimentações das peças por funções recursivas.
    // Exemplo: Crie uma função recursiva para o movimento do Bispo.

    // Sugestão: Implemente a movimentação do Cavalo utilizando loops com variáveis múltiplas e condições avançadas.
    // Inclua o uso de continue e break dentro dos loops.
    printf("\nNível Mestre: Exemplo concluído (Bispo recursivo + uso de loops aninhados/continue/break).\n");

    return 0;
}
