#ifndef MOVIMENTO_H
#define MOVIMENTO_H
#include "estado.h"

//DI 312

//#define DRAWPLAYER 47

void draw_player(State *st);

int flagMana(State *st);

void playerRandom(State *st,Mob *mob);

void do_movement_action(State *st, int dx, int dy,Mob *mob, Audio *audios);

void teletransporte(State *st,Mob *mobs,Audio *audios);

int update(State *st,Mob *mob, Audio *audios);

#endif