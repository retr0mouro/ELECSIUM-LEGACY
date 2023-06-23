#include "luz.h"

// Algumas funções auxiliares usadas na luz

void verificaLuz(STATE *st){ // percorre o mapa todo e verifica se não tem luz que passou pelas paredes, começa da esquerda para a direita e de cima para baixo
  init_color(CHAO,147 * 4, 157 * 4, 72 * 4);
  init_pair(COLOR_CHAO,CHAO,CHAO);
  for(int i = 0; i<54; i++){
      int flag = 0;
    for(int j = 0; j<211; j++){
      for(int raioX = 0; raioX<=2 ; raioX++){
        for(int raioY = 0; raioY<=2; raioY++){
          if(st->map[i][j] == '.' && st->map[i+raioX][j+raioY] == '.' && (raioX != 0 && raioY!= 0)){
            flag ++;
          }
        }
      }
      if(flag < 8 && st->map[i][j] == ' '){
        st->map[i][j] = (int) ' ';
        mvaddch(i,j,' ' | COLOR_PAIR(COLOR_CHAO));
      }
    }
  }
}

void verificaLuz2(STATE *st){ // percorre o mapa todo e verifica se não tem luz que passou pelas paredes, começa da direita para a esquerda e de cima para baixo
  init_color(CHAO,147 * 4, 157 * 4, 72 * 4);
  init_pair(COLOR_CHAO,CHAO,CHAO);
  for(int i = 0; i < 54; i++){
      int flag = 0;
    for(int j = 211 ;j > 0; j--){
      for(int raioX = 0; raioX<=2 ; raioX++){
        for(int raioY = 0; raioY<=2; raioY++){
          if(st->map[i][j] == '.' && st->map[i+raioX][j+raioY] == '.' && (raioX != 0 && raioY != 0)){
            flag ++;
          }
        }
      }
      if(flag < 3 && st->map[i][j] == ' '){
        st->map[i][j] = (int) ' ';
        mvaddch(i,j,' ' | COLOR_PAIR(COLOR_CHAO));
      }
    }
  }
}


void limpaLuz(STATE *st){  // limpa a luz a cada movimento do jogador (só é implementada no movimentos)
  for(int l = 0;l < 53;l++){
    for(int c = 0;c < 210;c++){
      if(st->map[l][c] == '.'){
        st->map[l][c] = ' ';
        mvaddch(l,c,' '|COLOR_PAIR(COLOR_CHAO));
      }
    }
  }
}

/* JA NAO E USADA
void redrawLuz(STATE *st){ 
  for(int l = 0;l < 53;l++){
    for(int c = 0;c < 210;c++){
      if(st->map[l][c] == '.'){
        st->map[l][c] = '.';
        mvaddch(l,c,'.'); //se colocar cor pode tornar o jogo lento / tem delay
      }
    }
  }
}
*/

int objetivo(STATE *st, int x, int y){  // vé se tem objetivo/elsiu/mobs
  int flag = 0;
  if(st->map[x][y] == (int) 'V' || st->map[x][y] == (int) '^' || st->map[x][y] == (int) 'c' || st->map[x][y] == (int) 'p' || st->map[x][y] == (int) 's' || st->map[x][y] == (int) 'G' ){
    flag = 1;
  }
  return flag;
}


int verificaCima(STATE *st, int x, int y){ // caso tenha parede em baixo do player devolve 1 
  int flag = 0;
  if(st->playerY > y && (st->map[x+1][y] == '#' && st->map[x][y+1] == '#')) flag = 1;
  if(st->playerY < y && (st->map[x+1][y] == '#' && st->map[x][y-1] == '#')) flag = 1;
  return flag;
}

int verificaBaixo(STATE *st, int x, int y){ // caso tenha parede em cima do player devolve 1
  int flag = 0;
  if(st->playerY > y && (st->map[x-1][y] == '#' && st->map[x][y+1] == '#')) flag = 1;
  if(st->playerY < y && (st->map[x-1][y] == '#' && st->map[x][y-1] == '#')) flag = 1;
  return flag;
}

int paredeEntrePontosCima(STATE *st, int x, int y, int xant, int yant, int i3){ // vê a distancia entre dois pontos e verifica se existe parede entre eles
  int distx = abs(x - xant);                                                   
  int disty = abs(y - yant);
  int flag = 0;
  if(sqrt(distx*distx + disty*disty) > 3 || distx > 3 || disty > 3){
  for(int i = 1; i < disty;i++){
    if(flag == 1){
      break;
    }
    for(int j = 0; j < distx;j++){
      if(y<st->playerY && st->map[st->playerX - i3 - j][y + i] == (int) '#'){
        flag = 1;
        break;
      }
      if(y>st->playerY && st->map[st->playerX - i3 - j][y - i] == (int) '#'){
        flag = 1;
        break;
      }
    }
  }
}
return flag;
}

