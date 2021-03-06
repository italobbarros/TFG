#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <Arduino.h>
#include "config.h"

enum peca{
    BRANCAS=0,
    PRETAS=1
};


bool chessBoardBegin(void); //Inicialização do tabuleiro com as peças na posição inicial

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
bool checkBoard(void);
void AtualizaChessBoard(void);
void excluiMovDiagonal(int k, int saiu, int i);
void excluiMovHorVertical(int k, int saiu, int i);
void testeMovimento(char peca,int saiu,int i);
void createPGN(int casaAnt,int casa,bool tipo);
void movBoard(int PosInicial, int PosFinal);
void movepeca(int PosInicial, int PosFinal);
char moveChess(void);
void auxilioJogo(void);
void tiraPeca(int PosInicial);
String getPGN(void);

void pecaNaFrente(peca tipo);

String tempoPretas(bool vez);
String tempoBrancas(bool vez);
void StopTime(void);
String getTempo(bool tipo);
bool timeOut(void);
#endif /*CHESSBOARD_H*/