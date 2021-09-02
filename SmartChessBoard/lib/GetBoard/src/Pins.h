#ifndef _PINS_H_
#define _PINS_H_

#include "Arduino.h"

  //declaração dos pinos de saída do mux no micro
  #define pinMux1 18 
  #define pinMux2 5
  #define pinMux3 32
  #define pinMux4 33

  //declaração dos pinos de select do mux no micro
  #define pinMux_S0 19
  #define pinMux_S1 21
  #define pinMux_S2 27
  #define pinMux_S3 13 
/*
  //declaração dos pinos utilizados na tela
  #define TFT_MISO 12 //depois tenho que tirar pois nao ta conectado
  #define TFT_MOSI 23
  #define TFT_SCLK 22 //deveria ser 18 ou 14
  #define TFT_CS   15  // Chip select control pin
  #define TFT_DC    25  // Data Command control pin
  #define TFT_RST   26  // Reset pin (could connect to RST pin)
  */

  //declaração dos pinos utilizados no encoder          
  #define pinDT 34
  #define pinSW 35
  #define pinCLK 4 

  //declaração dos pinos utilizados nos botões
  #define pinPUSH1 16 //pino RX2
  #define pinPUSH2 17 //pino TX2

  //declaração do pino utilizado no buzzer
  #define pinBuzzer 2 

#endif /*_PINS_H_*/