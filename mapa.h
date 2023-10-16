#ifndef MAPA_H
#define MAPA_H
#include "estado.h"



int contaVizinhos1(State *st,int x,int y);

int contaVizinhos2(State *st,int x,int y);

void geraParedes1(State *st);

void geraParedes2(State *st);

void drawMap(State *st,int nrows,int ncols);

void drawElec(State *st);

void drawMobs(State *st,Mob *mobs);

void redrawMap(State *st);

#endif