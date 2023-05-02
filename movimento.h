#include "mapa.h"

void draw_player(STATE *st){
	attron(COLOR_PAIR(COLOR_WHITE));
		//mvaddch(st.playerX, st.playerY, '@' | A_BOLD);
		switch (st->race)
		{
		case 1:
			mvaddch(st->playerX, st->playerY, '@' | A_BOLD);
			break;
		case 2:
			mvaddch(st->playerX, st->playerY, 'W' | A_BOLD);
			break;
		case 3: 
			mvaddch(st->playerX, st->playerY, 'O' | A_BOLD);
			break;
		case 4:
			mvaddch(st->playerX, st->playerY, 'A' | A_BOLD);
			break;
		}
		attroff(COLOR_PAIR(COLOR_WHITE));
}



void do_movement_action(STATE *st, int dx, int dy) {
	int y = 0;
	int x = 0;


	//movimento normal
	if(st->map[st->playerX + dx][st->playerY + dy] != (int) '#'){
		st->playerX += dx;
		st->playerY += dy;
	}


	
	//caso o objetivo seja atingido
    if(st->playerX == st->objetivoX && st->playerY == st->objetivoY){
		clear();
        drawMap(st); 
		x = rand() % 52;
		y = rand() % 209;
		while(1){
			if(st->map[x][y] != (int) '#' && contaVizinhos2(st,x,y) < 4){
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
		st->map[st->objetivoX][st->objetivoY] = (int) 'V';
    	mvaddch(st->objetivoX,st->objetivoY,(int) 'V' | A_REVERSE);
		x = rand() % 52;
		y = rand() % 209;
		while(1){
			if(st->map[x][y] != (int) '#' && contaVizinhos2(st,x,y) < 4){
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
    }
	if(st->playerMP > 1) st->playerMP--;
	//else st->playerMP = 10;
	//printw("%d",st->playerMP);
}



int update(STATE *st) {
	int key = getch();

	mvaddch(st->playerX, st->playerY, ' ');
	switch(key) {
		case KEY_A1:
		case '7': do_movement_action(st, -1, -1); return 1; break;
		case KEY_UP:
		case '8': do_movement_action(st, -1, +0); return 1; break;
		case KEY_A3:
		case '9': do_movement_action(st, -1, +1); return 1; break;
		case KEY_LEFT:
		case '4': do_movement_action(st, +0, -1); return 1; break;
		case KEY_B2:
		case '5': return 1; break;
		case KEY_RIGHT:
		case '6': do_movement_action(st, +0, +1); return 1; break;
		case KEY_C1:
		case '1': do_movement_action(st, +1, -1); return 1; break;
		case KEY_DOWN:
		case '2': do_movement_action(st, +1, +0); return 1; break;
		case KEY_C3:
		case '3': do_movement_action(st, +1, +1); return 1; break;
		case 'q': endwin(); exit(0); return 1; break;
		case 'c': if(st->playerMP < 49 && st->playerMP > 0) st->playerMP++; return 1; break;
		case 'h': st->playerX = st->objetivoX; st->playerY = st->objetivoY - 1; return 1; break;
		case 'o': return 0;break;
		//case KEY_BACKSPACE: ;
	}
}