int paredeEntrePontosBaixo(STATE *st, int x, int y, int xant, int yant, int i3){ // o mesmo q a função de cima mas utilizada na luz de baixo
  int distx = abs(x - xant);
  int disty = abs(y - yant);
  int flag = 0;
  if( sqrt(distx*distx + disty*disty) > 3 || distx > 3 || disty > 3){
  for(int i = 1; i < disty;i++){
    if(flag == 1){
      break;
    }
    for(int j = 0; j < distx;j++){
      if(y<st->playerY && st->map[st->playerX + i3 - j][y + i] == (int) '#'){
        flag = 1;
        break;
      }
      if(y>st->playerY && st->map[st->playerX + i3 - j][y - i] == (int) '#'){
        flag = 1;
        break;
      }
    }
  }
}
return flag;
}

float declive(STATE *st, int x, int y) {  // vê o declive entre o jogador e a borda do mapa (x,y) o x e o y vão se movendo ao longo das bordas do mapa
  if (x - st->playerX == 0)
    return 40000; // n é possível dividir por 0
  return (float) ((y - st->playerY) * 1.0 / (x - st->playerX));
}

int equationX(STATE *st, int xb, int yb, int y) { // calcula a coordenada x utilizando a equação da reta
  int xn = 0;                                     // xb : x da borda , yb : y da borda
  float m = declive(st, xb, yb), b = 0;         
  b = st->playerY - (m * st->playerX);
  if (m != 0) {
    xn = round((y - b) / m); 
  }
  return xn;
}

int equationY(STATE *st, int xb, int yb, int x) { // calcula a coordenada y utilizando a equação da reta 
  int yn = 0;
  float m = declive(st, xb, yb), b = 0;
  b = st->playerY - (m * st->playerX);
  yn = round((m * x) + b);
  return yn;
}




//VISÃO MODO FACIL

void direita(STATE *st) { // ilumina para a direita
  for (int i = 54; i > -1; i--) {
      if (declive(st, i, 210) == 40000) {
        for (int j = 1; st->playerY + j != 211; j++) {
          if(objetivo(st, st->playerX, (st->playerY + j))){
            continue;
          }
            if(st->map[st->playerX][st->playerY + j] != (int) '#' && st->map[st->playerX][st->playerY + j] != (int) 'V'){
                st->map[st->playerX][st->playerY + j] = (int) '.';
                 mvaddch(st->playerX,st->playerY + j,'.');
                 }
            else break;
        }
      } else {
        for (int j = 1; st->playerY + j < 210; j++) {
          int x = 0;
          x = equationX(st,i,210,st->playerY + j);
          if(objetivo(st, x, (st->playerY + j))){
            continue;
          }
          if(st->map[x][st->playerY + j] != (int) '#'){
            st->map[x][st->playerY + j] = (int) '.';
             mvaddch(x,st->playerY + j,'.');
             }
          else break;
        }
      }
    }
}

void esquerda(STATE *st){ // ilumina para a esquerda
        for (int i4 = 0; i4 < 54; i4++) {
              if (declive(st, i4, 0) == 40000) {
                for (int j2 = 1; st->playerY - j2 != 0; j2++) {
                  if(objetivo(st, st->playerX, (st->playerY -j2))){
            continue;
          }
                    if(st->map[st->playerX][st->playerY - j2] != (int) '#'){
                        st->map[st->playerX][st->playerY - j2] = (int) '.';
                         mvaddch(st->playerX,st->playerY - j2,'.');}
                    else break;
                }
              } else {
              for (int j3 = 1; st->playerY - j3 > -1; j3++) {
                  int b = 0;
                  b = equationX(st,i4,0,st->playerY - j3); 
                  if(objetivo(st, b, (st->playerY - j3))){
                  continue;
                  }
                  if(st->map[b][st->playerY - j3] != (int) '#'){
                    st->map[b][st->playerY - j3] = (int) '.';
                     mvaddch(b,st->playerY - j3,'.');}
                  else break;
              }
    }
  } 
}

