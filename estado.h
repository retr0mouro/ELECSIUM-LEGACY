/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <limits.h>
#include <math.h>
//#include <SFML/Audio.h>



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
STATE st = {12,20,49,30,0,0,0,0,{{0}}};*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <SFML/Audio.h>


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

#define NROWS 59
#define NCOLS 211

#define MAPALT 54
#define MAPLAR 211


typedef struct state {
    int playerX;
    int playerY;
    int playerHP;
    int playerMAXMP;
    int playerMP;
    int objetivoX;
    int objetivoY;
    int dif;
    int race;
    int elecsium;
    int arma;
    int skill;
    int mobs_TOTAIS;
    int floor;
    int map[54][211];
    int sound;
    int playanterior;
} STATE;

typedef struct mobs {
    int mobX;
    int mobY;
    int vida;
    int qual_mob;
    int awake;
    int indice;
} * MOB;



typedef struct audio{
    sfMusic* music;
    sfMusic* jusic;
    sfSound* siu;
    sfSoundBuffer* buffersiu;
    sfSound* saiu;
    sfSoundBuffer* buffersaiu;
    sfSound* ganhou;
    sfSoundBuffer* bufferganhou;
    sfSound* elecsium;
    sfSoundBuffer* bufferelecsium;
    sfSound* tp;
    sfSoundBuffer* buffertp;
    sfSound* mk;
    sfSoundBuffer* buffermk;
} AUDIO;

AUDIO audios = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

STATE st = {12,20,49,0,20,0,0,0,0,0,1,0,0,1,{{0}},0,5};

MOB mobs[30]; //= {{17,16,0,1,0,0}};

#define MALLOC_MOB(arr) for (int i = 0; i < 30; i++) { \
    	mobs[i] = malloc(sizeof(MOB)); \
	}

#define FREE_MOB(arr) do { \
    for (int i = 0; i < 30; i++) { \
        free(arr[i]); \
    } \
    } while(0)
