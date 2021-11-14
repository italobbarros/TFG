#include "ChessBoard.h"
#include <GetBoard.h>
#include <TFT.h>
#include <stdio.h>
#include "config.h"
#include "RegrasMove.h"
#include <Ticker.h>	 //Biblioteca para gerar eventos de tempo (ticker)
#include "Interrupt.h"

int jogo[16]={e2,e4,e7,e5,g1,f3,f8,d6,d2,d4,f7,f6,f1,c4,c7,c6};
static bool boardNow[64]={
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 };

static bool referencia[64]={
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,
  1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 };
int tempo = millis();
static bool boardLast[64];
static int boardComp[64];
static bool comeB[64],moveB[64];

bool FIM =false,acabou=false;
String PGN="";

bool auxilio=true,jogando=false,rock=false,ROCK=false;
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
bool vez=0;// a branca começa
int aux1=0,aux=0,chegou,saiu=65,rodada=1; // rodada começa em 1
int saiuAntSave=66;
int y=0;


Ticker tkSecond;												// Second - Timer for Updating Datetime Structure

void Second_Tick(void){

    if(getFim()){
        FIM=true;
    }

}

void chessBoardBegin(void){ //Inicialização do tabuleiro com as peças na posição inicial

    if(checkBoard()==SUCESS){
        for(int i=0;i<64;i++){
            movepecaTFT(chessBoard[i],i); 
        }
        tkSecond.attach(1, Second_Tick);// Inicializa a função de tick para comparações dos botoes
    }else{
        textErrorTFT("Error na inicialização do tabuleiro",widthTFT/2,heightTFT/2); //irá printar na tela do dispositivo uma imagem de error
    }

}

char checkBoard(void){
        boardMapping();//atualiza a aquisição
    for(int i=0;i<64;i++){
        getBoard(&boardNow[i],i); //pega a matrix da aquisição
        if(referencia[i] != boardNow[i]){//se a posição do tabuleiro não for inicializado corretamente ele vai retornar failed
            return FAILED;
        }
    } 
    return SUCESS;
}
void AtualizaChessBoard(void){//retorna a matrix do tabuleiro preenchida
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

    boardMapping();//atualiza a aquisição
    for(int i=0;i<64;i++){
        getBoard(&boardNow[i],i); //pega a matrix da aquisição
        if((boardLast[i]- boardNow[i])==1){//retirou a peça
            saiu = i; //posição da peça retirada
            jogando = true; // flag para marcar que uma peça foi retirada do tabuleiro
        }
        boardLast[i] = boardNow[i];
    } 
    //descomentar essa parte de cima depois
    if(vez==BRANCAS){ //vez das brancas
        //boardNow[jogo[y]] = 0;
        if(SW1Atual != SW1Last){
            //boardNow[jogo[y+1]] = 1;
            if(moveChess()==SUCESS){
                #if DEBUG 
                    Serial.println("Brancas");
                    Serial.println("Rodada:"+String(rodada));
                    Serial.println("peca:"+String(chessBoard[chegou])+" da posição "+String(saiu));
                #endif
                vez = PRETAS;
                jogando = false;
                Serial.println("chegou = "+String(chegou));
                createPGN(saiu,chegou,BRANCAS);
                Serial.println("PGN= "+ PGN);
            }
            else{
                Serial.println("ERROR no movimento");
            }
        }   
    }
    else if(vez==PRETAS){ //vez das pretas
        //boardNow[jogo[y+2]] = 0;
        if(SW2Atual != SW2Last){
            //boardNow[jogo[y+3]] = 1;
            if(moveChess()==SUCESS){
                #if DEBUG 
                    Serial.println("Pretas");
                    Serial.println("peca:"+String(chessBoard[chegou])+" da posição "+String(saiu));
                #endif
                y=y+4;
                vez = BRANCAS;
                jogando = false;
                rodada++;
                createPGN(saiu,chegou,PRETAS);
            }else{
                Serial.println("ERROR no movimento");
            }
            Serial.println("PGN = "+ PGN);
        }  
    }
    if(auxilio){
        auxilioJogo(); //função que da as sugestoes de vezs
    }
    
    
}
void getChess(char *parameter, int i){
    char b = chessBoard[i];
    *parameter = b;
}

void movepeca(int PosInicial, int PosFinal){
    char valaux1 = chessBoard[PosInicial];
    chessBoard[PosInicial] = '_';
    chessBoard[PosFinal] = valaux1;
}



