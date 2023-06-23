#include "mobs.h"
//#include "estado.h"
//#include "utils.h"

//Verificar se os andares não passam dos seus limites | FUNCIONA
int verificaFloor(STATE *st){
	switch(st->dif){
		case 1:
			if(st->floor < 11)
			return 1;
			break;
		case 2:
			if(st->floor < 16)
			return 1;
			break;
		case 3:
			if(st->floor < 101)
			return 1;
			break;
    default:
      return 1;
	}
	return 0;
}


//Verificar se o jogador não morreu | FUNCIONA
int verificaHP(STATE *st){
  if(st->playerHP <= 0) return 0;
  return 1;
}


//Inicializar os mobs | FUNCIONA
void initializeMobs(MOB *mobs){
  for(int i = 0;i < 30;i++){
    mobs[i]->mobX = i;
    mobs[i]->mobY = i + 2;
    mobs[i]->vida = 0;
    mobs[i]->qual_mob = 0;
    mobs[i]->awake = 0;
    mobs[i]->indice = 0;
  }
}


/*int mobsOverlap(STATE *st,MOB *mobs){
  for(int i = 0;i < st->mobs_TOTAIS;i++){
    for(int j = 0;j < st->mobs_TOTAIS;j++){
      if(mobs[i]->mobX == mobs[j]->mobX && mobs[i]->mobY == mobs[j]->mobY) return 1;
    }
  }
  return 0;
}*/

void cleanMobs(STATE *st,MOB *mob){
  for(int i = 0; mob[i]->indice ; i++){
    if(mob[i]->vida <= 0) {
      st->map[mob[i]->mobX][mob[i]->mobY] = '.';
      mvaddch(mob[i]->mobX,mob[i]->mobY,'.' | COLOR_PAIR(COLOR_PONTO));
      mob[i]->mobX = 0;
      mob[i]->mobY = 0;
    }
  }
}



// Fixando o Y do mob, verifica na linha do mesmo, o local mais próximo possível
// de ser uma casa para o mob, ou seja, não é parede, jogador, objetivo ou
// elecsium
int x_mais_perto(MOB mob, STATE *st) {
  int x_positivo = mob->mobX + 1;
  int x_negativo = mob->mobX - 1;
  int x_mais_perto;
  while(st->map[x_positivo][mob->mobY] != ' ' && x_positivo < 53) {
    x_positivo++;
  }
  while(st->map[x_negativo][mob->mobY] != ' ' && x_negativo > 0) {
    x_negativo--;
  }
  
  if(mob->mobX - x_negativo >= x_positivo - mob->mobX) x_mais_perto = x_negativo;
    else x_mais_perto = x_positivo;
  if(x_negativo <= 0 || x_positivo >= 53) x_mais_perto = -1;

  return x_mais_perto;
}

// Fixando o X do mob, verifica na coluna do mesmo, o local mais próximo
// possível de ser uma casa para o mob, ou seja, não é parede, jogador, objetivo
// ou elecsium
int y_mais_perto(MOB mob, STATE *st) {
  int y_positivo = mob->mobY + 1;
  int y_negativo = mob->mobY - 1;
  int y_mais_perto;
  while(st->map[mob->mobX][y_positivo] != ' ' && y_positivo < 53) {
    y_positivo++;
  }
  while(st->map[mob->mobX][y_negativo] != ' ' && y_negativo > 0) {
    y_negativo--;
  }
  
  if(mob->mobX - y_negativo >= y_positivo - mob->mobX) y_mais_perto = y_negativo;
    else y_mais_perto = y_positivo;
  if(y_negativo <= 0 || y_positivo >= 53) y_mais_perto = -1;
  
  return y_mais_perto;
}

// Gera uma quantidade de elecsium aleatoriamente no mapa, dependendo da
// dificuldade;   | FUNCIONA
void gera_elecsium(STATE *st) {
  init_pair(ELEC,COLOR_BLACK,COLOR_CYAN);
  int dificuldade = 2;
  if (st->dif == 2)
    dificuldade = 2;
  else if (st->dif == 3)
    dificuldade = 3;

  int qt_elecsium = dificuldade;
  for (int i = st->floor; i > 4; i -= 5) qt_elecsium++;


  for (; qt_elecsium > 0; qt_elecsium--) {
    int x = rand() % 52;
    int y = rand() % 209;
    while (1) {
      if (st->map[x][y] == (int) ' ') {
        break;
      } else {
        x = rand() % 52;
        y = rand() % 209;
      }
    }
    st->map[x][y] = (int) '^';
    mvaddch(x,y,'^' | COLOR_PAIR(ELEC));
  }
}

