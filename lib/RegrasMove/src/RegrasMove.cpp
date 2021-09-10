#include "RegrasMove.h"
#include "GetBoard.h"

int mov=0;
int comeBoard[64],moveBoard[64];
int move2Board[8][8];
void clearBoard(void){
        for (int i = 0; i < 64; i++){
            comeBoard[i]=0;
            moveBoard[i]=0;
            
        } 
}

void testeRegra(char peca,int casaAtual){
  switch (peca){
    default:
      
      break;
    //branco
    case 'p': //piao p
      break;
    case 'b': //bispo
      
      break;
    case 'r': //rook
      
      break;
    case 'q': //rainha
      
      break;  
    case 'k': //king
      
      break;
    case 'n'://cavalo 
      
      break;
    
    //preto  
    case 'P': //piao P
      
      break;
    case 'B': //bispo
      
      break;
    case 'R': //rook
      
      break;
    case 'Q': //rainha
      
      break;  
    case 'K': //king
      
      break;
    case 'N'://cavalo 
      
      break; 
  }
}

void RegraChess(char peca,int casaAtual){
  switch (peca){
    default:

      break;
    //branco
    case 'p': //piao p
        clearBoard();
        mov=1;
        if((casaAtual>=a2)|(casaAtual<=h2)){ // O pião na posição inicial pode movimentar 2 casas
            mov = 2;
            //Serial.println("mov"+String(mov));
        }
        comeBoard[casaAtual - 9] = 1; // vai colocar um na casa que ele pode comer
        comeBoard[casaAtual - 7] = 1; // vai colocar um na casa que ele pode comer
        for(int i=1;i<=mov;i++){
            moveBoard[casaAtual-i*8] = 1; // vai colocar um na casa que ele pode movimentar
        }
        //Serial.println("MoveBoard"+String(casaAtual-mov*8));
      break;
    case 'b': //bispo
        clearBoard();
        RegraDiagonal(casaAtual);
        
      break;
    case 'r': //rook
        clearBoard();
        RegraHorVert(casaAtual);
      break;
    case 'q': //rainha
        clearBoard();
        RegraDiagonal(casaAtual);
        RegraHorVert(casaAtual);
      break;  
    case 'k': //king
        clearBoard();
      break;
    case 'n'://cavalo 
        clearBoard();
            if((casaAtual - 15)>0){moveBoard[casaAtual - 15] = 1;}
            if((casaAtual - 17)>0){moveBoard[casaAtual - 17] = 1;}
            if((casaAtual - 6)>0){moveBoard[casaAtual - 6] = 1;}
            if((casaAtual - 10)>0){moveBoard[casaAtual - 10] = 1;}
            if((casaAtual + 15)<64){moveBoard[casaAtual + 15] = 1;}
            if((casaAtual + 17)<64){moveBoard[casaAtual + 17] = 1;}
            if((casaAtual + 6)<64){moveBoard[casaAtual  + 6] = 1;}
            if((casaAtual + 10)<64){moveBoard[casaAtual + 10] = 1;}
      break;
    
    //preto  
    case 'P': //piao P
        clearBoard();
        mov=1;
        if((casaAtual>=a7)|(casaAtual<=h7)){ // O pião na posição inicial pode movimentar 2 casas
            mov = 2;
        }
        comeBoard[casaAtual + 9] = 1; // vai colocar um na casa que ele pode comer
        comeBoard[casaAtual + 7] = 1; // vai colocar um na casa que ele pode comer
        for(int i=1;i<=mov;i++){
            moveBoard[casaAtual+i*8] = 1; // vai colocar um na casa que ele pode movimentar
        }
      break;
    case 'B': //bispo
        clearBoard();
        RegraDiagonal(casaAtual);;
      break;
    case 'R': //rook
        clearBoard();
         RegraHorVert(casaAtual);
        
      break;
    case 'Q': //rainha
        clearBoard();
        RegraDiagonal(casaAtual);
        RegraHorVert(casaAtual);
      break;  
    case 'K': //king
        clearBoard();

      break;
    case 'N'://cavalo 
        clearBoard();
        if((casaAtual - 15)>0){moveBoard[casaAtual - 15] = 1;}
        if((casaAtual - 17)>0){moveBoard[casaAtual - 17] = 1;}
        if((casaAtual - 6)>0){moveBoard[casaAtual - 6] = 1;}
        if((casaAtual - 10)>0){moveBoard[casaAtual - 10] = 1;}
        if((casaAtual + 15)<64){moveBoard[casaAtual + 15] = 1;}
        if((casaAtual + 17)<64){moveBoard[casaAtual + 17] = 1;}
        if((casaAtual + 6)<64){moveBoard[casaAtual  + 6] = 1;}
        if((casaAtual + 10)<64){moveBoard[casaAtual + 10] = 1;}
      break; 
  }
}

void getTest(int *come, int *move,int i){
    int c = comeBoard[i];
    int m = moveBoard[i];
    *come = c;
    *move = m;
}

void RegraDiagonal(int casaAtual){
    int i=0,j=0;
        for (int x = 0; x < 8; x++){
            for (int w = 0; w < 8; w++){
                move2Board[x][w]=0;
            }      
        }
        //decodificaçÃo de qual casaAtual era a anterior
            if(casaAtual<8){ //primeira casaAtual é i=0,j=0
            i=0; j= casaAtual; //primeira linha so muda a coluna
            }else if((casaAtual>=8) & (casaAtual<16)){
            i=1; j= casaAtual-(8*1); //segunda linha so muda a coluna
            }else if((casaAtual>=16) & (casaAtual<24)){
            i=2; j= casaAtual-(8*2); //terceira linha so muda a coluna
            }else if((casaAtual>=24) & (casaAtual<32)){
            i=3; j= casaAtual-(8*3); //quarta linha so muda a coluna
            }else if((casaAtual>=32) & (casaAtual<40)){
            i=4; j= casaAtual-(8*4); //quinta linha so muda a coluna
            }else if((casaAtual>=40) & (casaAtual<48)){
            i=5; j= casaAtual-(8*5);
            }else if((casaAtual>=48) & (casaAtual<56)){
            i=6; j= casaAtual-(8*6);
            }else if((casaAtual>=56) & (casaAtual<64)){
            i=7; j= casaAtual-(8*7);
            }
            //Serial.println("Valor de i:"+String(i));
            //Serial.println("Valor de j:"+String(j));
        for (int y = 1; y <= 8; y++){
            if(((i+y)<8) && ((j+y)<8)){move2Board[i+y][j+y] = 1;}
            if(((i-y)>=0) && ((j+y)<8)){move2Board[i-y][j+y] = 1;}
            if(((i+y)<8) && ((j-y)>=0)){move2Board[i+y][j-y] = 1;}
            if(((i-y)>=0) && ((j-y)>=0)){move2Board[i-y][j-y] = 1;}
        }
        for (int a = 0; a < 8; a++){
            for (int b = 0; b < 8; b++){
                moveBoard[a*8+b] = move2Board[a][b];
            }
        }     
}

void RegraHorVert(int casaAtual){
    for (int i = 1; i <= 8; i++){
        if((casaAtual - i*8)>0){moveBoard[casaAtual - i*8] = 1;}
        if((casaAtual + i*8)<64){moveBoard[casaAtual + i*8] = 1;}
    }
    for (int y = 0; y < 8; y++){
        if((casaAtual>=(8*y))&(casaAtual<=8*y+7)){
            for (int i = 0; i < 8; i++){
                moveBoard[y*8+i] = 1;
            }
        }  
    }
}