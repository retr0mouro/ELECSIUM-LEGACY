//#include "estado.h"
#include "mobs.h"

/*#define HP 2
#define HBAR 9
#define MP 88
#define MBAR 69
#define ELSIU 110
#define PAUSE 90*/



void drawHP();

void drawHealth(STATE *st);

void drawMP();

void drawMana(STATE *st);

void menuDiff(STATE *st, MOB *mobs, AUDIO *audios);

void menu1(STATE *st, MOB *mobs,AUDIO *audios);

void menuPause(STATE *st, MOB *mobs,AUDIO *audios);

void victory(STATE *st,MOB *mobs,AUDIO *audios);