// Verifica se existem paredes entre o jogador e o mob, returnando 0 se houver
// uma parede entre eles
int pode_snipar(MOB mob, STATE *st) {
  int xDoMob = mob->mobX;
  int yDoMob = mob->mobY;

  while(xDoMob != st->playerX || yDoMob != st->playerY) {

    if(xDoMob < st->playerX && yDoMob < st->playerY) { // cima esquerda
      if(st->map[xDoMob][yDoMob] == '#' || st->map[xDoMob + 1][yDoMob] == '#' || st->map[xDoMob][yDoMob + 1] == '#') return 0;

      xDoMob++;
      yDoMob++;
    }

    if(xDoMob > st->playerX && yDoMob < st->playerY) { // baixo esquerda
      if(st->map[xDoMob][yDoMob] == '#' || st->map[xDoMob - 1][yDoMob] == '#' || st->map[xDoMob][yDoMob + 1] == '#') return 0;

      xDoMob--;
      yDoMob++;
    }

    if(xDoMob < st->playerX && yDoMob > st->playerY) { // cima direita
      if(st->map[xDoMob][yDoMob] == '#' || st->map[xDoMob + 1][yDoMob] == '#' || st->map[xDoMob][yDoMob - 1] == '#') return 0;

      xDoMob++;
      yDoMob--;
    }

    if(xDoMob > st->playerX && yDoMob > st->playerY) { // baixo direita
      if(st->map[xDoMob][yDoMob] == '#' || st->map[xDoMob - 1][yDoMob] == '#' || st->map[xDoMob][yDoMob - 1] == '#') return 0;

      xDoMob--;
      yDoMob--;
    }

    if(xDoMob < st->playerX && yDoMob == st->playerY) {
      if(st->map[xDoMob][yDoMob] == '#') return 0;

      xDoMob++;
    }

    if(xDoMob > st->playerX && yDoMob == st->playerY) {
      if(st->map[xDoMob][yDoMob] == '#') return 0;

      xDoMob--;
    }

    if(xDoMob == st->playerX && yDoMob < st->playerY) {
      if(st->map[xDoMob][yDoMob] == '#') return 0;

      yDoMob++;
    }

    if(xDoMob == st->playerX && yDoMob > st->playerY) {
      if(st->map[xDoMob][yDoMob] == '#') return 0;

      yDoMob--;
    }
  }

  return 1;
}

// Calcula a distancia entre o mob e o jogador.
int distancia_ideal(MOB mob, STATE *st) {
  int distancia = 0;
  int xDoMob = mob->mobX;
  int yDoMob = mob->mobY;

  while(xDoMob != st->playerX || yDoMob != st->playerY) {

    if(xDoMob < st->playerX && yDoMob < st->playerY) { // cima esquerda
      xDoMob++;
      yDoMob++;
      distancia++;
    }

    if(xDoMob > st->playerX && yDoMob < st->playerY) { // baixo esquerda
      xDoMob--;
      yDoMob++;
      distancia++;
    }

    if(xDoMob < st->playerX && yDoMob > st->playerY) { // cima direita
      xDoMob++;
      yDoMob--;
      distancia++;
    }

    if(xDoMob > st->playerX && yDoMob > st->playerY) { // baixo direita
      xDoMob--;
      yDoMob--;
      distancia++;
    }

    if(xDoMob < st->playerX && yDoMob == st->playerY) { // cima
      xDoMob++;
      distancia++;
    }

    if(xDoMob > st->playerX && yDoMob == st->playerY) { // baixo
      xDoMob--;
      distancia++;
    }

    if(xDoMob == st->playerX && yDoMob < st->playerY) { // esquerda
      yDoMob++;
      distancia++;
    }

    if(xDoMob == st->playerX && yDoMob > st->playerY) { // direita
      yDoMob--;
      distancia++;
    }
  }

  return distancia;
}

// Calcula a nova distância do jogador ao mob->
int nova_distancia(int x, int y, STATE *st) {
  int distancia = 0;

  while(x != st->playerX || y != st->playerY) {

    if(x < st->playerX && y < st->playerY) { // cima esquerda
      x++;
      y++;
      distancia++;
    }

    if(x > st->playerX && y < st->playerY) { // baixo esquerda
      x--;
      y++;
      distancia++;
    }

    if(x < st->playerX && y > st->playerY) { // cima direita
      x++;
      y--;
      distancia++;
    }

    if(x > st->playerX && y > st->playerY) { // baixo direita
      x--;
      y--;
      distancia++;
    }

    if(x < st->playerX && y == st->playerY) { // cima
      x++;
      distancia++;
    }

    if(x > st->playerX && y == st->playerY) { // baixo
      x--;
      distancia++;
    }

    if(x == st->playerX && y < st->playerY) { // esquerda
      y++;
      distancia++;
    }

    if(x == st->playerX && y > st->playerY) { // direita
      y--;
      distancia++;
    }
  }

  return distancia;
}

