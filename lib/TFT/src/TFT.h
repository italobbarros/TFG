#ifndef TFT_H
#define TFT_H
#include <Arduino.h>
#include "config.h"

#define chessThimotti 
//#define chessItalo 


#ifdef chessItalo
    #include "pecas1.h"
#endif

#ifdef chessThimotti
    #include "pecas2.h"
#endif

/**
 * @param casaWidth valor da largura da casa
 * @param casaHeight valor da altura da casa
 * @param offsetX distancia da borda da tela ate a primeira casa em relação ao X
 * @param offsetY distancia da borda da tela ate a primeira casa em relação ao Y
 * @param raio é o raio do circulo preenchido definido para as casas que podem ser movimentadas
 * @param raio1 é o raio do circulo que irá identificar as casas que podem ser comidas  
 */



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
void textErrorTFT(const char *stringAtual,int x, int y);
void printTextTFT1(const char *stringAtual,int x, int y);
void printTextTFT2(const char *stringAtual,const char *stringAnterior,int x, int y);

#endif /*TFT_H*/