void cima(STATE *st){ // ilumina para cima
  for (int z = 211; z > -1; z--) { // z : Y do mapa
    if(st->map[st->playerX-1][st->playerY] == '#') break;
          if (declive(st, 0, z) == 0) {
            for (int i2 = 1; st->playerX - i2 > -1; i2++) { // i2 : X do mapa | caso do declive ser infinito
              if(objetivo(st, (st->playerX - i2), st->playerY)){
            continue;
          }
                if(st->map[st->playerX - i2][st->playerY] != (int) '#'){
                    st->map[st->playerX - i2][st->playerY] = (int) '.';
                    mvaddch(st->playerX - i2,st->playerY,'.');
                    }
                else break;
            }
          } else {
            for (int i3 = 1; st->playerX - i3 > -1; i3++) { // i3 : X do mapa 
              int a = 0;
              a = equationY(st,0,z,st->playerX - i3);
              int aux = equationY(st,0,z,st->playerX-i3+1);
              if(objetivo(st, (st->playerX - i3), a)){
              continue;
              }
              if (verificaCima(st, st->playerX-i3, a)) break;
              if (paredeEntrePontosCima(st, st->playerX-i3, a, st->playerX-i3+1, aux,i3) == 1){
                break;
              }
              if(st->map[st->playerX - i3][a] != (int) '#'){
                    st->map[st->playerX - i3][a] = (int) '.';
                    mvaddch(st->playerX - i3,a,'.');
            } else break;
      }
    }
  }
}

void baixo(STATE *st){ // ilumina para baixo
  for (int z = 1; z < 211; z++) { // z : Y do mapa
    if(st->map[st->playerX+1][st->playerY] == '#') break;
          if (declive(st, 53, z) == 0) {
            for (int i2 = 1; st->playerX + i2 < 53; i2++) { // i2 : X do mapa | caso do declive ser infinito
              if(objetivo(st, (st->playerX + i2), st->playerY)){
            continue;
          }
                if(st->map[st->playerX + i2][st->playerY] != (int) '#'){
                    st->map[st->playerX + i2][st->playerY] = (int) '.';
                    mvaddch(st->playerX + i2,st->playerY,'.');
                    }
                else break;
            }
          } else {
            for (int i3 = 1; st->playerX + i3 < 53; i3++) { // i3 : X do mapa
              int a = 0;
              a = equationY(st,53,z,st->playerX + i3);
              int aux = equationY(st,53,z,st->playerX + i3 -1);
              if(objetivo(st, (st->playerX + i3), a)){
              continue;
              }
              if (verificaBaixo(st, st->playerX+i3, a)) break;
              if (i3 == 1 && paredeEntrePontosBaixo(st, st->playerX+i3, a, st->playerX, st->playerY,i3) == 1) break;
              if (paredeEntrePontosBaixo(st, st->playerX+i3, a, st->playerX+i3-1, aux,i3) == 1){
                break;
              }
              if(st->map[st->playerX + i3][a] != (int) '#'){
                    st->map[st->playerX + i3][a] = (int) '.';
                    mvaddch(st->playerX + i3,a,'.');
            } else break;
      }
    }
  } 
} 

void luznormal(STATE *st){ // junta todas as funções de iluminação
  direita(st);
  esquerda(st);
  baixo(st);
  cima(st);
  verificaLuz(st);
  verificaLuz2(st);
}



// VISAO DO TRYHARD

int distancia(STATE *st, int x, int y){ // função para calcular a distância entre um ponto e o jogador e devolve uma flag para parar a iluminação caso passe de um certo raio
  int distx = abs(x - st->playerX);
  int disty = abs(y - st->playerY);
  int flag = 0, raio = 0;
  if(st->dif == 3){
    raio = 8;
  }else raio = 16;
  if( (float) sqrt(distx*distx + disty*disty) >  (float) raio){
    flag = 1;
  }
  return flag;
}

void direitath(STATE *st) { // ilumina a direita 
  for (int i = 53; i > -1; i--) {
      if (declive(st, i, 210) == 40000) {
        for (int j = 1; st->playerY + j != 211; j++) {
          if(objetivo(st, st->playerX, (st->playerY + j))){
            continue;
          }
          if(distancia(st, st->playerX, (st->playerY +j))){
            break;
          }
            if(st->map[st->playerX][st->playerY + j] != (int) '#' && st->map[st->playerX][st->playerY + j] != (int) 'V'){
                st->map[st->playerX][st->playerY + j] = (int) '.';
                 mvaddch(st->playerX,st->playerY + j,'.');
                 }
            else break;
        }
      } else {
        for (int j = 1; st->playerY + j < 210; j++) {
          int x = 0;
          x = equationX(st,i,210,st->playerY + j);
          if(objetivo(st, x, (st->playerY + j))){
            continue;
          }
          if(distancia(st, x, (st->playerY +j))){
            break;
          }
          if(st->map[x][st->playerY + j] != (int) '#'){
            st->map[x][st->playerY + j] = (int) '.';
             mvaddch(x,st->playerY + j,'.');
             }
          else break;
        }
      }
    }
}

