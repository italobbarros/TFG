#include "ChessBoard.h"
#include <GetBoard.h>
#include <TFT.h>
#include <stdio.h>
#include "config.h"
#include "RegrasMove.h"
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
static bool boardAuxNow[64];
static bool boardLast[64];
static int boardComp[64];
static bool comeB[64],moveB[64];

String PGN;

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
bool vez;// a branca começa
int aux1,aux,chegou,saiu,rodada; // rodada começa em 1
int saiuAntSave;
int y,t,pos1;
int s1,s2,m1,m2;
bool stopTime;
unsigned long timePlay1,timePlay2;
  #define tempOriginal 15

bool chessBoardBegin(void){ //Inicialização do tabuleiro com as peças na posição inicial
    vez=0;PGN="pgn=";
    aux1=0,aux=0,chegou,saiu=65,rodada=1; // rodada começa em 1
    saiuAntSave=66,pos1=66;
    y=0;t=0;

    stopTime=0;
    timePlay1=0;timePlay2=0;
    m1=tempOriginal,m2=tempOriginal;

    SW1Last = push1Read();
    SW2Last = push2Read();
    if(checkBoard()==SUCESS){
        for(int i=0;i<64;i++){
            movepecaTFT(chessBoard[i],i); 
            boardLast[i] = boardNow[i];
        }
        return SUCESS;
    }else{
        textTFT("Error na Inicialização!",heightTFT/2+10,widthTFT/2,Error); //irá printar na tela do dispositivo uma imagem de error
        return FAILED;
    }

}

bool checkBoard(void){
    boardMapping();//atualiza a aquisição
    Serial.println("checkBoard[]=");
    for(int i=0;i<64;i++){
        getBoard(&boardNow[i],i); //pega a matrix da aquisição
        Serial.print(String(boardNow[i]) + " ,");
            if((i+1)%8==0){
            printf("\n");
            }
        if(referencia[i] != boardNow[i]){//se a posição do tabuleiro não for inicializado corretamente ele vai retornar failed
            Serial.println("Error na inicialização!");
            return FAILED;
        }
    } 
    return SUCESS;
}
void AtualizaChessBoard(void){//retorna a matrix do tabuleiro preenchida
    boardMapping();//atualiza a aquisição
    for(int i=0;i<64;i++){
        getBoard(&boardNow[i],i); //pega a matriz da aquisição
        if((boardLast[i]- boardNow[i])==1){//retirou a peça
            saiu = i; //posição da peça retirada
            jogando = true; // flag para marcar que uma peça foi retirada do tabuleiro
            t +=1;
        }
    }
    if(jogando==true){
        if(t==1){
            for(int i=0;i<64;i++){
                boardLast[i] = boardNow[i];
            }
            t=0;
        }
        //descomentar essa parte de cima depois
        if(vez==BRANCAS){ //vez das brancas
            if(!push1Read()){
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
            if(!push2Read()){
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
                //SW2Last = push2Read();
            }  
        }
        if(auxilio){
            auxilioJogo(); //função que da as sugestoes de vezs
        }
        
         
    }
    
    if(vez==BRANCAS){
        printTextTFT1((tempoBrancas(vez)).c_str(),heightTFT/2,widthTFT,"Bot");//valor dinamico do tempo das brancas
        printTextTFT1((getTempo(PRETAS)).c_str(),heightTFT/2,offsetY/4,"Top");//valor estatico do tempo das pretas
    }else{
        printTextTFT1((tempoPretas(vez)).c_str(),heightTFT/2,offsetY/4,"Top");//valor dinamico do tempo das pretas
        printTextTFT1((getTempo(BRANCAS)).c_str(),heightTFT/2,widthTFT,"Bot"); //valor estatico do tempo das brancas
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
            if(chessBoard[casa]=='p'){
                PGN += String(rodada)+ ". " + String(colunas[z]) + String(linhas[k]) + " ";
            }else{
                PGN += String(rodada)+ ". " + String(chessBoard[casa]) + String(colunas[z]) + String(linhas[k]) + " ";
            }
            //para a casa que ta chegando
            PGN += String(colunas[j]) + String(linhas[i]) + " ";

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
            if(chessBoard[casa]=='P'){
                PGN += String(colunas[z]) + String(linhas[k]) + " ";
            }else{
                PGN += String(chessBoard[casa]) + String(colunas[z]) + String(linhas[k]) + " ";
            }
            //para a casa que ta chegando
            PGN += String(colunas[j]) + String(linhas[i]) + " ";
                        
        }
    }

}