// Calcula a distancia entre mobs || 
int distancia_mobeal(MOB mob, MOB sta) {
  int distancia = 0;
  int xDoMob = mob->mobX;
  int yDoMob = mob->mobY;
  int xRandomMob = sta->mobX;
  int yRandomMob = sta->mobY;

  while(xDoMob != xRandomMob || yDoMob != yRandomMob) {

    if(xDoMob < xRandomMob && yDoMob < yRandomMob) {
      xDoMob++;
      yDoMob++;
      distancia++;
    }

    if(xDoMob > xRandomMob && yDoMob < yRandomMob) {
      xDoMob--;
      yDoMob++;
      distancia++;
    }

    if(xDoMob < xRandomMob && yDoMob > yRandomMob) {
      xDoMob++;
      yDoMob--;
      distancia++;
    }

    if(xDoMob > xRandomMob && yDoMob > yRandomMob) {
      xDoMob--;
      yDoMob--;
      distancia++;
    }

    if(xDoMob < xRandomMob && yDoMob == yRandomMob) {
      xDoMob++;
      distancia++;
    }

    if(xDoMob > xRandomMob && yDoMob == yRandomMob) {
      xDoMob--;
      distancia++;
    }

    if(xDoMob == xRandomMob && yDoMob < yRandomMob) {
      yDoMob++;
      distancia++;
    }

    if(xDoMob == xRandomMob && yDoMob > yRandomMob) {
      yDoMob--;
      distancia++;
    }
  }

  return distancia;
}

// Gera mobs aleatoriamente no mapa, sendo que a quantidade varia com a
// dificuldade escolhida, e o tipo de mobs varia aleatoriamente.
void gera_mobs(STATE *st, MOB *mob) {
  if(verificaFloor(st) == 0) return;

    //init_pair(MOBS,COLOR_RED,CHAO);
    //init_pair(BOSS,COLOR_CYAN,COLOR_RED);

  int dificuldade = 1;
  if (st->dif == 2) dificuldade = 2;
  else if (st->dif == 3) dificuldade = 3;
  
  int qts_Mobs = 1;
  for (int i = st->floor; i > 4; i -= 5) qts_Mobs++;

  for(; qts_Mobs > 0; qts_Mobs--) {
    
    if(st->floor % 5 != 0) {
      int random_mob = rand() % 3;
        int x = 0;
        int y = 0;
      switch (random_mob) {
      case 0: // shock beetles
        for(int i = 0; i < 4 && st->mobs_TOTAIS < 29; i++) {
          x = rand() % 52;
          y = rand() % 209;

          while(1) {
            if(st->map[x][y] == ' '//st->map[x][y] != (int) 'x' && st->map[x][y] != (int) 'z' && st->map[x][y] != (int) '$' && st->map[x][y] != (int) 'P' && st->map[x][y] != (int) '#' && st->map[x][y] != (int) '^' && (x != st->playerX && y != st->playerY)
               && x > 4 && y > 4 && x < 50 && y < 205) {
              mob[st->mobs_TOTAIS]->mobX = x;
              mob[st->mobs_TOTAIS]->mobY = y;
              mob[st->mobs_TOTAIS]->vida = 15 + st->floor * dificuldade;
              mob[st->mobs_TOTAIS]->qual_mob = 0;
              mob[st->mobs_TOTAIS]->indice = st->mobs_TOTAIS + 1;
              st->mobs_TOTAIS++;
              break;
            } else {
              x = rand() % 52;
              y = rand() % 209;
            }
          }
          st->map[x][y] = (int)'s';
          mvaddch(x,y,'s' | COLOR_PAIR(MOBS));
        }
        break;

      case 1: // Circuit Crawlers
        for(int i = 0; i < 5 && st->mobs_TOTAIS < 29; i++) {
          x = rand() % 52;
          y = rand() % 209;

          while(1) {
            if(st->map[x][y] == ' '//st->map[x][y] != (int) 'x' && st->map[x][y] != (int) 'z' && st->map[x][y] != (int) '$' && st->map[x][y] != (int) 'P' && st->map[x][y] != (int) '#' && st->map[x][y] != (int) '^'&& (x != st->playerX && y != st->playerY)
               && x > 4 && y > 4 && x < 50 && y < 205) {
              mob[st->mobs_TOTAIS]->mobX = x;
              mob[st->mobs_TOTAIS]->mobY = y;
              mob[st->mobs_TOTAIS]->vida = 20 + st->floor * dificuldade;
              mob[st->mobs_TOTAIS]->qual_mob = 1;
              mob[st->mobs_TOTAIS]->indice = st->mobs_TOTAIS + 1;
              st->mobs_TOTAIS++;
              break;
            } else {
              x = rand() % 52;
              y = rand() % 209;
            }
          }
          st->map[x][y] = (int)'c';
          mvaddch(x,y,'c' | COLOR_PAIR(MOBS));
        }
        break;

      case 2: // Plasma Bats
      if(st->mobs_TOTAIS < 29){
        //label
        novo_bat:
        x = rand() % 52;
        y = rand() % 209;
        while(1) {

          if(st->map[x][y] == ' '//st->map[x][y] != (int) 'x' && st->map[x][y] != (int) 'z' && st->map[x][y] != (int) '$' && st->map[x][y] != (int) 'P' && st->map[x][y] != (int) '#' && st->map[x][y] != (int) '^' (x != st->playerX && y != st->playerY) && st->map[x][y] != '.'
             && x > 4 && y > 4 && x < 50 && y < 205) {
            mob[st->mobs_TOTAIS]->mobX = x;
            mob[st->mobs_TOTAIS]->mobY = y;
            mob[st->mobs_TOTAIS]->vida = 10 + st->floor * dificuldade;
            mob[st->mobs_TOTAIS]->qual_mob = 2;
            mob[st->mobs_TOTAIS]->indice = st->mobs_TOTAIS + 1;
            st->mobs_TOTAIS++;
            break;
          } else {
            x = rand() % 52;
            y = rand() % 209;
          }
        }
        st->map[x][y] = (int)'p';
      }
        mvaddch(x,y,'p' | COLOR_PAIR(MOBS));

        for(int i = 1; i < 3 && st->mobs_TOTAIS < 29; i++) {
          //x = rand() % 52;
          //y = rand() % 209;

          int novoX = x_mais_perto(mob[st->mobs_TOTAIS - i], st);
          int novoY = y_mais_perto(mob[st->mobs_TOTAIS - i], st);
          if(novoX == -1 && novoY == -1){ //ir para label
            st->mobs_TOTAIS--;
            goto novo_bat;
          }
          mob[st->mobs_TOTAIS]->mobX = novoX;
          mob[st->mobs_TOTAIS]->mobY = novoY;
          mob[st->mobs_TOTAIS]->vida = 10 + st->floor * dificuldade;
          mob[st->mobs_TOTAIS]->qual_mob = 2;
          mob[st->mobs_TOTAIS]->indice = st->mobs_TOTAIS + 1;


          if(st->map[mob[st->mobs_TOTAIS]->mobX][mob[st->mobs_TOTAIS]->mobY] != ' ' && distancia_mobeal(mob[st->mobs_TOTAIS - i], mob[st->mobs_TOTAIS]) > 1) {
            if(abs(novoY - y) < abs(novoX - x) /*&& x > 4 && y > 4 && x < 50 && y < 205 && st->map[x][y] != '.'*/) {
              mob[st->mobs_TOTAIS]->mobY = y;
              
            } else {
              mob[st->mobs_TOTAIS]->mobX = x;
              
            }
          }
          
          st->map[mob[st->mobs_TOTAIS]->mobX][mob[st->mobs_TOTAIS]->mobY] = (int)'p';
          st->mobs_TOTAIS++;
          mvaddch(mob[st->mobs_TOTAIS]->mobX , mob[st->mobs_TOTAIS]->mobY , 'p' | COLOR_PAIR(MOBS));
        }
        break;
      }
    } else { // mini boss Storm Giant
      int x;
      int y;
      x = rand() % 52;
      y = rand() % 209;
      while(1) {
        if(st->map[x][y] == ' '/*st->map[x][y] != (int) 'x' && st->map[x][y] != (int) 'z' && st->map[x][y] != (int) '$' && st->map[x][y] != (int) 'P' && st->map[x][y] != (int) '#' && st->map[x][y] != (int) '^' */
           && x > 4 && y > 4 && x < 50 && y < 205) {
          mob[st->mobs_TOTAIS]->mobX = x;
          mob[st->mobs_TOTAIS]->mobY = y;
          mob[st->mobs_TOTAIS]->vida = 100 + st->floor * dificuldade * 2;
          mob[st->mobs_TOTAIS]->qual_mob = 3;
          mob[st->mobs_TOTAIS]->indice = st->mobs_TOTAIS + 1;
          mob[st->mobs_TOTAIS]->awake = 1;
          st->mobs_TOTAIS++;
          break;
        } else {
          x = rand() % 52;
          y = rand() % 209;
        }
      }
      st->map[x][y] = (int)'G';
      mvaddch(x,y,'G' | COLOR_PAIR(BOSS));
      break;
    }
  }
  //st->mobs_TOTAIS = st->mobs_TOTAIS;
}

