#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <limits.h>


typedef struct state {
	int playerX;
	int playerY;
    int playerHP;
    int playerMP;
    int objetivoX;
    int objetivoY;
    int dif;
    int race;
    int map[54][211];
} STATE;

typedef struct mobs {
    int mobX;
    int mobY;
    int awake;
} MOB;

//srand(time(NULL));
STATE st = {12,20,49,30,0,0,0,0,{{0}}};