#include "Interrupt.h"
#include "Pins.h"

unsigned long tempo_fim = 0, tempo_fim2 = 0;
#define Tempo_total 3000
int auxilia;
bool Fim, botao1, botao2;

void InterruptBegin(){
  Fim=LOW,tempo_fim = 0, tempo_fim2 = 0;
  botao1=HIGH, botao2=HIGH;
  auxilia=0;    
  //configura os pinos dos botões
  pinMode(pinPUSH1,INPUT);
  pinMode(pinPUSH2,INPUT);

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
bool  push1Read(void){
  return digitalRead(pinPUSH1);
}

bool push2Read(void){
  return digitalRead(pinPUSH2);//precisa retorar o botao2
}

void AtualizaButton1(void){
  if(tempo_fim == 0){
    tempo_fim = millis();
  }else if(((millis() - tempo_fim) > Tempo_total) && (!digitalRead(pinPUSH1))){
    Fim = true;
  }else if(digitalRead(pinPUSH1)){
    tempo_fim = millis();
  }

}
void AtualizaButton2(void){
  if(tempo_fim2 == 0){
    tempo_fim2 = millis();
  }else if(((millis() - tempo_fim2) > Tempo_total) && (!digitalRead(pinPUSH2))){
    Fim = true;
  }else if(digitalRead(pinPUSH2)){
    tempo_fim2 = millis();
  }
}