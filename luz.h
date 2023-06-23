//#include "estado.h"
//#include "utils.h"
#include "menus.h"
// Algumas funções auxiliares usadas na luz

void verificaLuz(STATE *st);

void verificaLuz2(STATE *st); // percorre o mapa todo e verifica se não tem luz que passou pelas paredes, começa da direita para a esquerda e de cima para baixo


void limpaLuz(STATE *st); // limpa a luz a cada movimento do jogador (só é implementada no movimentos)

int objetivo(STATE *st, int x, int y);

int verificaCima(STATE *st, int x, int y); // caso tenha parede em baixo do player devolve 1 

int verificaBaixo(STATE *st, int x, int y); // caso tenha parede em cima do player devolve 1


int paredeEntrePontosCima(STATE *st, int x, int y, int xant, int yant, int i3); // vê a distancia entre dois pontos e verifica se existe parede entre eles


int paredeEntrePontosBaixo(STATE *st, int x, int y, int xant, int yant, int i3);
float declive(STATE *st, int x, int y);
int equationX(STATE *st, int xb, int yb, int y);
int equationY(STATE *st, int xb, int yb, int x);



//VISÃO MODO FACIL

void direita(STATE *st);
void esquerda(STATE *st);
void cima(STATE *st);
void baixo(STATE *st);
void luznormal(STATE *st);


// VISAO DO TRYHARD

int distancia(STATE *st, int x, int y);
void direitath(STATE *st);
void esquerdath(STATE *st);
void cimath(STATE *st);
void baixoth(STATE *st);
void luzth(STATE *st);
void pintaLuz(STATE *st);
void luz(STATE *st);