// Verifica qual o indice do mob mais proximo da lista de mobs, tendo como ponto
// de referencia o jogador
int nearest_mob(MOB *mob, STATE *st) {
  int menos_vida = 0;
  int closest_mob = 0;
  int distancia = 696;
  for(int i = 0; mob[i]->indice; i++) {

    if(mob[i]->vida > 0 && distancia_ideal(mob[i], st) < distancia && pode_snipar(mob[i], st)) {
      menos_vida = mob[i]->vida;
      distancia = distancia_ideal(mob[i], st);
      closest_mob = mob[i]->indice;
    } else {
      if(mob[i]->vida > 0 && distancia_ideal(mob[i], st) == distancia && pode_snipar(mob[i], st) &&
          mob[i]->vida < menos_vida) {
        menos_vida = mob[i]->vida;
        closest_mob = mob[i]->indice;
      }
    }
  }
  return closest_mob;
}

// verifica qual o indice do mob mais proximo do player, excluindo o mob de referência
int nearest_comrade(MOB mob, MOB *mobs, STATE *st) {
  int closest_mob = 0;
  int distancia = 696;

    for(int i = 0; mobs[i]->indice; i++) {
    if(mobs[i]->vida > 0 && (mobs[i]->mobX != mob->mobX || mobs[i]->mobY != mob->mobY) && distancia_ideal(mobs[i], st) < distancia /*&& pode_snipar(mob, mobs[i])*/) {
      distancia = distancia_ideal(mobs[i], st);
      closest_mob = mobs[i]->indice;
    }
  }
  return closest_mob;
}

