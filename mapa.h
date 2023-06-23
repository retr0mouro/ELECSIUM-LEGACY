#include "luz.h"
/*#include "estado.h"
#include "utils.h"*/


int contaVizinhos1(STATE *st,int x,int y);

int contaVizinhos2(STATE *st,int x,int y);

void geraParedes1(STATE *st);

void geraParedes2(STATE *st);

void drawMap(STATE *st,int nrows,int ncols);

void drawElec(STATE *st);

void drawMobs(STATE *st,MOB *mobs);

void redrawMap(STATE *st);