void createPGN(int casaAnt,int casa,bool tipo){
    char colunas[8]={'a','b','c','d','e','f','g','h'};
    char linhas[8]={'8','7','6','5','4','3','2','1'};
    volatile int i,j,k,z;
  //decodificaçÃo de qual casa
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

        
      //descodificamÃo de qual casaAnt
    if(casaAnt<8){ //primeira casaAnt é k=0,z=0
      k=0; z= casaAnt; //prkmekra lknha so muda a coluna
    }else if((casaAnt>=8) & (casaAnt<16)){
      k=1; z= casaAnt-(8*1); //segunda lknha so muda a coluna
    }else if((casaAnt>=16) & (casaAnt<24)){
      k=2; z= casaAnt-(8*2); //tercekra lknha so muda a coluna
    }else if((casaAnt>=24) & (casaAnt<32)){
      k=3; z= casaAnt-(8*3); //quarta lknha so muda a coluna
    }else if((casaAnt>=32) & (casaAnt<40)){
      k=4; z= casaAnt-(8*4); //quknta lknha so muda a coluna
    }else if((casaAnt>=40) & (casaAnt<48)){
      k=5; z= casaAnt-(8*5);
    }else if((casaAnt>=48) & (casaAnt<56)){
      k=6; z= casaAnt-(8*6);
    }else if((casaAnt>=56) & (casaAnt<64)){
      k=7; z= casaAnt-(8*7);
    } 
    if(tipo==BRANCAS){
        if(rock){ // rock pequeno O-O
            PGN += String(rodada)+ ". " + "O-O" +" ";
            rock =false;
            
        }
        else if (ROCK){ //ROCK GRANDE o-o-o
            PGN += String(rodada)+ ". " + "O-O-O" +" ";
            ROCK =false;
        }
        else{
            //para a casa que ta saindo
            if(chessBoard[casaAnt]=='p'){
                PGN += String(rodada)+ ". " + String(colunas[z]) + String(linhas[k]) + " ";
            }else{
                PGN += String(rodada)+ ". " + String(chessBoard[casaAnt]) + String(colunas[z]) + String(linhas[k]) + " ";
            }
            //para a casa que ta chegando
            if(chessBoard[casa]=='p'){
                PGN += String(colunas[j]) + String(linhas[i]) + " ";
            }else{
                PGN += String(chessBoard[casa]) + String(colunas[j]) + String(linhas[i]) + " ";
            }
        }
        
    }else{ //PRETAS
        if(rock){ // rock pequeno O-O
            PGN += "O-O ";
            rock = false; 
        }
        else if(ROCK){ //ROCK GRANDE o-o-o
            PGN += "O-O-O ";
            ROCK = false;
        }
        else{
            //para a casa que ta saindo
            if(chessBoard[casaAnt]=='P'){
                PGN += String(colunas[z]) + String(linhas[k]) + " ";
            }else{
                PGN += String(chessBoard[casaAnt]) + String(colunas[z]) + String(linhas[k]) + " ";
            }
            //para a casa que ta chegando
            if(chessBoard[casa]=='P'){
                PGN += String(colunas[j]) + String(linhas[i]) + " ";
            }else{
                PGN += String(chessBoard[casa]) + String(colunas[j]) + String(linhas[i]) + " ";
            }            
        }
    }
    if(acabou){
        FIM = true;
    }

}
String getPGN(void){
    return PGN;
}

bool getFIM(void){
    return FIM;
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
            #if DEBUG
                Serial.println("chessBoard[saiu]:" + String(chessBoard[saiu]));
            #endif
            RegraChess(chessBoard[saiu],saiu); // atribui a regra do xadrez e salva nos vetores comeBoard e moveBoard
               // printf("_________________________\n");
                //Serial.printf("moveB[64]=\n");
            for(int i=0;i<64;i++){
                getTest(&comeB[i],&moveB[i],i); //pega os vetores da camada anterior e atribui as variaveis criadas na biblioteca                   
                if((moveB[i]==1) & (boardNow[i]==0)){// onde ele pode movimentar e não possui peça
                    switch(chessBoard[saiu]){
                        case 'B': //bispo preto
                            if((moveB[i-7]==1) & ((i-7) > 0)){
                                moveB[i]=0;
                            }
                            if((moveB[i-9]==1) & ((i-9) > 0)){
                                moveB[i]=0; 
                            }
                            if((moveB[i+7]==1) & ((i+7) < 64)){
                                moveB[i]=0; 
                            }
                            if((moveB[i+9]==1) & ((i+9) < 64)){
                                moveB[i]=0; 
                            }
                            if(moveB[i]==1){
                                simbolCasa(i,2);
                                moveB[i]=0; 
                            }
                            break;
                        case 'P': //piao preto
                            simbolCasa(i,2);
                            moveB[i]=0; 
                            break;
                        default:
                            simbolCasa(i,2);
                            moveB[i]=0;
                            break;
                    }
                        
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
                aux =1;
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

