#include "TFT.h"
#include "TFT_eSPI.h"



TFT_eSPI tft = TFT_eSPI(); 

void tftbegin(void){
    tft.init();
    tft.setRotation(rotationTFT);	// landscape
    tft.fillScreen(TFT_WHITE);
    tft.setSwapBytes(true);
    tft.fillScreen(TFT_BLACK);
    for(int i=0;i<8;i++){   //linha
        for(int j=0;j<8;j++){ //coluna
            if((i%2)){
                if(j%2){
                tft.pushImage(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, casabranca);
                }else{
                tft.pushImage(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, casapreta);
                }
            }else{
                if(j%2){
                tft.pushImage(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, casapreta);
                }else{
                tft.pushImage(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, casabranca);  
                }
            }
        }
    }
}

void setaCasa(int casa, const uint16_t *arrayBranca, const uint16_t *arrayPreta){
  int i,j;
  //decodificaçÃo de qual casa era a anterior
    if(casa<8){ //primeira casa é i=0,j=0
      i=0; j= casa; //primeira linha so muda a coluna
    }else if((casa>=8) & (casa<16)){
      i=1; j= casa-(8*1); //segunda linha so muda a coluna
    }else if((casa>=16) & (casa<24)){
      i=2; j= casa-(8*2); //terceira linha so muda a coluna
    }else if((casa>=24) & (casa<32)){
      i=3; j= casa-(8*3); //quarta linha so muda a coluna
    }else if((casa>=32) & (casa<40)){
      i=4; j= casa-(8*4); //quinta linha so muda a coluna
    }else if((casa>=40) & (casa<48)){
      i=5; j= casa-(8*5);
    }else if((casa>=48) & (casa<56)){
      i=6; j= casa-(8*6);
    }else if((casa>=56) & (casa<64)){
      i=7; j= casa-(8*7);
    } 
    //a partir dos parametros de i,j é pintado a casa especifica     
    if((i%2)){
      if(j%2){
        tft.pushImage(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, arrayBranca);
      }else{
        tft.pushImage(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, arrayPreta);
      }
    }else{
      if(j%2){
        tft.pushImage(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, arrayPreta);
      }else{
        tft.pushImage(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, arrayBranca);  
      }
    }
}
void simbolCasa(int casa,int tipo){
  int i,j;
  //decodificaçÃo de qual casa era a anterior
    if(casa<8){ //primeira casa é i=0,j=0
      i=0; j= casa; //primeira linha so muda a coluna
    }else if((casa>=8) & (casa<16)){
      i=1; j= casa-(8*1); //segunda linha so muda a coluna
    }else if((casa>=16) & (casa<24)){
      i=2; j= casa-(8*2); //terceira linha so muda a coluna
    }else if((casa>=24) & (casa<32)){
      i=3; j= casa-(8*3); //quarta linha so muda a coluna
    }else if((casa>=32) & (casa<40)){
      i=4; j= casa-(8*4); //quinta linha so muda a coluna
    }else if((casa>=40) & (casa<48)){
      i=5; j= casa-(8*5);
    }else if((casa>=48) & (casa<56)){
      i=6; j= casa-(8*6);
    }else if((casa>=56) & (casa<64)){
      i=7; j= casa-(8*7);
    } 
      //a partir dos parametros de i,j é pintado a casa especifica  
      if(tipo==1){
        if((i%2)){
          if (j % 2){ //peça escolhida
            tft.drawRect(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, TFT_RED);
            tft.drawRect((offsetX+1)+(j*casaWidth), (offsetY+1)+(i*casaHeight), casaWidth-2, casaHeight-2, TFT_RED);
          }
          else{
            tft.drawRect(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, TFT_RED);
            tft.drawRect((offsetX+1)+(j*casaWidth), (offsetY+1)+(i*casaHeight), casaWidth-2, casaHeight-2, TFT_RED);
          }
        }
        else{
          if (j % 2){
            tft.drawRect(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, TFT_RED);
            tft.drawRect((offsetX+1)+(j*casaWidth), (offsetY+1)+(i*casaHeight), casaWidth-2, casaHeight-2, TFT_RED);
          }
          else{
            tft.drawRect(offsetX+j*casaWidth, offsetY+i*casaHeight, casaWidth, casaHeight, TFT_RED);
            tft.drawRect((offsetX+1)+(j*casaWidth), (offsetY+1)+(i*casaHeight), casaWidth-2, casaHeight-2, TFT_RED);
          }
        }
      }else if(tipo==2){ // posição para a qual vai movimentar
        if((i%2)){
          if (j % 2){
            tft.fillCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth, raio, TFT_RED); 
          }
          else{
            tft.fillCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth, raio, TFT_RED);
          }
        }
        else{
          if (j % 2){
            tft.fillCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth, raio, TFT_RED);
          }
          else{
            tft.fillCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth, raio, TFT_RED);
          }
        }
      }else if(tipo==3){ // posição para a qual vai atacar
        if((i%2)){
          if (j % 2){
            tft.drawCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth,raio1, TFT_RED);
            tft.drawCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth,raio1-4, TFT_RED);
          }
          else{
            tft.drawCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth,raio1, TFT_RED);
            tft.drawCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth,raio1-4, TFT_RED);
          }
        }
        else{
          if (j % 2){
            tft.drawCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth,raio1, TFT_RED);
            tft.drawCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth,raio1-4, TFT_RED);

          }
          else{
            tft.drawCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth,raio1, TFT_RED);
            tft.drawCircle(offsetX+(casaWidth/2)+(j*casaWidth), offsetY+(casaWidth/2)+ i*casaWidth,raio1-4, TFT_RED);
          }
        }
      }   
      
}
void movepecaTFT(char peca,int casaAtual){
  switch (peca){
    default:
      setaCasa(casaAtual,casabranca,casapreta);
      break;
    //branco
    case 'p': //piao p
      setaCasa(casaAtual,piaobranco_FB,piaobranco_FP);
      break;
    case 'b': //bispo
      setaCasa(casaAtual,bispobranco_FB,bispobranco_FP);
      break;
    case 'r': //rook
      setaCasa(casaAtual,torrebranca_FB,torrebranca_FP);
      break;
    case 'q': //rainha
      setaCasa(casaAtual,rainhabranca_FB,rainhabranca_FP);
      break;  
    case 'k': //king
      setaCasa(casaAtual,reibranco_FB,reibranco_FP);
      break;
    case 'n'://cavalo 
      setaCasa(casaAtual,cavalobranco_FB,cavalobranco_FP);
      break;
    
    //preto  
    case 'P': //piao P
      setaCasa(casaAtual,piaopreto_FB,piaopreto_FP);
      break;
    case 'B': //bispo
      setaCasa(casaAtual,bispopreto_FB,bispopreto_FP);
      break;
    case 'R': //rook
      setaCasa(casaAtual,torrepreta_FB,torrepreta_FP);
      break;
    case 'Q': //rainha
      setaCasa(casaAtual,rainhapreta_FB,rainhapreta_FP);
      break;  
    case 'K': //king
      setaCasa(casaAtual,reipreto_FB,reipreto_FP);
      break;
    case 'N'://cavalo 
      setaCasa(casaAtual,cavalopreto_FB,cavalopreto_FP);
      break; 
  }
}

