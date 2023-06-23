#include "music.h"

//Verificar se os andares não passam dos seus limites | FUNCIONA
int verificaFloor(STATE *st);

//Verificar se o jogador não morreu | FUNCIONA
int verificaHP(STATE *st);


//Inicializar os mobs | FUNCIONA
void initializeMobs(MOB *mobs);


void cleanMobs(STATE *st,MOB *mob);



// Fixando o Y do mob, verifica na linha do mesmo, o local mais próximo possível
// de ser uma casa para o mob, ou seja, não é parede, jogador, objetivo ou
// elecsium
int x_mais_perto(MOB mob, STATE *st);


// Fixando o X do mob, verifica na coluna do mesmo, o local mais próximo
// possível de ser uma casa para o mob, ou seja, não é parede, jogador, objetivo
// ou elecsium
int y_mais_perto(MOB mob, STATE *st);

// Gera uma quantidade de elecsium aleatoriamente no mapa, dependendo da
// dificuldade;   | FUNCIONA
void gera_elecsium(STATE *st);

// Verifica se existem paredes entre o jogador e o mob, returnando 0 se houver
// uma parede entre eles
int pode_snipar(MOB mob, STATE *st);

// Calcula a distancia entre o mob e o jogador.
int distancia_ideal(MOB mob, STATE *st);

// Calcula a nova distância do jogador ao mob->
int nova_distancia(int x, int y, STATE *st);


// Calcula a distancia entre mobs 
int distancia_mobeal(MOB mob, MOB sta);

// Gera mobs aleatoriamente no mapa, sendo que a quantidade varia com a
// dificuldade escolhida, e o tipo de mobs varia aleatoriamente.
void gera_mobs(STATE *st, MOB *mob);

// Verifica qual o indice do mob mais proximo da lista de mobs, tendo como ponto
// de referencia o jogador
int nearest_mob(MOB *mob, STATE *st);


// verifica qual o indice do mob mais proximo do player, excluindo o mob de referência
int nearest_comrade(MOB mob, MOB *mobs, STATE *st);
// Verifica se a posicao esta na lista
int esta_na_lista(int posicoes[], int posicao, int repeticoes);
// Algoritmo para aproximar o mob do jogador
void aproxima_do_player(MOB mob, STATE *st);
// Algoritmo de fuga para os mobs covardes, ou seja, fogem se sozinhos
void foge_do_player(MOB mob, STATE *st);
// Consoante a distância do mob ao jogador, determina se o mob tem movimento/se
// está acordado.
void mobs_are_awake(MOB *mobs, STATE *st);
// Função para despertar os mobs, utilizadas pelos mobs espertos
void mob_awakes_mob(MOB mob, MOB *mobs, STATE *st);
// Verifica a vida do mob para saber se foi derrotado
void mob_morreu(MOB mob, STATE *st, AUDIO *audios);
// Função de combate, referente ao dano que é deferido ao mob
void mob_levou_dano(MOB mob, STATE *st, AUDIO *audios);
// Função de combatte, referente ao dano que o jogador tomou
void mob_deu_dano(MOB mob, STATE *st);
// Algoritmo para o movimento do mob
void movimento_mob(MOB *mobs, STATE *st, AUDIO *audios);