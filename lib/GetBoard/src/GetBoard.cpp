#include "GetBoard.h"
#include "Pins.h"
#include "Rotaryencoder.h"
#include "config.h"


bool board[64];
int enc;
static bool s0,s1,s2,s3;
int sw1,sw2;
static int selectMux;    
//Função que faz a inicialização, configurando as
// portas do micro para output ou input
void GetBoardbegin(void){
    //configura os pinos de saída do mux como entrada no esp32
    pinMode(pinMux1,INPUT_PULLDOWN);
    pinMode(pinMux2,INPUT_PULLDOWN);
    pinMode(pinMux3,INPUT_PULLDOWN);
    pinMode(pinMux4,INPUT_PULLDOWN);

    //configura os pinos de seleção do mux como saída no esp32
    pinMode(pinMux_S0,OUTPUT);
    pinMode(pinMux_S1,OUTPUT);
    pinMode(pinMux_S2,OUTPUT);
    pinMode(pinMux_S3,OUTPUT);

    //configura o init do encoder	
    encoderInit(pinCLK, pinDT);
    pinMode(pinSW,INPUT_PULLUP);

    //configura os pinos dos botões
    pinMode(pinPUSH1,INPUT);
    pinMode(pinPUSH2,INPUT);

    
    //configura o pino do buzzer	
    //pinMode(pinBuzzer,OUTPUT);

    //attachInterrupt(pinCLK, encoderRead_isr, RISING);

    for(int i=0;i<64;i++){
        board[i] =0;
    }
}
void printboard(int casas){
   
    int cal=5;
        int cal0=( cal)%2;   
        int cal1=(( cal)/2)%2;
        int cal2=(( cal)/4)%2;
        int cal3=(( cal)/8);
        /*printf("s0 %d\n",cal0);
        printf("s1 %d\n",cal1);
        printf("s2 %d\n",cal2);
        printf("s3 %d\n",cal3);
        printf("________\n");*/
    digitalWrite(pinMux_S0, cal0); //SETA se o s0 esta em 0 ou 1
    digitalWrite(pinMux_S1, cal1); //SETA se o s1 esta em 0 ou 1
    digitalWrite(pinMux_S2, cal2); //SETA se o s2 esta em 0 ou 1
    digitalWrite(pinMux_S3, cal3); //SETA se o s3 esta em 0 ou 1
    muxMapping (cal);
      
      /*
    printf("_________________________\n");
  printf("board[64]=\n");
  for(int i=0;i<casas;i++){
  printf("%d ,",board[i]);
    if((i+1)%8==0){
    printf("\n");
    }
  }*/
}
//Função que faz o mapeamento do mux em relação a 
//chave de seleção
void muxMapping(int selectCanal){
    switch (selectCanal){ //variável que representa o select do mux
        case 0:
            muxRead(h8,h6,h4,h2); // leitura da primeira casa de todos os mux ao mesmo tempo -> CANAL0
            break;
        case 1:
            muxRead(g8,g6,g4,g2); // leitura da segunda casa de todos os mux ao mesmo tempo -> CANAL1
            break;
        case 2:
            muxRead(f8,f6,f4,f2); // leitura da terceira casa de todos os mux ao mesmo tempo -> CANAL2
            break;
        case 3:
            muxRead(e8,e6,e4,e2); // leitura da quarta casa de todos os mux ao mesmo tempo -> CANAL3            
            break;
        case 4:
            muxRead(d8,d6,d4,d2); // leitura da quinta casa de todos os mux ao mesmo tempo -> CANAL4             
            break;
        case 5:        
            muxRead(c8,c6,c4,c2); // leitura da sexta casa de todos os mux ao mesmo tempo -> CANAL5             
            break;
        case 6:
            muxRead(b8,b6,b4,b2); // leitura da sétima casa de todos os mux ao mesmo tempo -> CANAL6             
            break;
        case 7:
            muxRead(a8,a6,a4,a2); // leitura da oitava casa de todos os mux ao mesmo tempo -> CANAL7             
            break;
        case 8:
            muxRead(a7,a5,a3,a1); // leitura da nona casa de todos os mux ao mesmo tempo -> CANAL8             
            break;
        case 9:
            muxRead(b7,b5,b3,b1); // leitura da décima casa de todos os mux ao mesmo tempo -> CANAL9             
            break;
        case 10:
            muxRead(c7,c5,c3,c1); // leitura da décima primera casa de todos os mux ao mesmo tempo -> CANAL10             
            break;
        case 11:
            muxRead(d7,d5,d3,d1); // leitura da décima segunda casa de todos os mux ao mesmo tempo -> CANAL11             
            break;
        case 12:
            muxRead(e7,e5,e3,e1); // leitura da décima terceira casa de todos os mux ao mesmo tempo -> CANAL12            
            break;
        case 13:
            muxRead(f7,f5,f3,f1); // leitura da décima quarta casa de todos os mux ao mesmo tempo -> CANAL13            
            break;
        case 14:
            muxRead(g7,g5,g3,g1); // leitura da décima quinta casa de todos os mux ao mesmo tempo -> CANAL14            
            break;
        default:
            muxRead(h7,h5,h3,h1); // leitura da décima sexta casa de todos os mux ao mesmo tempo -> CANAL             
            break;
    }
}

//Função que executa a leitura das 4 saídas dos  
//4 mux ao mesmo tempo para um indice em comum
//e salva no vetor board
void muxRead(int a, int b, int c, int d){
    board[a]= digitalRead(pinMux1);        /* Leitura da casa do mux 1 no buffer em sua respectiva posição a*/
    board[b]= digitalRead(pinMux2);        /* Leitura da casa do mux 2 no buffer em sua respectiva posição b*/
    board[c]= digitalRead(pinMux3);        /* Leitura da casa do mux 3 no buffer em sua respectiva posição c*/
    board[d]= digitalRead(pinMux4);        /* Leitura da casa do mux 4 no buffer em sua respectiva posição d*/
}

//Função que percorre todo o tabuleiro
void boardMapping(void){
    for(selectMux=0;selectMux<16;selectMux++){
        // converte o calor do select inteiro em variáveis booleanas para cada select do mux
        s0=(selectMux)%2;   
        s1=((selectMux)/2)%2;
        s2=((selectMux)/4)%2;
        s3=((selectMux)/8);
        digitalWrite(pinMux_S0,s0); //SETA se o s0 esta em 0 ou 1
        digitalWrite(pinMux_S1,s1); //SETA se o s1 esta em 0 ou 1
        digitalWrite(pinMux_S2,s2); //SETA se o s2 esta em 0 ou 1
        digitalWrite(pinMux_S3,s3); //SETA se o s3 esta em 0 ou 1
        
        /*chama a função que irá necessariamente fazer o mapeamento do tabuleiro
        já anexando no vetor board a casa na sua posição correta.
        */
        delay(1);
        muxMapping(selectMux);
    }
}
void getBoard(bool *parameter, int i){
    bool b = board[i];
    *parameter = b;
}


void buzzerActive(bool buzzer){
    digitalWrite(pinBuzzer,buzzer);
}
void IRAM_ATTR encoderRead_isr(){/* Código de tratamento da interrupção do encoder */
    enc = mappingEncoder(pinCLK, pinDT,100);
    Serial.println("encoder: " + String(enc));
}
int getEncoder(void){
    return mappingEncoder(pinCLK, pinDT,100);
}

int encoderSW(void){
    return digitalRead(pinSW);
}

void IRAM_ATTR botao1(){

}