// Verifica se a posicao esta na lista
int esta_na_lista(int posicoes[], int posicao, int repeticoes) {

  for(int i = 0; i < repeticoes; i++) {
    if(posicoes[i] == posicao) return 1;
  }
  return 0;
}

// Algoritmo para aproximar o mob do jogador
void aproxima_do_player(MOB mob, STATE *st) {
  int posicao = rand() % 8;
  int posicoes[8];
  int repeticoes = 0;
  while(repeticoes < 8) { // fica stuck numa parede
    if(posicao == 1 && (st->map[mob->mobX - 1][mob->mobY + 1] == ' ' || st->map[mob->mobX - 1][mob->mobY + 1] == '.') && nova_distancia(mob->mobX - 1, mob->mobY + 1, st) <= distancia_ideal(mob, st)) {
      mob->mobX--;
      mob->mobY++;
      break;
    } else { // cima direita
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 1;
      repeticoes++;
    }

    if(posicao == 2 && (st->map[mob->mobX][mob->mobY + 1] == ' ' || st->map[mob->mobX][mob->mobY + 1] == '.') && nova_distancia(mob->mobX, mob->mobY + 1, st) <= distancia_ideal(mob, st)) {
      mob->mobY++;
      break;
    } else { // direita
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 2;
      repeticoes++;
    }

    if(posicao == 3 && (st->map[mob->mobX + 1][mob->mobY + 1] == ' ' || st->map[mob->mobX + 1][mob->mobY + 1] == '.') && nova_distancia(mob->mobX + 1, mob->mobY + 1, st) <= distancia_ideal(mob, st)) {
      mob->mobX++;
      mob->mobY++;
      break;
    } else { // baixo direita
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 3;
      repeticoes++;
    }

    if(posicao == 4 && (st->map[mob->mobX + 1][mob->mobY] == ' ' || st->map[mob->mobX + 1][mob->mobY] == '.') && nova_distancia(mob->mobX + 1, mob->mobY, st) <= distancia_ideal(mob, st)) {
      mob->mobX++;
      break;
    } else { // baixo
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 4;
      repeticoes++;
    }

    if(posicao == 5 && (st->map[mob->mobX + 1][mob->mobY - 1] == ' ' || st->map[mob->mobX + 1][mob->mobY - 1] == '.') && nova_distancia(mob->mobX + 1, mob->mobY - 1, st) <= distancia_ideal(mob, st)) {
      mob->mobX++;
      mob->mobY--;
      break;
    } else { // baixo esquerda
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 5;
      repeticoes++;
    }

    if(posicao == 6 && (st->map[mob->mobX][mob->mobY - 1] == ' ' || st->map[mob->mobX][mob->mobY - 1] == '.') && nova_distancia(mob->mobX, mob->mobY - 1, st) <= distancia_ideal(mob, st)) {
      mob->mobY--;
      break;
    } else { // esquerda
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 6;
      repeticoes++;
    }

    if(posicao == 7 && (st->map[mob->mobX - 1][mob->mobY - 1] == ' ' || st->map[mob->mobX - 1][mob->mobY - 1] == '.') && nova_distancia(mob->mobX - 1, mob->mobY - 1, st) <= distancia_ideal(mob, st)) {
      mob->mobX--;
      mob->mobY--;
      break;
    } else { // cima esquerda
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 7;
      repeticoes++;
    }

    if(posicao == 0 && (st->map[mob->mobX - 1][mob->mobY] == ' ' || st->map[mob->mobX - 1][mob->mobY] == '.') && nova_distancia(mob->mobX - 1, mob->mobY, st) <= distancia_ideal(mob, st)) {
      mob->mobX--;
      break;
    } else { // cima
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 0;
      repeticoes++;
    }
  }
}

