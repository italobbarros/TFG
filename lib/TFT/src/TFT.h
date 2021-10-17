#ifndef TFT_H
#define TFT_H
#include <Arduino.h>
#include "config.h"

//#define chessThimotti 1
#define chessItalo 1


/**
 * @param casaWidth valor da largura da casa
 * @param casaHeight valor da altura da casa
 * @param offsetX distancia da borda da tela ate a primeira casa em relação ao X
 * @param offsetY distancia da borda da tela ate a primeira casa em relação ao Y
 * @param raio é o raio do circulo preenchido definido para as casas que podem ser movimentadas
 * @param raio1 é o raio do circulo que irá identificar as casas que podem ser comidas  
 */
#ifdef chessThimotti
    #define casaWidth 30
    #define casaHeight 30
    #define offsetX 0
    #define offsetY 40
    #define raio 5
    #define raio1 19
#endif

#ifdef chessItalo
    #define casaWidth 38
    #define casaHeight 38
    #define offsetX 8
    #define offsetY 92
    #define raio 5
    #define raio1 19
#endif


/**
 * @param casa é o indice da casa que irá ser escolhida de 0 a 63
 * @param arrayBranca é o array da respectiva peça com fundo branco
 * @param arrayPreto é o array da respectiva peça com fundo preto
 */
void setaCasa(int casa, const uint16_t *arrayBranca, const uint16_t *arrayPreta);

/**
 * @param casa é o indice da casa que irá ser escolhida de 0 a 63
 * @param tipo é o valor que representa o simbolo que será utilizado (1=escolhida,2=movimento,3=comer)
 */
void simbolCasa(int casa,int tipo);

/**
 * @param peca parametro que recebe um char(que representa a peça)
 * @param casaAtual é o indice da casa que irá ser escolhida de 0 a 63
 */
void movepecaTFT(char peca,int casaAtual);
void tftbegin(void);
void fbPlayerTFT(int x, int y);
void printTextTFT1(const char *stringAtual,int x, int y);
void printTextTFT2(const char *stringAtual,const char *stringAnterior,int x, int y);

#endif /*TFT_H*/