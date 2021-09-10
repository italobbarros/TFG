#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <Arduino.h>

void chessBoardBegin(void); //Inicialização do tabuleiro com as peças na posição inicial
void getChess(char *parameter, int i); //retorna a matrix do tabuleiro preenchida
void AtualizaChessBoard(void);
void menu(void);
void createPGN(void);
void movBoard(int PosInicial, int PosFinal);
void movepeca(int PosInicial, int PosFinal);
char moveChess(void);
void auxilioJogo(void);
void tiraPeca(int PosInicial);


#endif /*CHESSBOARD_H*/