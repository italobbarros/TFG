#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "Arduino.h"

void InterruptBegin();
void Interrupt();
void IRAM_ATTR botaoPlayer1(void);
void IRAM_ATTR botaoPlayer2(void);
bool getFim(void);
bool push1Read(void);
bool push2Read(void);

#endif /*INTERRUPT_H*/