#include "Interrupt.h"
#include "Pins.h"

unsigned long tempo_fim = 0, tempo_fim2 = 0;
#define Tempo_total 3000

bool Fim=0, botao1, botao2;

void InterruptBegin()
{
  botao1=HIGH, botao2=HIGH;    
      //configura os pinos dos botões
  pinMode(pinPUSH1,INPUT);
  pinMode(pinPUSH2,INPUT);

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
  if (tempo_fim == 0){
    tempo_fim = millis(); //Apertou
    botao1 = LOW;
    Serial.println("botao1= "+ String(push1Read()));
  }
  else{ //soltou
    if ((millis() - tempo_fim) > Tempo_total){
      tempo_fim = 0;
      Fim = true;
      botao1 = HIGH;
      Serial.println("botao1= "+ String(push1Read()));
    }
    else if((millis() - tempo_fim) > 100){
      tempo_fim = 0;
      botao1 = HIGH;
      Serial.println("botao1= "+ String(push1Read()));
    }
  }
}
void IRAM_ATTR botaoPlayer2(void){
  if (tempo_fim2 == 0){
    tempo_fim2 = millis(); //Apertou
    botao2 = LOW;
    Serial.println("botao2= "+ String(push2Read()));
  }
  else{ //soltou
    if ((millis() - tempo_fim2) > Tempo_total){
      tempo_fim2 = 0;
      Fim = true;
      botao2 = HIGH;
      Serial.println("botao2= "+ String(push2Read()));
    }
    else if((millis() - tempo_fim2) > 100){
      tempo_fim2 = 0;
      botao2 = HIGH;
      Serial.println("botao2= "+ String(push2Read()));
    }
    
  }
}

bool  push1Read(void){
    return botao1;//precisa retorar o botao1 da interrupção
}

bool push2Read(void){
    return botao2;//precisa retorar o botao2
}