// Algoritmo de fuga para os mobs covardes, ou seja, fogem se sozinhos
void foge_do_player(MOB mob, STATE *st) {
  int posicao = rand() % 8;
  int posicoes[8];
  int repeticoes = 0;
  while(repeticoes < 8) { // n tem para onde fugir logo fica com medo e não faz nada
    if(posicao == 1 && (st->map[mob->mobX - 1][mob->mobY + 1] == ' ' || st->map[mob->mobX - 1][mob->mobY + 1] == '.') && nova_distancia(mob->mobX - 1, mob->mobY + 1, st) > distancia_ideal(mob, st)) {
      mob->mobX--;
      mob->mobY++;
      break;
    } else { // cima direita
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 1;
      repeticoes++;
    }

    if(posicao == 2 && (st->map[mob->mobX][mob->mobY + 1] == ' ' || st->map[mob->mobX][mob->mobY + 1] == '.') && nova_distancia(mob->mobX, mob->mobY + 1, st) > distancia_ideal(mob, st)) {
      mob->mobY++;
      break;
    } else { // direita
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 2;
      repeticoes++;
    }

    if(posicao == 3 && (st->map[mob->mobX + 1][mob->mobY + 1] == ' ' || st->map[mob->mobX + 1][mob->mobY + 1] == '.') && nova_distancia(mob->mobX + 1, mob->mobY + 1, st) > distancia_ideal(mob, st)) {
      mob->mobX++;
      mob->mobY++;
      break;
    } else { // baixo direita
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 3;
      repeticoes++;
    }

    if(posicao == 4 && (st->map[mob->mobX + 1][mob->mobY] == ' ' || st->map[mob->mobX + 1][mob->mobY] == '.') && nova_distancia(mob->mobX + 1, mob->mobY, st) > distancia_ideal(mob, st)) {
      mob->mobX++;
      break;
    } else { // baixo
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 4;
      repeticoes++;
    }

    if(posicao == 5 && (st->map[mob->mobX + 1][mob->mobY - 1] == ' ' || st->map[mob->mobX + 1][mob->mobY - 1] == '.') && nova_distancia(mob->mobX + 1, mob->mobY - 1, st) > distancia_ideal(mob, st)) {
      mob->mobX++;
      mob->mobY--;
      break;
    } else { // baixo esquerda
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 5;
      repeticoes++;
    }

    if(posicao == 6 && (st->map[mob->mobX][mob->mobY - 1] == ' ' || st->map[mob->mobX][mob->mobY - 1] == '.') && nova_distancia(mob->mobX, mob->mobY - 1, st) > distancia_ideal(mob, st)) {
      mob->mobY--;
      break;
    } else { // esquerda
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 6;
      repeticoes++;
    }

    if(posicao == 7 && (st->map[mob->mobX - 1][mob->mobY - 1] == ' ' || st->map[mob->mobX - 1][mob->mobY - 1] == '.') && nova_distancia(mob->mobX - 1, mob->mobY - 1, st) > distancia_ideal(mob, st)) {
      mob->mobX--;
      mob->mobY--;
      break;
    } else { // cima esquerda
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 7;
      repeticoes++;
    }

    if(posicao == 0 && (st->map[mob->mobX - 1][mob->mobY] == ' ' || st->map[mob->mobX - 1][mob->mobY] == '.') && nova_distancia(mob->mobX - 1, mob->mobY, st) > distancia_ideal(mob, st)) {
      mob->mobX--;
      break;
    } else { // cima
      while(esta_na_lista(posicoes, posicao, repeticoes)) posicao = rand() % 8;

      posicoes[repeticoes] = 0;
      repeticoes++;
    }
  }
}

// Consoante a distância do mob ao jogador, determina se o mob tem movimento/se
// está acordado.
void mobs_are_awake(MOB *mobs, STATE *st) {

  for(int i = 0; mobs[i]->indice; i++) {
    switch (st->dif) {
    case 1:
      if(distancia_ideal(mobs[i], st) <= 15 && mobs[i]->vida > 0) mobs[i]->awake = 1;
        else mobs[i]->awake = 0;
      break;

    case 2:
      if(distancia_ideal(mobs[i], st) <= 20 && mobs[i]->vida > 0) mobs[i]->awake = 1;
      break;

    case 3:
      if(distancia_ideal(mobs[i], st) <= 25 && mobs[i]->vida > 0) mobs[i]->awake = 1;
      break;
    }
  }
}

// Função para despertar os mobs, utilizadas pelos mobs espertos
void mob_awakes_mob(MOB mob, MOB *mobs, STATE *st) {
  for(int i = 0; mob->awake && mobs[i]->indice; i++) {
    switch (st->dif) {
    case 1:
      if(distancia_mobeal(mobs[i], mob) <= 5 && mobs[i]->vida > 0) mobs[i]->awake = 1;
      break;

    case 2:
      if(distancia_mobeal(mobs[i], mob) <= 9 && mobs[i]->vida > 0) mobs[i]->awake = 1;
      break;

    case 3:
      if(distancia_mobeal(mobs[i], mob) <= 15 && mobs[i]->vida > 0) mobs[i]->awake = 1;
      break;
    }
  }
}

// Verifica a vida do mob para saber se foi derrotado
void mob_morreu(MOB mob, STATE *st, AUDIO *audios) {
  init_color(CHAO,147 * 4, 157 * 4, 72 * 4);
  init_pair(COLOR_CHAO,CHAO,CHAO);
  int buff = 0;
  if(st->race == 5) buff = 2; // Elecsiuans
  int regen_rate = 5;
  for(int i = st->elecsium; i > 9; i -= 10) regen_rate++;


  int elec_regen = buff + regen_rate;
  if(mob->vida <= 0) {

    if(mob->qual_mob == 3){
      st->sound = 9;
      effects(st,&mob,audios);
    }

    mob->awake = 0;
    
    //st->map[mob->mobX][mob->mobY] = (int)'.';
    //mvaddch(mob->mobX,mob->mobY,'.' | COLOR_PAIR(COLOR_CHAO));

    //cleanMobs(st,mob);
    
    if(st->playerHP + elec_regen < 49) st->playerHP += elec_regen;
                                     else st->playerHP = 49;
    if(st->playerMP + elec_regen < MAXMP) st->playerMP += elec_regen;
                                     else st->playerMP = MAXMP;
  }
}

