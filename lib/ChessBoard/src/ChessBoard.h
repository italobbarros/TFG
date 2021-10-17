#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <Arduino.h>
#include <config.h>

void chessBoardBegin(void); //Inicialização do tabuleiro com as peças na posição inicial
void getChess(char *parameter, int i); //retorna a matrix do tabuleiro preenchida
void AtualizaChessBoard(void);
void menu(void);
void createPGN(int casa,bool tipo);
void movBoard(int PosInicial, int PosFinal);
void movepeca(int PosInicial, int PosFinal);
char moveChess(void);
void auxilioJogo(void);
void tiraPeca(int PosInicial);
String getPGN(void);
bool getFIM(void);

#endif /*CHESSBOARD_H*/