#ifndef MENUS_H
#define MENUS_H
#include "estado.h"



void drawHP();

void drawHealth(State *st);

void drawMP();

void drawMana(State *st);

void menuDiff(State *st, Mob *mobs, Audio *audios);

void menu1(State *st, Mob *mobs,Audio *audios);

void menuPause(State *st, Mob *mobs,Audio *audios);

void victory(State *st,Mob *mobs,Audio *audios);

#ifndef