// Função de combate, referente ao dano que é deferido ao mob
void mob_levou_dano(MOB mob, STATE *st, AUDIO *audios) {
  
  int dificuldade = 4;
  if(st->dif == 2)
    dificuldade = 3;
  else if(st->dif == 3)
    dificuldade = 2;

  if(st->race == 4)
    dificuldade++; // thundercallers

  int dano_Player = dificuldade * (st->elecsium + 5);

  if(st->arma == 1) {
    if(distancia_ideal(mob, st) <= 2) {
      mob->vida -= dano_Player;
      mob_morreu(mob, st, audios);
    }
  }
  if(st->arma == 2) {
    if(st->race == 1 && distancia_ideal(mob, st) <= 5 + 2) { // Joltspurs
      mob->vida -= dano_Player + distancia_ideal(mob, st);
      mob_morreu(mob, st, audios);
    } else {
      if(distancia_ideal(mob, st) <= 5) {
        mob->vida -= dano_Player + distancia_ideal(mob, st);
        mob_morreu(mob, st, audios);
      }
    }
  }
}

// Função de combatte, referente ao dano que o jogador tomou
void mob_deu_dano(MOB mob, STATE *st) {
  int dodge = rand() % 10;

  int dificuldade = 2;
  if(st->dif == 2) dificuldade = 3;
  else if(st->dif == 3) dificuldade = 4;

  if(st->race == 3) dificuldade--; // ironforged

  int dano_Mobs = 1;//dificuldade * st->floor - st->elecsium;

  if((dodge == 1 && st->race == 2)) dano_Mobs = 0; // sparkrunners

  if(mob->vida > 0) {
    switch (mob->qual_mob) {
    case 0: // shock beetles
      if(distancia_ideal(mob, st) <= 2 && pode_snipar(mob, st) && dodge != 2) {
        st->playerHP -= dano_Mobs + 1;
      }
      break;

    case 1: // Circuit Crawlers
      if(distancia_ideal(mob, st) <= 2 && pode_snipar(mob, st) && dodge != 2) {
        st->playerHP -= dano_Mobs - 1;
      }
      break;

    case 2: // Plasma Bats long range
      if(distancia_ideal(mob, st) == 4 && pode_snipar(mob, st) && dodge != 3 &&
          dodge != 2) {
        st->playerHP -= dano_Mobs + 5;
      }
      if(distancia_ideal(mob, st) < 4 && pode_snipar(mob, st) && dodge != 2) {
        st->playerHP -= dano_Mobs + 5;
      }
      break;

    case 3: // mini boss
      if(distancia_ideal(mob, st) <= 3 && pode_snipar(mob, st)) {
        st->playerHP -= dano_Mobs + dano_Mobs;
      }
      break;
    }
  }
}

