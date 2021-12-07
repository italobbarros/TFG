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

  //attachInterrupt(pinPUSH1, botaoPlayer1, CHANGE);
  //attachInterrupt(pinPUSH2, botaoPlayer2, CHANGE);
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
void IRAM_ATTR botaoPlayer1(void){
  if (tempo_fim == 0){
    tempo_fim = millis(); //Apertou
    botao1 = LOW;
    Serial.println("botao1= "+ String(push1Read())+" apertou");
  }
  else{ //soltou
    if ((millis() - tempo_fim) > Tempo_total){
      tempo_fim = 0;
      Fim = true;
      botao1 = HIGH;
      Serial.println("botao1= "+ String(push1Read())+"soltou");
    }
    else if((millis() - tempo_fim) > 500){
      tempo_fim = 0;
      botao1 = HIGH;
      Serial.println("botao1= "+ String(push1Read())+"soltou");
    }
  }
}
void IRAM_ATTR botaoPlayer2(void){
  if(tempo_fim2 == 0){
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