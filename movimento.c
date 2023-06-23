#include "movimento.h"
//#include "utils.h"

//DI 312

//#define DRAWPLAYER 47

void draw_player(STATE *st){
		//mvaddch(st.playerX, st.playerY, '@' | A_BOLD);
		init_pair(DRAWPLAYER,COLOR_BLACK,CHAO);
		switch (st->race)
		{
		case 1:
			st->map[st->playerX][st->playerY] = '@';
			mvaddch(st->playerX, st->playerY, '@' | COLOR_PAIR(DRAWPLAYER));
			break;
		case 2:
			st->map[st->playerX][st->playerY] = 'W';
			mvaddch(st->playerX, st->playerY, 'W' | COLOR_PAIR(DRAWPLAYER));
			break;
		case 3:
			st->map[st->playerX][st->playerY] = 'O'; 
			mvaddch(st->playerX, st->playerY, 'O' | COLOR_PAIR(DRAWPLAYER));
			break;
		case 4:
			st->map[st->playerX][st->playerY] = 'A';
			mvaddch(st->playerX, st->playerY, 'A' | COLOR_PAIR(DRAWPLAYER));
			break;
		}
}


int flagMana(STATE *st){
	if(st->playerMP == MAXMP) return 1;
	return 0;
}


void playerRandom(STATE *st,MOB *mob){
	initializeMobs(mob);
	st->mobs_TOTAIS = 0;
	int y = 0;
	int x = 0;
	clear();
        drawMap(st,NROWS,NCOLS); 
		x = rand() % (NROWS - 7);
		y = rand() % (NCOLS - 2);
		while(1){
			if(st->map[x][y] != (int) '#' && contaVizinhos2(st,x,y) < 4){
    			st->objetivoX = x;
    			st->objetivoY = y;
				break;
			}else{
				x = rand() % (NROWS - 7);
				y = rand() % (NCOLS - 2);
			}
		}
		st->objetivoX = x;
		st->objetivoY = y;
		st->map[st->objetivoX][st->objetivoY] = (int) 'V';
    	mvaddch(st->objetivoX,st->objetivoY,(int) 'V');
		x = rand() % (NROWS - 7);
		y = rand() % (NCOLS - 2);
		while(1){
			if(st->map[x][y] != (int) '#' && contaVizinhos2(st,x,y) < 4){
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
		
		
		
		gera_elecsium(st);
		gera_mobs(st,mob);
		
		
		drawElec(st);
		drawMobs(st,mob);
    	
		
		draw_player(st);
		refresh();
    }


void do_movement_action(STATE *st, int dx, int dy,MOB *mob, AUDIO *audios) {


	if(st->playerMAXMP == 0){
		//apanhar elecsium
		if(st->map[st->playerX + dx][st->playerY + dy] == (int) '^'){
			st->map[st->playerX][st->playerY] = ' ';
			st->playerX += dx;
			st->playerY += dy;

			st->sound = 6;
			effects(st,mob,audios);

			if(st->playerMP > -1 && st->playerMP < 39){ 
				st->playerMP += 10;
				if(st->playerMP == MAXMP) st->playerMAXMP = 1;
				st->map[st->playerX][st->playerY] = ' ';
			}
			else{
				st->playerMP = MAXMP;
				st->playerMAXMP = 1;
				st->map[st->playerX][st->playerY] = ' ';
			}
		}
		//movimento normal
		if(st->map[st->playerX + dx][st->playerY + dy] != (int) '#' && st->map[st->playerX + dx][st->playerY + dy] != (int) 's' && 
		st->map[st->playerX + dx][st->playerY + dy] != (int) 'c' && st->map[st->playerX + dx][st->playerY + dy] != (int) 'p' && 
		st->map[st->playerX + dx][st->playerY + dy] != (int) 'G'){
			st->map[st->playerX][st->playerY] = ' ';
			st->playerX += dx;
			st->playerY += dy;
			//return;
		}
	
		//caso o objetivo seja atingido
    	if(st->playerX == st->objetivoX && st->playerY == st->objetivoY){
			effects(st,mob,audios);
			playerRandom(st,mob);
			st->floor++;
			st->mobs_TOTAIS = 0;
		}
		//return;
	}
	if(st->playerMAXMP == 1){
		//passar em elecsium
		if(st->map[st->playerX + dx][st->playerY + dy] == (int) '^'){
			st->map[st->playerX][st->playerY] = ' ';
			st->playerX += dx;
			st->playerY += dy;
			//st->map[st->playerX][st->playerY] = ' ';
			//st->playerMAXMP = 2;//empurrar elecsium
		}
		//movimento normal
		if(st->map[st->playerX + dx][st->playerY + dy] != (int) '#' && st->map[st->playerX + dx][st->playerY + dy] != (int) 's' && 
		st->map[st->playerX + dx][st->playerY + dy] != (int) 'c' && st->map[st->playerX + dx][st->playerY + dy] != (int) 'p' && 
		st->map[st->playerX + dx][st->playerY + dy] != (int) 'G'){
			st->map[st->playerX][st->playerY] = ' ';
			st->playerX += dx;
			st->playerY += dy;
		}
	
		//caso o objetivo seja atingido
    	if(st->playerX == st->objetivoX && st->playerY == st->objetivoY){
			effects(st,mob,audios);
			playerRandom(st,mob);
			st->floor++;
			st->mobs_TOTAIS = 0;
		}
		//return;
	}




	/*if(st->playerMAXMP == 2){
	if(st->map[st->playerX + dx][st->playerY + dy] != (int) '#'){
		st->playerX += dx;
		st->playerY += dy;
		st->map[st->playerX - dx][st->playerY - dy] = '^';
		st->playerMAXMP = 1;
		//caso o objetivo seja atingido
    	if(st->playerX == st->objetivoX && st->playerY == st->objetivoY){
			playerRandom(st,NROWS,NCOLS);
			st->floor++;
		}
	}
}*/
//return;*/
}


void teletransporte(STATE *st,MOB *mobs,AUDIO *audios){

	//JOGADA BAIXO
	if(st->playanterior == 2){
	int flag = 0;

    for(int i = 5; 1 == 1 ; i++){
	  if(((st->playerX + i ) >= 54) || (st->playerY >= 211) || ((st->playerX + i ) <= 0) || (st->playerY <= 0)){
		flag = 1;
		break;
	  }

      if(st->map[st->playerX + i ][st->playerY] != (int) '#'){
	   st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX + i;
	   st->playerY = st->playerY;
	   
	   if(st->dif == 3){
	   st->playerMP -= 12;
	   }
	   else{
		st->playerMP -= 6;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	  }

	  else{
		continue;
	  }
	 }


	 if(flag == 1){

	 for(int j = 4; j > 0; j--){
	 if(((st->playerX + j ) < 54) && (st->playerY < 211) && ((st->playerX + j ) > 0) && (st->playerY > 0)){
	  
      if(st->map[st->playerX + j ][st->playerY] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX + j;
	   st->playerY = st->playerY;

	   if(st->dif == 3){
	   st->playerMP -= 12;
	   }
	   else{
		st->playerMP -= 6;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	   }
	 }

	  else{
		continue;
	   }
	  }
	 }
	}

    //JOGADA CIMA
	else if(st->playanterior == 8){
	int flag = 0;

    for(int i = 5; 1 == 1 ; i++){
	  if(((st->playerX - i ) >= 54) || (st->playerY >= 211) || ((st->playerX - i ) <= 0) || (st->playerY <= 0)){
		flag = 1;
		break;
	  }

      if(st->map[st->playerX - i ][st->playerY] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX - i;
	   st->playerY = st->playerY;
	   
	   if(st->dif == 3){
	   st->playerMP -= 12;
	   }
	   else{
		st->playerMP -= 6;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	  }

	  else{
		continue;
	  }
	 }
	 

	 if(flag == 1){

	 for(int j = 4; j > 0; j--){
	 if(((st->playerX - j ) < 54) && (st->playerY < 211) && ((st->playerX - j ) > 0) && (st->playerY > 0)){
	  
      if(st->map[st->playerX - j ][st->playerY] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX - j;
	   st->playerY = st->playerY;
	   
	   if(st->dif == 3){
	   st->playerMP -= 12;
	   }
	   else{
		st->playerMP -= 6;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	   }
	 }

	  else{
		continue;
	   }
	  }
	 }
	}

	//JOGADA DIREITA
	if(st->playanterior == 6){
	int flag = 0;

    for(int i = 5; 1 == 1 ; i++){
	  if((st->playerX >= 54) || ((st->playerY + i)>= 211) || (st->playerX <= 0) || ((st->playerY + i) <= 0)){
		flag = 1;
		break;
	  }

      if(st->map[st->playerX][st->playerY + i] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX;
	   st->playerY = st->playerY + i;
	   
	   if(st->dif == 3){
	   st->playerMP -= 12;
	   }
	   else{
		st->playerMP -= 6;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	  }

	  else{
		continue;
	  }
	 }


	 if(flag == 1){

	 for(int j = 4; j > 0; j--){
	 if((st->playerX < 54) && ((st->playerY + j) < 211) && (st->playerX > 0) && ((st->playerY + j) > 0)){
	  
      if(st->map[st->playerX][st->playerY + j] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX;
	   st->playerY = st->playerY + j;

	   if(st->dif == 3){
	   st->playerMP -= 12;
	   }
	   else{
		st->playerMP -= 6;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	   }
	 }

	  else{
		continue;
	   }
	  }
	 }
	}

	//JOGADA ESQUERDA
	if(st->playanterior == 4){
	int flag = 0;

    for(int i = 5; 1 == 1 ; i++){
	  if((st->playerX >= 54) || ((st->playerY - i)>= 211) || (st->playerX <= 0) || ((st->playerY - i) <= 0)){
		flag = 1;
		break;
	  }

      if(st->map[st->playerX][st->playerY - i] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX;
	   st->playerY = st->playerY - i;
	   
	   if(st->dif == 3){
	   st->playerMP -= 12;
	   }
	   else{
		st->playerMP -= 6;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	  }

	  else{
		continue;
	  }
	 }


	 if(flag == 1){

	 for(int j = 4; j > 0; j--){
	 if((st->playerX < 54) && ((st->playerY - j) < 211) && (st->playerX > 0) && ((st->playerY - j) > 0)){
	  
      if(st->map[st->playerX][st->playerY - j] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX;
	   st->playerY = st->playerY - j;

	   if(st->dif == 3){
	   st->playerMP -= 12;
	   }
	   else{
		st->playerMP -= 6;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	   }
	 }

	  else{
		continue;
	   }
	  }
	 }
	}

	//JOGADA CIMA ESQUERDA
	if(st->playanterior == 7){
	int flag = 0;

    for(int i = 4; 1 == 1 ; i++){
	  if(((st->playerX - i) >= 54) || ((st->playerY - i)>= 211) || ((st->playerX - i) <= 0) || ((st->playerY - i) <= 0)){
		flag = 1;
		break;
	  }

      if(st->map[st->playerX - i][st->playerY - i] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX - i;
	   st->playerY = st->playerY - i;
	   
	   if(st->dif == 3){
	   st->playerMP -= 15;
	   }
	   else{
		st->playerMP -= 8;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	  }

	  else{
		continue;
	  }
	 }


	 if(flag == 1){

	 for(int j = 3; j > 0; j--){
	 if(((st->playerX - j)< 54) && ((st->playerY - j) < 211) && ((st->playerX - j) > 0) && ((st->playerY - j) > 0)){
	  
      if(st->map[st->playerX - j][st->playerY - j] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX - j;
	   st->playerY = st->playerY - j;

	   if(st->dif == 3){
	   st->playerMP -= 15;
	   }
	   else{
		st->playerMP -= 8;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	   }
	 }

	  else{
		continue;
	   }
	  }
	 }
	}

	//JOGADA BAIXO ESQUERDA
	if(st->playanterior == 1){
	int flag = 0;

    for(int i = 4; 1 == 1 ; i++){
	  if(((st->playerX + i) >= 54) || ((st->playerY - i)>= 211) || ((st->playerX + i) <= 0) || ((st->playerY - i) <= 0)){
		flag = 1;
		break;
	  }

      if(st->map[st->playerX + i][st->playerY - i] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX + i;
	   st->playerY = st->playerY - i;
	   
	   if(st->dif == 3){
	   st->playerMP -= 15;
	   }
	   else{
		st->playerMP -= 8;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	  }

	  else{
		continue;
	  }
	 }


	 if(flag == 1){

	 for(int j = 3; j > 0; j--){
	 if(((st->playerX + j)< 54) && ((st->playerY - j) < 211) && ((st->playerX + j) > 0) && ((st->playerY - j) > 0)){
	  
      if(st->map[st->playerX + j][st->playerY - j] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX + j;
	   st->playerY = st->playerY - j;

	   if(st->dif == 3){
	   st->playerMP -= 15;
	   }
	   else{
		st->playerMP -= 8;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	   }
	 }

	  else{
		continue;
	   }
	  }
	 }
	}

	//JOGADA CIMA DIREITA
	if(st->playanterior == 9){
	int flag = 0;

    for(int i = 4; 1 == 1 ; i++){
	  if(((st->playerX - i) >= 54) || ((st->playerY + i)>= 211) || ((st->playerX - i) <= 0) || ((st->playerY + i) <= 0)){
		flag = 1;
		break;
	  }

      if(st->map[st->playerX - i][st->playerY + i] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX - i;
	   st->playerY = st->playerY + i;
	   
	   if(st->dif == 3){
	   st->playerMP -= 15;
	   }
	   else{
		st->playerMP -= 8;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	  }

	  else{
		continue;
	  }
	 }


	 if(flag == 1){

	 for(int j = 3; j > 0; j--){
	 if(((st->playerX - j)< 54) && ((st->playerY + j) < 211) && ((st->playerX - j) > 0) && ((st->playerY + j) > 0)){
	  
      if(st->map[st->playerX - j][st->playerY + j] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX - j;
	   st->playerY = st->playerY + j;

	   if(st->dif == 3){
	   st->playerMP -= 15;
	   }
	   else{
		st->playerMP -= 8;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	   }
	 }

	  else{
		continue;
	   }
	  }
	 }
	}

	//JOGADA BAIXO DIREITA
	if(st->playanterior == 3){
	int flag = 0;

    for(int i = 4; 1 == 1 ; i++){
	  if(((st->playerX + i) >= 54) || ((st->playerY + i)>= 211) || ((st->playerX + i) <= 0) || ((st->playerY + i) <= 0)){
		flag = 1;
		break;
	  }

      if(st->map[st->playerX + i][st->playerY + i] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX + i;
	   st->playerY = st->playerY + i;
	   
	   if(st->dif == 3){
	   st->playerMP -= 15;
	   }
	   else{
		st->playerMP -= 8;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	  }

	  else{
		continue;
	  }
	 }


	 if(flag == 1){

	 for(int j = 3; j > 0; j--){
	 if(((st->playerX + j)< 54) && ((st->playerY + j) < 211) && ((st->playerX + j) > 0) && ((st->playerY + j) > 0)){
	  
      if(st->map[st->playerX + j][st->playerY + j] != (int) '#'){
		st->map[st->playerX][st->playerY] = ' ';
       st->playerX = st->playerX + j;
	   st->playerY = st->playerY + j;

	   if(st->dif == 3){
	   st->playerMP -= 15;
	   }
	   else{
		st->playerMP -= 8;
	   }


	   st->sound = 7;
	   effects(st,mobs,audios);

	   break;
	   }
	 }

	  else{
		continue;
	   }
	  }
	 }
	}
}



int update(STATE *st,MOB *mob, AUDIO *audios) {
	int key = getch();

	if(key == '5') return 1; // retirar se necessario
	mvaddch(st->playerX, st->playerY, ' ' | COLOR_PAIR(COLOR_CHAO));
	switch(key) {
		case KEY_A1:
		case '7': st->playanterior = 7; do_movement_action(st, -1, -1,mob, audios); limpaLuz(st); return 1; break;
		case KEY_UP:
		case '8': st->playanterior = 8; do_movement_action(st, -1, +0,mob, audios); limpaLuz(st); return 1; break;
		case KEY_A3:
		case '9': st->playanterior = 9; do_movement_action(st, -1, +1,mob, audios); limpaLuz(st); return 1; break;
		case KEY_LEFT:
		case '4': st->playanterior = 4; do_movement_action(st, +0, -1,mob, audios); limpaLuz(st); return 1; break;
		case KEY_B2:
		case '5': limpaLuz(st); return 1; break;
		case KEY_RIGHT:
		case '6': st->playanterior = 6; do_movement_action(st, +0, +1,mob, audios); limpaLuz(st); return 1; break;
		case KEY_C1:
		case '1': st->playanterior = 1; do_movement_action(st, +1, -1,mob, audios); limpaLuz(st); return 1; break;
		case KEY_DOWN:
		case '2': st->playanterior = 2; do_movement_action(st, +1, +0,mob, audios); limpaLuz(st); return 1; break;
		case KEY_C3:
		case '3': st->playanterior = 3; do_movement_action(st, +1, +1,mob, audios); limpaLuz(st); return 1; break;
		case 'Q':
		case 'q': st->sound = 11; effects(st,mob,audios); endwin(); exit(0); FREE_MOB(mob); return 1; break;
		case 'C':
		case 'c': if(st->playerMP < 49 && st->playerMP > -1) st->playerMP++; return 1; break;
		case 'O':
		case 'o': st->sound = -2; som(st,mob,audios); return 0;break;
		case 'H':
		case 'h': if(st->playerMP > 9){/*st->playerMP -= 10*/;st->playerX = st->objetivoX; st->playerY = st->objetivoY - 1; st->playerMAXMP = 0;} break;
		case 'T':
		case 't': if((st->playerMP > 11 && st->dif == 3 && (st->playanterior == 2 || st->playanterior == 4 || st->playanterior == 6 || st->playanterior == 8)) ||
		             (st->playerMP > 5 && st->dif != 3 && (st->playanterior == 2 || st->playanterior == 4 || st->playanterior == 6 || st->playanterior == 8)) ||
					 ((st->playanterior == 1 || st->playanterior == 3 || st->playanterior == 7 || st->playanterior == 9) && st->playerMP > 14 && st->dif == 3) || 
					 ((st->playanterior == 1 || st->playanterior == 3 || st->playanterior == 7 || st->playanterior == 9) && st->playerMP > 7 && st->dif != 3)){

			          teletransporte(st,mob,audios);
		              st->playerMAXMP = 0;
					  limpaLuz(st);
				    }
			        break;
		case 'E':
		case 'e': st->arma = 1; break;
		case 'R':
		case 'r': st->arma = 2; break;
		case 'z':
		case 'Z': st->playerHP = 0; break;
	}
	return 1;
}