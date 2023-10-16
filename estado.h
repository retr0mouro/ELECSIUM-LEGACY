#ifndef ESTADO_H
#define ESTADO_H
#include <SFML/Audio.h>


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
} State;

typedef struct mobs {
    int mobX;
    int mobY;
    int vida;
    int qual_mob;
    int awake;
    int indice;
} * Mob;



typedef struct audios{
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
} Audio;

#endif