String getTempo(bool tipo){
  if(tipo==0){
    if(s1<10 && m1<10){
        return ("0"+String(m1)+ ":0" + String(s1)); 
    }
    else if(m1<10){
        return ("0"+String(m1)+ ":" + String(s1)); 
    }
    else if(s1<10){
        return (String(m1)+ ":0" + String(s1)); 
    }
    else{
        return (String(m1)+ ":" + String(s1));
    }
  }else{
    if(s2<10 && m2<10){
        return ("0"+String(m2)+ ":0" + String(s2)); 
    }
    else if(m2<10){
        return ("0"+String(m2)+ ":" + String(s2)); 
    }
    else if(s2<10){
        return (String(m2)+ ":0" + String(s2)); 
    }
    else{
        return (String(m2)+ ":" + String(s2));
    }
  }
}

void StopTime(void){
  stopTime = 1;
}

bool timeOut(void){
    if((s1==0) && (m1==0)){
        return 1;
    }else if((s2==0) && (m2==0)){
        return 1;
    }else{
        return 0;
    }
}
String tempoBrancas(bool vez){
  if(vez==0 && (!stopTime)){
    if(millis() - timePlay1 >= 1000){
        if(m1 == tempOriginal){
            m1 = m1 - 1;
            s1=59;
        }
        else if(m1>0 && s1==0){
            m1 = m1 - 1;
            s1=59;    
        }else if(m1>=0 && s1>0){
            s1--;
        }
        timePlay1=millis();       
    }
  }else{
    timePlay1=millis();
  }
  return getTempo(0);
  
}

String tempoPretas(bool vez){
    if(vez==1 && (!stopTime)){
        if(millis() - timePlay2>=1000){
            if(m2 == tempOriginal){
                m2 = m2 - 1;
                s2=59;
            }
            else if(m2>0 && s2==0){
                m2 = m2 - 1;
                s2=59;    
            }else if(m2>=0 && s2>0){
                s2--;
            }
            timePlay2=millis();      
        }
    }
    else{
        timePlay2=millis();
    }
    return getTempo(1);
}


String getPGN(void){
    return PGN;
}



void auxilioJogo(void){
    if(saiuAntSave != saiu){
        simbolCasa(saiu, 1); // faz uma marcação na casa que possui a peça que ira mover
        #if DEBUG
        Serial.println("chessBoard[saiu]:" + String(chessBoard[saiu]));
        #endif
        RegraChess(chessBoard[saiu], saiu); // atribui a regra do xadrez e salva nos vetores comeBoard e moveBoard
                                            // printf("_________________________\n");
                                            // Serial.printf("moveB[64]=\n");
        testeXadrez();
        saiuAntSave = saiu;
    }
    
    //auxilio para a casa que foi movimentada mas que nao tem peça
    boardMapping();
    for(int i=0;i<64;i++){
        getBoard(&boardAuxNow[i],i); //pega a matrix da aquisição
        if(pos1 != i){
            if((boardAuxNow[i] - boardLast[i]) == 1){ //saiu da casa
                simbolCasa(i, 4);
                pos1 = i;
            }
        }
    }

}

void testeXadrez(void){
    for (int i = 0; i < 64; i++){
            getTest(&comeB[i], &moveB[i], i); // pega os vetores da camada anterior e atribui as variaveis criadas na biblioteca
            if ((moveB[i] == 1) & (boardNow[i] == 0)){ // onde ele pode movimentar e não possui peça
                switch (chessBoard[saiu])
                {
                case 'B': // bispo preto
                    if ((moveB[i - 7] == 1) & ((i - 7) > 0))
                    {
                        moveB[i] = 0;
                    }
                    if ((moveB[i - 9] == 1) & ((i - 9) > 0))
                    {
                        moveB[i] = 0;
                    }
                    if ((moveB[i + 7] == 1) & ((i + 7) < 64))
                    {
                        moveB[i] = 0;
                    }
                    if ((moveB[i + 9] == 1) & ((i + 9) < 64))
                    {
                        moveB[i] = 0;
                    }
                    if (moveB[i] == 1)
                    {
                        simbolCasa(i, 2);
                        moveB[i] = 0;
                    }
                    break;
                case 'P': // piao preto
                    simbolCasa(i, 2);
                    moveB[i] = 0;
                    break;
                default:
                    simbolCasa(i, 2);
                    moveB[i] = 0;
                    break;
                }
            }
            else if ((comeB[i] == 1) & (boardNow[i] == 1))
            { // onde ele pode comer e possui peça
            }
        }
}


char moveChess(void){
    aux = 0;
    boardMapping(); // atualiza a aquisição
    for (int i = 0; i < 64; i++){
        getBoard(&boardNow[i], i); // pega a matrix da aquisição
        boardComp[i] = boardNow[i] - boardLast[i];
        if (boardComp[i] == 1){ // chegou na casa
            chegou = i;
            aux = 1;
        }
    }
    if (aux == 1){                           // caso para movimento simples
        movepeca(saiu, chegou); // movimenta a matriz
    }
    printf("_________________________\n");
    printf("chessBoard[64]=\n");
    for (int i = 0; i < 64; i++){
        movepecaTFT(chessBoard[i], i);
        //serial
        printf("%c ,", chessBoard[i]);
        if ((i + 1) % 8 == 0){
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

