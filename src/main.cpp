#include <Arduino.h>
#include "SPI.h"
#include <Rotaryencoder.h>
#include <ChessBoard.h>
#include "connection.h"
#include <TFT.h>
#include <GetBoard.h>
#include "config.h"
#include "Interrupt.h"


static bool boardNow[64];
int temp=millis();;
int state=0,encAnt=0,SwAnt,SwAtual;
int val=1;



void setup(){
  Serial.begin(115200);
  InterruptBegin();
  tftbegin();
  GetBoardbegin();
  if(chessBoardBegin()==FAILED){
    state=0;
    Serial.println("ERROR!!!");
  }else{
    state=1;
    SwAtual = encoderSW();
    connectWiFI();
  }

}

char randomChess(int val){
switch (val){
    default:
      return '_';
      break;
    //branco
    case 1: //piao p
      return 'p';
          break;
    case 2: //bispo
      return 'b';

      break;
    case 3: //rook
      return 'r';

      break;
    case 4: //rainha
      return 'q';

      break;  
    case 5: //king
    return 'k';
        break;

    case 6://cavalo 
      return 'n';
      break;
    
    //preto  
    case 7: //piao P
      return 'P';
        break;
    case 8: //bispo
      return 'B';
          break;
    case 9: //rook
      return 'R';
          break;
    case 10: //rainha
      return 'Q';

      break;  
    case 11: //king
      return 'K';
      
      break;
    case 12://cavalo 
      return 'N';
      break; 
  }
}


void loop(){
  //movepecaTFT(randomChess(random(0,12)),random(0,64)); 
  //tftTest();
  fpsView();
  switch (state){
    case 0:
      if(chessBoardBegin()==SUCESS){
        SwAtual = encoderSW();
        connectWiFI();
        state=1;
      }else{
        state=3;
      }
      delay(1000);
      break;
    case 1:
      AtualizaChessBoard();
      AtualizaButton1();
      AtualizaButton2();
      if(getFim()){
        sendPGN();
        Serial.println("Enviando PGN!");
        textTFT("Enviando PGN!",heightTFT/2 + 20,widthTFT/2,Good);
        delay(5000);
        ESP.restart();
      }
      break;

    default:
      boardMapping();//atualiza a aquisição
      for(int i=0;i<64;i++){
          getBoard(&boardNow[i],i); //pega a matrix da aquisição
          if(boardNow[i]==1){
            movepecaTFT('p',i);
          }else{
            movepecaTFT('_',i);   
          }
      }
      state=0;
      delay(1000);
      break;
  }
}


/*
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
