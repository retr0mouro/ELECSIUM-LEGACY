#include "movimento.h"


void resume(STATE *st,MOB *mob, AUDIO *audios){
	init_color(COLOR_CHEGADA,755,0,755);
	init_pair(CHEGADA,COLOR_BLACK,COLOR_CHEGADA);


	pausa:
	menuPause(st,audios);
    clear();
	//jogar = 1;
	goto ciclo;

	//ciclo---------------------------------------------------------------------------------------------------------------

	ciclo:
	while (verificaHP(st)){
		if(verificaFloor(st) == 0) victory(st,audios);
		clear();
		redrawMap(st);
	move(NROWS - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		printw("(%d,%d) %d %d %d",mob[1]->mobX,mob[1]->mobY,st->floor, NROWS,NCOLS);//NCOLS, st->playerX, st->playerY, st->objetivoX, st->objetivoY, NROWS);
		attroff(COLOR_PAIR(COLOR_BLUE));
		


		//Funcoes para luz
		luz(st);//ligar
		verificaLuz(st);
		verificaLuz2(st);



		//menus e jogador
		draw_player(st);
		drawHP();
		drawMP();
		drawHealth(st);
		drawMana(st);




		mvaddch(st->objetivoX,st->objetivoY,(int) 'V' | COLOR_PAIR(CHEGADA));
		movimento_mob(mob,st, audios);
		
		
		
		
		drawElec(st);
		drawMobs(st,mob);
		
		
		cleanMobs(st,mob); 
		
		
		
		
		//Print da vizinhaça do jogador;
		/*mvaddch(st->playerX - 1, st->playerY - 1, st->map[st->playerX - 1][st->playerY - 1]);
		mvaddch(st->playerX - 1, st->playerY + 0, st->map[st->playerX - 1][st->playerY + 0]);
		mvaddch(st->playerX - 1, st->playerY + 1, st->map[st->playerX - 1][st->playerY + 1]); 
		mvaddch(st->playerX + 0, st->playerY - 1, st->map[st->playerX + 0][st->playerY - 1]); 
		mvaddch(st->playerX + 0, st->playerY + 1, st->map[st->playerX + 0][st->playerY + 1]);
		mvaddch(st->playerX + 1, st->playerY - 1, st->map[st->playerX + 1][st->playerY - 1]);
		mvaddch(st->playerX + 1, st->playerY + 0, st->map[st->playerX + 1][st->playerY + 0]);
		mvaddch(st->playerX + 1, st->playerY + 1, st->map[st->playerX + 1][st->playerY + 1]);*/


		
		move(st->playerX, st->playerY);
		

		if(update(st,mob,audios) == 0) {
			goto pausa;
			break;
		}
	}
	st->sound = 11; 
	effects(st, audios); 
	endwin(); 
	exit(0); 
	FREE_MOB(mobs); 
	return;
}

void repeat(STATE *st,MOB *mob, AUDIO *audios){
	if(verificaHP(st) == 0){
		menuNoob(st); 
		FREE_MOB(mobs);
		endwin();
		exit(0);
		return;
	}
	init_color(COLOR_CHEGADA,755,0,755);
	init_pair(CHEGADA,COLOR_BLACK,COLOR_CHEGADA);
	menu1(st, audios);
    clear();

	som(st, audios);
    drawMap(st,NROWS,NCOLS);
	//initialize(st);  
	//distancia(st,st->playerX,st->playerY,1); 


	int x = rand() % (NROWS - 7);
	int y = rand() % (NCOLS - 2);
	while(1){
		if(st->map[x][y] != (int) '#'){
    		st->objetivoX = x;
    		st->objetivoY = y;
			break;
		}else{
			x = rand() % (NROWS - 7);
			y = rand() % (NCOLS - 2);
		}
	}

	
	x = rand() % (NROWS - 7);
	y = rand() % (NCOLS - 2);
	while(1){
		if(st->map[x][y] != (int) '#'){
    		st->playerX = x;
    		st->playerY = y;
			break;
		}else{
			x = rand() % (NROWS - 7);
			y = rand() % (NCOLS - 2);
		}
	}
	st->playerX = x;
	st->playerY = y;
    draw_player(st);
    
	st->map[st->objetivoX][st->objetivoY] = (int) 'V';
    mvaddch(st->objetivoX,st->objetivoY,(int) 'V' | COLOR_PAIR(CHEGADA));
	gera_elecsium(st);
	gera_mobs(st,mob);
	mobs_are_awake(mob,st);
    refresh();

	//ciclo------------------------------------------------------ ---------------------------------------------------------
	while (verificaHP(st) == 1){
		if(verificaFloor(st) == 0) victory(st,audios);
		clear();
		redrawMap(st);
	move(NROWS - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		printw("(%d,%d) %d %d %d",mob[1]->mobX,mob[1]->mobY,st->floor, NROWS,NCOLS);//NCOLS, st->playerX, st->playerY, st->objetivoX, st->objetivoY, NROWS);
		attroff(COLOR_PAIR(COLOR_BLUE));
		


		//Funcoes para luz
		luz(st);//ligar
		verificaLuz(st);
		verificaLuz2(st);



		//menus e jogador
		draw_player(st);
		drawHP();
		drawMP();
		drawHealth(st);
		drawMana(st);




		mvaddch(st->objetivoX,st->objetivoY,(int) 'V' | COLOR_PAIR(CHEGADA));
		movimento_mob(mob,st, audios);
		
		
		
		
		drawElec(st);
		drawMobs(st,mob);
		
		
		cleanMobs(st,mob);
		
		
		
		move(st->playerX, st->playerY);
		

		if(update(st,mob,audios) == 0) {
			resume(st,mob,audios);
			break;
		}
	}
	st->sound = 11; 
	effects(st, audios); 
	endwin(); 
	exit(0); 
	FREE_MOB(mobs); 
	return;
}


int main() {
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