#include <Arduino.h>
#include "SPI.h"
#include <Rotaryencoder.h>
#include <ChessBoard.h>
#include "connection.h"
#include <TFT.h>
#include <GetBoard.h>
#include "config.h"
#include "Interrupt.h"


static int boardNow[64];
char chessB[65];
int temp=millis();;
int menuVal=0,encAnt=0,SwAnt,SwAtual;
int val=1;


void setup(){
  Serial.begin(9600);
  InterruptBegin();
  tftbegin();
  GetBoardbegin();
  chessBoardBegin();
  SwAtual = encoderSW();

  connectWiFI();
}
void loop(){/*
  if(millis() - temp > 100){
    for(int i=0;i<64;i++){
      getChess(&chessB[i],i); //pega a matrix da aquisição
    }
    Firebase.setString("Chessboard",chessB);
  }*/
  
  /*
  SwAnt = SwAtual;
  if(menuVal==1){
    if(encAnt<getEncoder()){
      menuVal=2;
    }
    printTextTFT1("Xadrez",160,240);
    SwAtual = encoderSW();
    if(SwAnt > SwAtual){
      Serial.println("enc: "+ String(encoderSW()));
      delay(1000);
      chessBoardBegin();
      menuVal=0;
    }
  }*/
  /*
  boardMapping();//atualiza a aquisição
  for(int i=0;i<64;i++){
      getBoard(&boardNow[i],i); //pega a matrix da aquisição
      if(boardNow[i]==1){
        movepecaTFT('p',i);
      }else{
        movepecaTFT('_',i);   
      }
  }
  //serial
  printf("_________________________\n");
  printf("board[64]=\n");
  for(int i=0;i<64;i++){
  printf("%d ,",boardNow[i]);
    if((i+1)%8==0){
    printf("\n");
    }
  }
  delay(1000);*/
  if(menuVal==0){
    AtualizaChessBoard();
  }
  if(getFIM()){
    sendPGN();
  }
}




/*
    boardMapping();//atualiza a aquisição
  for(int i=0;i<64;i++){
      getBoard(&boardNow[i],i); //pega a matrix da aquisição
      if(boardNow[i]==1){
        movepecaTFT('p',i);
      }else{
        movepecaTFT('_',i);   
      }
  }
  //serial
  printf("_________________________\n");
  printf("board[64]=\n");
  for(int i=0;i<64;i++){
  printf("%d ,",boardNow[i]);
    if((i+1)%8==0){
    printf("\n");
    }
  }*/

  /*
//Serial.println("encoder: " + String(getEncoder()));
  if (getEncoder() > menuAnt){
    if(val!=2){
      printTextTFT1("Xadrez pensado","Xadrez rapido",160,240);
      val =2;
    }
    menuAnt = getEncoder();
  }else if(getEncoder() < menuAnt){
    if (val!=1){
      printTextTFT2("Xadrez rapido","Xadrez pensado",160,240);
      val = 1;
    }
    menuAnt = getEncoder();
  }

*/
