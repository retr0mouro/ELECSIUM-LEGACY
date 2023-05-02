#include "movimento.h"

/*
 *
 * Falta muita coisa, incluindo por exemplo:
 * - o mapa
 * - os monstros
 * - a fila de prioridade para saber quem se move
 * - o que está em cada casa
 *
 */

/*
 *
 * Um pequeno exemplo que mostra o que se pode fazer
 */

void repeat(STATE *st,int nrows){
	menu1(st);
    clear();
    drawMap(st);
	
	int x = rand() % 52;
	int y = rand() % 209;
	while(1){
		if(st->map[x][y] != (int) '#'){
    		st->objetivoX = x;
    		st->objetivoY = y;
			break;
		}else{
			x = rand() % 52;
			y = rand() % 209;
		}
	}
	st->objetivoX = x;
	st->objetivoY = y;
	

	
	x = rand() % 52;
	y = rand() % 209;
	while(1){
		if(st->map[x][y] != (int) '#'){
    		st->playerX = x;
    		st->playerY = y;
			break;
		}else{
			x = rand() % 52;
			y = rand() % 209;
		}
	}
	st->playerX = x;
	st->playerY = y;
    draw_player(st);
    
	st->map[st->objetivoX][st->objetivoY] = (int) 'V';
    mvaddch(st->objetivoX,st->objetivoY,(int) 'V'|A_REVERSE);
    refresh();

	
	while (1){
	move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		printw("(%d, %d) %d %d", st->playerX, st->playerY, st->objetivoX, st->objetivoY);
		attroff(COLOR_PAIR(COLOR_BLUE));
		draw_player(st);
		drawHealth(st);
		drawMana(st);
		//attron(COLOR_PAIR(COLOR_YELLOW));
		mvaddch(st->playerX - 1, st->playerY - 1, st->map[st->playerX - 1][st->playerY - 1]);
		mvaddch(st->playerX - 1, st->playerY + 0, st->map[st->playerX - 1][st->playerY + 0]);
		mvaddch(st->playerX - 1, st->playerY + 1, st->map[st->playerX - 1][st->playerY + 1]);
		mvaddch(st->playerX + 0, st->playerY - 1, st->map[st->playerX + 0][st->playerY - 1]);
		mvaddch(st->playerX + 0, st->playerY + 1, st->map[st->playerX + 0][st->playerY + 1]);
		mvaddch(st->playerX + 1, st->playerY - 1, st->map[st->playerX + 1][st->playerY - 1]);
		mvaddch(st->playerX + 1, st->playerY + 0, st->map[st->playerX + 1][st->playerY + 0]);
		mvaddch(st->playerX + 1, st->playerY + 1, st->map[st->playerX + 1][st->playerY + 1]);
        //attroff(COLOR_PAIR(COLOR_YELLOW));
		move(st->playerX, st->playerY);
		//st.playerMP--;
		if(update(st) == 0) {
			repeat(st,nrows);
			break;
		}
	}
}


int main() {
    initscr();
    //int map[59][211] = {{0}};
	//STATE st = {12,20,0,0,0,0};
	WINDOW *wnd = initscr();
    //wborder(wnd,'#','#','#','#','#','#','#','#');
	int ncols, nrows;
	getmaxyx(wnd,nrows,ncols);
    (void) ncols;

	srand(time(NULL));

	
	start_color();

    //int x1 = rand() % 209, x2 = rand() % 209, y1 = rand() % 57, y2 = rand() % 57;

	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
        init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
        init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);


	repeat(&st,nrows);
	/**
	 * Este código está muito mal escrito!
	 * Deveria existir uma função chamada draw_player!
	 *
	 * Se estamos a desenhar uma luz à volta do jogador
	 * deveria existir uma função chamada draw_light!
	 *
	 */
    /*menu1(&st);
    clear();
    drawMap(&st);
	
	int x = rand() % 52;
	int y = rand() % 209;
	while(1){
		if(st.map[x][y] != (int) '#'){
    		st.objetivoX = x;
    		st.objetivoY = y;
			break;
		}else{
			x = rand() % 52;
			y = rand() % 209;
		}
	}
	st.objetivoX = x;
	st.objetivoY = y;
	


	x = rand() % 52;
	y = rand() % 209;
	while(1){
		if(st.map[x][y] != (int) '#'){
    		st.playerX = x;
    		st.playerY = y;
			break;
		}else{
			x = rand() % 52;
			y = rand() % 209;
		}
	}
	st.playerX = x;
	st.playerY = y;
    draw_player(&st);
    
	st.map[st.objetivoX][st.objetivoY] = (int) 'V';
    mvaddch(st.objetivoX,st.objetivoY,(int) 'V'|A_REVERSE);
    refresh();
	while(1) {
		move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		printw("(%d, %d) %d %d", st.playerX, st.playerY, st.objetivoX, st.objetivoY);
		attroff(COLOR_PAIR(COLOR_BLUE));
		draw_player(&st);
		drawHealth(&st);
		drawMana(&st);
		//attron(COLOR_PAIR(COLOR_YELLOW));
		mvaddch(st.playerX - 1, st.playerY - 1, st.map[st.playerX - 1][st.playerY - 1]);
		mvaddch(st.playerX - 1, st.playerY + 0, st.map[st.playerX - 1][st.playerY + 0]);
		mvaddch(st.playerX - 1, st.playerY + 1, st.map[st.playerX - 1][st.playerY + 1]);
		mvaddch(st.playerX + 0, st.playerY - 1, st.map[st.playerX + 0][st.playerY - 1]);
		mvaddch(st.playerX + 0, st.playerY + 1, st.map[st.playerX + 0][st.playerY + 1]);
		mvaddch(st.playerX + 1, st.playerY - 1, st.map[st.playerX + 1][st.playerY - 1]);
		mvaddch(st.playerX + 1, st.playerY + 0, st.map[st.playerX + 1][st.playerY + 0]);
		mvaddch(st.playerX + 1, st.playerY + 1, st.map[st.playerX + 1][st.playerY + 1]);
        //attroff(COLOR_PAIR(COLOR_YELLOW));
		move(st.playerX, st.playerY);
		//st.playerMP--;
		update(&st);
		//player_move(&st,58);
		repeat(&st,nrows);
	}*/

	return 0;
}