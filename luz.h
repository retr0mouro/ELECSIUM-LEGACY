#ifndef LUZ_H
#define LUZ_H
#include "estado.h"



void verificaLuz(State *st);

void verificaLuz2(State *st); // percorre o mapa todo e verifica se não tem luz que passou pelas paredes, começa da direita para a esquerda e de cima para baixo


void limpaLuz(State *st); // limpa a luz a cada movimento do jogador (só é implementada no movimentos)

int objetivo(State *st, int x, int y);

int verificaCima(State *st, int x, int y); // caso tenha parede em baixo do player devolve 1 

int verificaBaixo(State *st, int x, int y); // caso tenha parede em cima do player devolve 1


int paredeEntrePontosCima(State *st, int x, int y, int xant, int yant, int i3); // vê a distancia entre dois pontos e verifica se existe parede entre eles


int paredeEntrePontosBaixo(State *st, int x, int y, int xant, int yant, int i3);
float declive(State *st, int x, int y);
int equationX(State *st, int xb, int yb, int y);
int equationY(State *st, int xb, int yb, int x);



//VISÃO MODO FACIL

void direita(State *st);
void esquerda(State *st);
void cima(State *st);
void baixo(State *st);
void luznormal(State *st);


// VISAO DO TRYHARD

int distancia(State *st, int x, int y);
void direitath(State *st);
void esquerdath(State *st);
void cimath(State *st);
void baixoth(State *st);
void luzth(State *st);
void pintaLuz(State *st);
void luz(State *st);

#endif