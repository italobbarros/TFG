#ifndef REGRASMOVE_H_
#define REGRASMOVE_H_


enum Lado{
    Bottom=1,
    Right=2,
    Left=3,
    Top=4 
};
bool testCasaBorda(int casaAtual, Lado lado);

void testeRegra(char peca,int casaAtual);
void RegraChess(char peca,int casaAtual);
void clearBoard(void);
void getTest(bool *come, bool *move,int i);
void RegraDiagonal(int casaAtual);
void RegraHorVert(int casaAtual);
void RegraRei(int casaAtual);
#endif /*REGRASMOVE_H_*/