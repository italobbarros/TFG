#ifndef TFT_H
#define TFT_H
#include <Arduino.h>

void setaCasa(int casa, const uint16_t *arrayBranca, const uint16_t *arrayPreta);
void simbolCasa(int casa,int tipo);
void movepecaTFT(char peca,int casaAtual);
void tftbegin(void);
void fbPlayerTFT(int x, int y);
void printTextTFT1(const char *stringAtual,int x, int y);
void printTextTFT2(const char *stringAtual,const char *stringAnterior,int x, int y);

#endif /*TFT_H*/