// Algoritmo para o movimento do mob
void movimento_mob(MOB *mobs, STATE *st, AUDIO *audios) {
  init_color(CHAO,147 * 4, 157 * 4, 72 * 4);
  init_pair(COLOR_CHAO,CHAO,CHAO);
  mobs_are_awake(mobs,st);

  int dano_singular = 1; // Variável para verificar se já disparamos a arma mais poderosa

  int dificuldade = 5;
  if(st->dif == 2) dificuldade = 3;
  if(st->dif == 3) dificuldade = 1;

  for(int i = 0; mobs[i]->indice; i++){
    if(mobs[i]->awake && mobs[i]->vida > 0){
      int mob_mais_perto = 0;
      if(nearest_comrade(mobs[i], mobs, st) && mobs[nearest_comrade(mobs[i], mobs, st) - 1]->qual_mob == 2) {
        dificuldade += 2;
        mob_mais_perto = nearest_comrade(mobs[i], mobs, st);
      }

      switch (mobs[i]->qual_mob) {
      case 0: // shock beetles/ afraid
        if(distancia_ideal(mobs[i], st) > 2 && mob_mais_perto && ((distancia_ideal(mobs[mob_mais_perto - 1], st) <= dificuldade) 
        || distancia_ideal(mobs[mob_mais_perto - 1], st) <= distancia_ideal(mobs[i], st))) {
          st->map[mobs[i]->mobX][mobs[i]->mobY] = ' ';
          mvaddch(mobs[i]->mobX,mobs[i]->mobY,'s' | COLOR_PAIR(MOBS));
          aproxima_do_player(mobs[i], st);
          st->map[mobs[i]->mobX][mobs[i]->mobY] = 's';
          if(st->arma == 2 && dano_singular){ 
            mob_levou_dano(mobs[nearest_mob(mobs, st) - 1], st, audios);
            dano_singular = 0;
          } else mob_levou_dano(mobs[i], st, audios);

        } else {
          if(distancia_ideal(mobs[i], st) > 2) {
            st->map[mobs[i]->mobX][mobs[i]->mobY] = ' ';
            mvaddch(mobs[i]->mobX,mobs[i]->mobY,'s' | COLOR_PAIR(MOBS));
            foge_do_player(mobs[i], st);
            st->map[mobs[i]->mobX][mobs[i]->mobY] = 's';
          if(st->arma == 2 && dano_singular){ 
            mob_levou_dano(mobs[nearest_mob(mobs, st) - 1], st, audios);
            dano_singular = 0;
          } else mob_levou_dano(mobs[i], st, audios);
 
            mob_awakes_mob(mobs[i], mobs, st);
 
          } else {
            if(st->arma == 2 && dano_singular) {
              mob_levou_dano(mobs[nearest_mob(mobs, st) - 1], st, audios);
              mob_deu_dano(mobs[i], st);
              dano_singular = 0;
            } else {
              mob_levou_dano(mobs[i], st, audios);
              mob_deu_dano(mobs[i], st);
            }
          }
        }
        break;

      case 1: // Circuit Crawlers/ burro
        if(distancia_ideal(mobs[i], st) > 2) {
          st->map[mobs[i]->mobX][mobs[i]->mobY] = ' ';
          mvaddch(mobs[i]->mobX,mobs[i]->mobY,'c' | COLOR_PAIR(MOBS));
          aproxima_do_player(mobs[i], st);
          st->map[mobs[i]->mobX][mobs[i]->mobY] = 'c';
          if(st->arma == 2 && dano_singular){ 
            mob_levou_dano(mobs[nearest_mob(mobs, st) - 1], st, audios);
            dano_singular = 0;
          } else mob_levou_dano(mobs[i], st, audios);

          } else {
            if(st->arma == 2 && dano_singular) {
              mob_levou_dano(mobs[nearest_mob(mobs, st) - 1], st, audios);
              mob_deu_dano(mobs[i], st);
              dano_singular = 0;
            } else {
              mob_levou_dano(mobs[i], st, audios);
              mob_deu_dano(mobs[i], st);
            }
          }
        break;

      case 2: // Plasma Bats long range / esperto
        if(distancia_ideal(mobs[i], st) > 4 && mob_mais_perto && (distancia_ideal(mobs[mob_mais_perto - 1], st) <= dificuldade 
        || distancia_ideal(mobs[mob_mais_perto - 1], st) <= distancia_ideal(mobs[i], st))) {
          st->map[mobs[i]->mobX][mobs[i]->mobY] = ' ';
          mvaddch(mobs[i]->mobX,mobs[i]->mobY,'p' | COLOR_PAIR(MOBS));
          aproxima_do_player(mobs[i], st);
          st->map[mobs[i]->mobX][mobs[i]->mobY] = 'p';
          if(st->arma == 2 && dano_singular){ 
            mob_levou_dano(mobs[nearest_mob(mobs, st) - 1], st, audios);
            dano_singular = 0;
          } else mob_levou_dano(mobs[i], st, audios);
        } else {
          if(distancia_ideal(mobs[i], st) <= 4 && mob_mais_perto && (distancia_ideal(mobs[mob_mais_perto], st) <= dificuldade
          || distancia_ideal(mobs[mob_mais_perto - 1], st) <= distancia_ideal(mobs[i], st))) {
            if(st->arma == 2 && dano_singular) {
              mob_levou_dano(mobs[nearest_mob(mobs, st) - 1], st, audios);
              mob_deu_dano(mobs[i], st);
              dano_singular = 0;
            } else {
              mob_levou_dano(mobs[i], st, audios);
              mob_deu_dano(mobs[i], st);
            }
            mob_deu_dano(mobs[i], st);
          } else {
            st->map[mobs[i]->mobX][mobs[i]->mobY] = ' ';
            mvaddch(mobs[i]->mobX,mobs[i]->mobY,'p' | COLOR_PAIR(MOBS));
            foge_do_player(mobs[i], st);
            st->map[mobs[i]->mobX][mobs[i]->mobY] = 'p';
          if(st->arma == 2 && dano_singular){ 
            mob_levou_dano(mobs[nearest_mob(mobs, st) - 1], st, audios);
            dano_singular = 0;
          } else mob_levou_dano(mobs[i], st, audios);
            mob_awakes_mob(mobs[i], mobs, st);
          }
        }
        break;

      case 3: // mini boss
        if(distancia_ideal(mobs[i], st) > 3) {
          st->map[mobs[i]->mobX][mobs[i]->mobY] = ' ';
          mvaddch(mobs[i]->mobX,mobs[i]->mobY,'G' | COLOR_PAIR(BOSS));
          aproxima_do_player(mobs[i], st);
          if(st->dif == 2) aproxima_do_player(mobs[i], st);
          st->map[mobs[i]->mobX][mobs[i]->mobY] = 'G';
          mob_levou_dano(mobs[i], st, audios);

        } else {
          mob_levou_dano(mobs[i], st, audios);
          mob_deu_dano(mobs[i], st);
        }

        break;
      }
    }
  }
}