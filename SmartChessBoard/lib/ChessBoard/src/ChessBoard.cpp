#include "ChessBoard.h"
#include <GetBoard.h>
#include <TFT.h>
#include <stdio.h>
#include "config.h"
#include "RegrasMove.h"

int jogo[16]={e2,e4,e7,e5,g1,f3,f8,d6,d2,d4,f7,f6,f1,c4,c7,c6};
static int boardNow[64]={
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 };
int tempo = millis();
static int boardLast[64];
static int boardComp[64];
static int comeB[64],moveB[64];
bool auxilio=true;
char chessBoard[65]={
        'R','N','B','Q','K','B','N','R', 
        'P','P','P','P','P','P','P','P',
        '_','_','_','_','_','_','_','_',
        '_','_','_','_','_','_','_','_',
        '_','_','_','_','_','_','_','_',
        '_','_','_','_','_','_','_','_',
        'p','p','p','p','p','p','p','p',
        'r','n','b','q','k','b','n','r'};
int SW1Last,SW1Atual=1;
int SW2Last,SW2Atual=1;
bool jogada=0;// a branca começa
int aux1=0,aux=0,chegou,saiu=65,rodada=1; // rodada começa em 1
int saiuAntSave=66;
int y=0;
void chessBoardBegin(void){ //Inicialização do tabuleiro com as peças na posição inicial
    for(int i=0;i<64;i++){
        movepecaTFT(chessBoard[i],i); 
    }
}
void getChessBoard(void){//retorna a matrix do tabuleiro preenchida
    SW1Last = SW1Atual;
    SW2Last = SW2Atual;
    for(int i=0;i<64;i++){
        boardLast[i] = boardNow[i];
    }
    if((millis()- tempo) >200){
        SW1Atual = push1Read();
        SW2Atual = push2Read();
        tempo = millis();
    }
    //boardMapping();//atualiza a aquisição

    if(jogada==0){ //jogada das brancas
        boardNow[jogo[y]] = 0;
        if(SW1Atual != SW1Last){
            boardNow[jogo[y+1]] = 1;
            //movBoard(jogo[y],jogo[y+1]); //tirar depois dos testes
            if(moveChess()==SUCESS){
                Serial.println("Brancas");
                Serial.println("Rodada:"+String(rodada));
                Serial.println("y:"+String(y));
                jogada = 1;
                }
            else{
                Serial.println("ERROR no movimento");
            }
        }   
    }
    else if(jogada==1){ //jogada das pretas
        boardNow[jogo[y+2]] = 0;
        if(SW2Atual != SW2Last){
            Serial.println("Pretas");
            boardNow[jogo[y+3]] = 1;
            //movBoard(jogo[y+2],jogo[y+3]); //tirar depois dos testes
            if(moveChess()==SUCESS){
                Serial.println("y:"+String(y+2));
                Serial.println("_______________");
                y=y+4;
                jogada = 0;
                rodada++;
            }else{
                Serial.println("ERROR no movimento");
            }
        }
    }
    if(auxilio){
        auxilioJogo(); //função que da as sugestoes de jogadas
    }
    
    
}

void movepeca(int PosInicial, int PosFinal){
    char valaux1 = chessBoard[PosInicial];
    chessBoard[PosInicial] = '_';
    chessBoard[PosFinal] = valaux1;
}


void createPGN(void){
    
}

void auxilioJogo(void){
            for(int i=0;i<64;i++){
                //getBoard(&boardNow[i],i); //pega a matrix da aquisição
                boardComp[i]= boardNow[i] - boardLast[i];
                if(boardComp[i] == -1){ //saiu da casa
                    saiu = i;
                }
            }
    if(saiuAntSave != saiu){
            simbolCasa(saiu,1); // faz uma marcação na casa que possui a peça que ira mover
            Serial.println("chessBoard[saiu]:"+String(chessBoard[saiu]));
            Serial.println("saiu:"+String(saiu));
            RegraChess(chessBoard[saiu],saiu); // atribui a regra do xadrez e salva nos vetores comeBoard e moveBoard
               // printf("_________________________\n");
                //printf("moveB[64]=\n");
            for(int i=0;i<64;i++){
                getTest(&comeB[i],&moveB[i],i); //pega os vetores da camada anterior e atribui as variaveis criadas na biblioteca
                if((moveB[i]==1) & (boardNow[i]==0)){// onde ele pode movimentar e não possui peça
                    simbolCasa(i,2);
                    moveB[i]=0;
                }else if((comeB[i]==1) & (boardNow[i]==1)){//onde ele pode comer e possui peça

                }
            }
            saiuAntSave = saiu;
        }

}

char moveChess(void){
    aux=0;
        for(int i=0;i<64;i++){
            //getBoard(&boardNow[i],i); //pega a matrix da aquisição
            boardComp[i]= boardNow[i] - boardLast[i];
            if(boardComp[i] == 1){ //chegou na casa
                chegou = i;
                aux =+1;
            }
        }   
        if(aux==1){ //caso para movimento simples
            movepeca(saiu,chegou); // movimenta a matriz
        }
        printf("_________________________\n");
        printf("chessBoard[64]=\n");
        for (int i = 0; i < 64; i++){
            movepecaTFT(chessBoard[i],i);
            //serial
            printf("%c ,",chessBoard[i]);
                if((i+1)%8==0){
                printf("\n");
                }
        }
       return SUCESS;
}


//Parte de teste para desenvolver o pgn 
//      |
//      V
void comeBoard(int PosInicial, int PosFinal){
    boardNow[PosFinal] = boardNow[PosInicial];
    boardNow[PosInicial] = 0;
}

void movBoard(int PosInicial, int PosFinal){
    if(boardNow[PosInicial]==1){
        int valaux1 = boardNow[PosInicial];
        boardNow[PosInicial] = 0;
        boardNow[PosFinal] = valaux1;
    }
}
void tiraPeca(int PosInicial){
    if(boardNow[PosInicial]==1){
        boardNow[PosInicial] = 0;
    }
}

