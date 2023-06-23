#include "game.h"
//#include <ncurses.h>


int main() {
	AUDIO audios = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

	STATE st = {12,20,49,0,20,0,0,0,0,0,1,0,0,1,{{0}},0,5};

	MOB mobs[30];
	
    initscr();
	MALLOC_MOB(mobs);

	srand(time(NULL));

	
	start_color();


	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
        init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
        init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);

	initializeMobs(mobs);
	repeat(&st,mobs,&audios);
	return 0;
}