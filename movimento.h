#include "mapa.h"

//DI 312

//#define DRAWPLAYER 47

void draw_player(STATE *st);

int flagMana(STATE *st);

void playerRandom(STATE *st,MOB *mob);

void do_movement_action(STATE *st, int dx, int dy,MOB *mob, AUDIO *audios);

void teletransporte(STATE *st,MOB *mobs,AUDIO *audios);

int update(STATE *st,MOB *mob, AUDIO *audios);