void esquerdath(STATE *st){ // ilumina a esquerda 
        for (int i4 = 0; i4 < 59; i4++) {
              if (declive(st, i4, 0) == 40000) {
                for (int j2 = 1; st->playerY - j2 != 0; j2++) {
                  if(objetivo(st, st->playerX, (st->playerY -j2))){
            continue;
          }
          if(distancia(st, st->playerX, (st->playerY - j2))){
            break;
          }
                    if(st->map[st->playerX][st->playerY - j2] != (int) '#'){
                        st->map[st->playerX][st->playerY - j2] = (int) '.';
                         mvaddch(st->playerX,st->playerY - j2,'.');}
                    else break;
                }
              } else {
              for (int j3 = 1; st->playerY - j3 > -1; j3++) {
                  int b = 0;
                  b = equationX(st,i4,0,st->playerY - j3); 
                  if(objetivo(st, b, (st->playerY - j3))){
                  continue;
                  }
                  if(distancia(st, b, (st->playerY -j3))){
            break;
          }
                  if(st->map[b][st->playerY - j3] != (int) '#'){
                    st->map[b][st->playerY - j3] = (int) '.';
                     mvaddch(b,st->playerY - j3,'.');}
                  else break;
              }
    }
  } 
}

void cimath(STATE *st){ // ilumina cima 
  for (int z = 211; z > -1; z--) {
    if(st->map[st->playerX-1][st->playerY] == '#') break;
          if (declive(st, 0, z) == 0) {
            for (int i2 = 1; st->playerX - i2 > -1; i2++) {
              if(objetivo(st, (st->playerX - i2), st->playerY)){
            continue;
          }
          if(distancia(st, (st->playerX - i2), st->playerY)){
            break;
          }
                if(st->map[st->playerX - i2][st->playerY] != (int) '#'){
                    st->map[st->playerX - i2][st->playerY] = (int) '.';
                    mvaddch(st->playerX - i2,st->playerY,'.');
                    }
                else break;
            }
          } else {
            for (int i3 = 1; st->playerX - i3 > -1; i3++) {
              int a = 0;
              a = equationY(st,0,z,st->playerX - i3);
              int aux = equationY(st,0,z,st->playerX-i3+1);
              if(objetivo(st, (st->playerX - i3), a)){
              continue;
              }
              if(distancia(st, (st->playerX - i3), a)){
            break;
          }
              if (paredeEntrePontosCima(st, st->playerX-i3, a, st->playerX-i3+1, aux,i3) == 1){
                break;
              }
              if(st->map[st->playerX - i3][a] != (int) '#'){
                    st->map[st->playerX - i3][a] = (int) '.';
                    mvaddch(st->playerX - i3,a,'.');
            } else break;
      }
    }
  }
}

void baixoth(STATE *st){ // ilumina baixo
  for (int z = 0; z < 211; z++) {
    if(st->map[st->playerX+1][st->playerY] == '#') break;
          if (declive(st, 53, z) == 0) {
            for (int i2 = 1; st->playerX + i2 < 53; i2++) {
              if(objetivo(st, (st->playerX + i2), st->playerY)){
            continue;
          }
          if(distancia(st, (st->playerX + i2), st->playerY)){
            break;
          }
                if(st->map[st->playerX + i2][st->playerY] != (int) '#'){
                    st->map[st->playerX + i2][st->playerY] = (int) '.';
                    mvaddch(st->playerX + i2,st->playerY,'.');
                    }
                else break;
            }
          } else {
            for (int i3 = 1; st->playerX + i3 < 53; i3++) {
              int a = 0;
              a = equationY(st,53,z,st->playerX + i3);
              int aux = equationY(st,53,z,st->playerX + i3 -1);
              if(objetivo(st, (st->playerX + i3), a)){
              continue;
              }
              if(distancia(st, (st->playerX + i3), a)){
            break;
          }
              if (paredeEntrePontosBaixo(st, st->playerX+i3, a, st->playerX+i3-1, aux,i3) == 1){
                break;
              }
              if(st->map[st->playerX + i3][a] != (int) '#'){
                    st->map[st->playerX + i3][a] = (int) '.';
                    mvaddch(st->playerX + i3,a,'.');
            } else break;
      }
    }
  } 
} 

void luzth(STATE *st){ // junta todas as funções para iluminar os outros modos
  direitath(st);
  esquerdath(st);
  baixoth(st);
  cimath(st);
}

void pintaLuz(STATE *st){
  init_color(CHAO,147 * 3, 157 * 3, 72 * 3);
  init_pair(COLOR_PONTO, COLOR_BLACK, CHAO);
  for(int i = 0; i < 54; i++){
    for(int j = 0; j < 211; j++){
      if(st->map[i][j] == (int) '.'){
        mvaddch(i,j, '.' | COLOR_PAIR(COLOR_PONTO));
      }
    }
  }
}

void luz(STATE *st){ // junta a iluminação dos vários modos
  if(st->dif < 2){
    luznormal(st);
  }else luzth(st);
  pintaLuz(st);
}