#include "Interrupt.h"
#include "Pins.h"

unsigned long tempo_fim = 0, tempo_fim2 = 0;
#define Tempo_total 3000

bool Fim, botao1=HIGH, botao2=HIGH;

void InterruptBegin()
{
  attachInterrupt(pinPUSH1, botaoPlayer1, CHANGE);
  attachInterrupt(pinPUSH2, botaoPlayer2, CHANGE);
}

bool getFim(void)
{
  if (Fim)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void IRAM_ATTR botaoPlayer1(void)
{
  if (tempo_fim == 0)
  {
    tempo_fim = millis(); //Apertou
    botao1 = LOW;
    ////serial.println("Botão do Reset pressionado!");
  }
  else
  { //soltou
    if ((millis() - tempo_fim) > Tempo_total)
    {
      tempo_fim = 0;
      Fim = true;

    }
    else
    {
      tempo_fim = 0;
      botao1 = HIGH;

    }
  }
}
void IRAM_ATTR botaoPlayer2(void)
{
  if (tempo_fim2 == 0)
  {
    tempo_fim2 = millis(); //Apertou
    botao2 = LOW;
  }
  else
  { //soltou
    if ((millis() - tempo_fim2) > Tempo_total)
    {
      tempo_fim2 = 0;
      Fim = true;

    }
    else
    {
      tempo_fim2 = 0;
      botao2 = HIGH;

    }
  }
}

bool  push1Read(void){
    
    return botao1;//precisa retorar o botao1 da interrupção
}

bool push2Read(void){
    return botao2;//precisa retorar o botao2
}