#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>

#define ELEC 43

#define BOSS 17
#define MOBS 18
#define COLOR_CHEGADA 90
#define CHEGADA 91
#define REVERSO 92
#define CHAO 93
#define CHAOLUZ 94
#define CHAOLUZP 95
#define COLOR_CHAO 96
#define PAREDE 97
#define COLOR_PAREDE 98
#define PAREDELUZ 99
#define PAREDELUZP 999
#define MAXMP 49
#define CEGO 1000
#define NVE 1001
#define COLOR_PONTO 27

#define HP 2
#define HBAR 9
#define MP 88
#define MBAR 69
#define ELSIU 110
#define PAUSE 90


#define DRAWPLAYER 47

#define NROWS 59
#define NCOLS 211

#define MAPALT 54
#define MAPLAR 211


#define MALLOC_MOB(arr) for (int i = 0; i < 30; i++) { \
    	mobs[i] = malloc(sizeof(MOB)); \
	}

#define FREE_MOB(arr) do { \
    for (int i = 0; i < 30; i++) { \
        free(arr[i]); \
    } \
    } while(0)


#endif 