void auxTFT(int casaAtual,int casaSetada){
  simbolCasa(casaAtual,0);

}

void fbPlayerTFT(int x, int y){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(TL_DATUM);
  tft.setTextPadding(0); // Setting to zero switches off padding
  tft.drawString("Jogo rapido", x, y, 4);
}
void textErrorTFT(const char *stringAtual,int x, int y){
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE,TFT_RED);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(stringAtual, x, y, 4);
}

void printTextTFT1(const char *stringAtual,int x, int y){
  tft.fillRoundRect(0,y-35,320,100,20,TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(stringAtual, x, y, 4);
}

void printTextTFT2(const char *stringAtual,const char *stringAnterior,int x, int y){
  tft.fillRoundRect(0,y-35,320,100,20,TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextDatum(TC_DATUM);
  if(stringAnterior!="nada"){
    for (int i = 0; i < 320; i=i+1){
    //tft.fillRoundRect(0,y,i+160,30,0,TFT_BLACK);
    tft.drawString(stringAnterior, x+i+1, y, 4);
    }
  }
  for (int i = 0; i<160; i=i+1){
    //tft.fillRoundRect(0,y,320,30,0,TFT_BLACK);
    tft.drawString(stringAtual, i, y, 4);
  }
}

//codigo da espadinha
/*
            tft.fillTriangle(25 + j * 38, 98 + i * 38, 27 + j * 38, 92 + i * 38, 29 + j * 38, 98 + i * 38,  TFT_RED);//ponta
            tft.fillRect(25 + j * 38,98 + i * 38,5,16,TFT_RED);// parte maior
            tft.fillRect(20 + j * 38,114 + i * 38,15,4,TFT_RED);//parte horizontal
            tft.fillRect(26 + j * 38,118 + i * 38,3,7,TFT_RED);//cabo
            tft.fillCircle(27 + j * 38,125 + i * 38,2,TFT_RED);//bola do cabo
*/