#ifndef MOBS_H
#define MOBS_H
#include "estado.h"

//Verificar se os andares não passam dos seus limites | FUNCIONA
int verificaFloor(State *st);

//Verificar se o jogador não morreu | FUNCIONA
int verificaHP(State *st);


//Inicializar os mobs | FUNCIONA
void initializeMobs(Mob *mobs);


void cleanMobs(State *st,Mob *mob);



// Fixando o Y do mob, verifica na linha do mesmo, o local mais próximo possível
// de ser uma casa para o mob, ou seja, não é parede, jogador, objetivo ou
// elecsium
int x_mais_perto(Mob mob, State *st);


// Fixando o X do mob, verifica na coluna do mesmo, o local mais próximo
// possível de ser uma casa para o mob, ou seja, não é parede, jogador, objetivo
// ou elecsium
int y_mais_perto(Mob mob, State *st);

// Gera uma quantidade de elecsium aleatoriamente no mapa, dependendo da
// dificuldade;   | FUNCIONA
void gera_elecsium(State *st);

// Verifica se existem paredes entre o jogador e o mob, returnando 0 se houver
// uma parede entre eles
int pode_snipar(Mob mob, State *st);

// Calcula a distancia entre o mob e o jogador.
int distancia_ideal(Mob mob, State *st);

// Calcula a nova distância do jogador ao mob->
int nova_distancia(int x, int y, State *st);


// Calcula a distancia entre mobs 
int distancia_mobeal(Mob mob, Mob sta);

// Gera mobs aleatoriamente no mapa, sendo que a quantidade varia com a
// dificuldade escolhida, e o tipo de mobs varia aleatoriamente.
void gera_mobs(State *st, Mob *mob);

// Verifica qual o indice do mob mais proximo da lista de mobs, tendo como ponto
// de referencia o jogador
int nearest_mob(Mob *mob, State *st);


// verifica qual o indice do mob mais proximo do player, excluindo o mob de referência
int nearest_comrade(Mob mob, Mob *mobs, State *st);
// Verifica se a posicao esta na lista
int esta_na_lista(int posicoes[], int posicao, int repeticoes);
// Algoritmo para aproximar o mob do jogador
void aproxima_do_player(Mob mob, State *st);
// Algoritmo de fuga para os mobs covardes, ou seja, fogem se sozinhos
void foge_do_player(Mob mob, State *st);
// Consoante a distância do mob ao jogador, determina se o mob tem movimento/se
// está acordado.
void mobs_are_awake(Mob *mobs, State *st);
// Função para despertar os mobs, utilizadas pelos mobs espertos
void mob_awakes_mob(Mob mob, Mob *mobs, State *st);
// Verifica a vida do mob para saber se foi derrotado
void mob_morreu(Mob mob, State *st, Audio *audios);
// Função de combate, referente ao dano que é deferido ao mob
void mob_levou_dano(Mob mob, State *st, Audio *audios);
// Função de combatte, referente ao dano que o jogador tomou
void mob_deu_dano(Mob mob, State *st);
// Algoritmo para o movimento do mob
void movimento_mob(Mob *mobs, State *st, Audio *audios);

#endif