#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <Arduino.h>
#include <config.h>

void chessBoardBegin(void); //Inicialização do tabuleiro com as peças na posição inicial

/**
 * @brief atribui a variável parameter a matrix do tabuleiro
 * 
 * @param parameter é o endereço da variavel que você deve passar para receber os caracteres referentes as casas dos tabuleiros
 * @param i é o indice que representa cada casa de tabuleiro
 */
void getChess(char *parameter, int i); 

/**
 * @brief Função que checa se as peças do tabuleiro foram colocadas corretamente
 * 
 * @return char 
 */
char checkBoard(void);
void AtualizaChessBoard(void);
void menu(void);
void createPGN(int casaAnt,int casa,bool tipo);
void movBoard(int PosInicial, int PosFinal);
void movepeca(int PosInicial, int PosFinal);
char moveChess(void);
void auxilioJogo(void);
void tiraPeca(int PosInicial);
String getPGN(void);
bool getFIM(void);



#endif /*CHESSBOARD_H*/