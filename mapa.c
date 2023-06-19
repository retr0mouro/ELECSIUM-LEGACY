#include "luz.h"



int contaVizinhos1(STATE *st,int x,int y){
    int vizinhos = 0;
    for(int i = -1;i < 2;i++){
        for(int j = -1;j < 2;j++){
            if(st->map[x+i][y+j] == (int) '#') vizinhos++;
            else continue;
        }
    }
    return vizinhos;
}

int contaVizinhos2(STATE *st,int x,int y){
    int vizinhos = 0;
    for(int i = -2;i < 3;i++){
        for(int j = -2;j < 3;j++){
            if(st->map[x+i][y+j] == (int) '#') vizinhos++;
            else continue;
        }
    }
    return vizinhos;
}


void geraParedes1(STATE *st){
    for(int i = 2;i < 53;i++){
        for(int j = 2;j < 209;j++){
            if(contaVizinhos1(st,i,j) >= 5 || contaVizinhos2(st,i,j) <= 2) st->map[i][j] = (int) '#';
            else st->map[i][j] = (int) ' ';
        }
    }
}


void geraParedes2(STATE *st){
    for(int i = 2;i < 53;i++){
        for(int j = 2;j < 209;j++){
            if(contaVizinhos1(st,i,j) >= 5) st->map[i][j] = (int) '#';
            else st->map[i][j] = (int) ' ';
        }
    }
}





void drawMap(STATE *st,int nrows,int ncols){
    init_color(CHAO,147 * 3, 157 * 3, 72 * 3);
    init_color(PAREDE,100 * 4, 64 * 4, 0 * 4);
    init_pair(COLOR_CHAO,CHAO,CHAO);
    init_pair(COLOR_PAREDE,PAREDE,PAREDE);
    clear();
    for(int p = 0;p < (nrows - 6);p++){
        for(int u = 0;u < ncols;u++){
            st->map[p][u] = (int) ' ';
        }
    }
    float percentagem = 0.0;
    if(st->dif == 1) percentagem = 0.5;
    if(st->dif == 2) percentagem = 0.54;
    if(st->dif == 3) percentagem = 0.6;
    int max = percentagem * ((nrows - 5) * ncols), count = 0;//,total = 58 * 210;


    //linhas e colunas limites do mapa ****************************
    for(int y = 0;y < (nrows - 5);y++){
        st->map[y][0] = (int) '#';
        move(y,0);
        addch((int) '#');
        st->map[y][ncols - 1] = (int) '#';
        move(y,ncols - 1);
        addch((int) '#' | COLOR_PAIR(COLOR_PAREDE));
        count += 2;
    }
    for(int yy = 0;yy < ncols;yy++){
        st->map[0][yy] = (int) '#';
        move(0,yy);
        addch((int) '#');
        st->map[nrows - 6][yy] = (int) '#';
        move(nrows - 6,yy);
        addch((int) '#' | COLOR_PAIR(COLOR_PAREDE));
        count += 2;
    }
    //************************************************************


    int i = 0;
    for(;i < max;i++){
        int row = rand() % ((nrows - 5) - 2) + 1;
        int col = rand() % (ncols - 2) + 1;
        st->map[row][col] = (int) '#';
        //mvaddch(row,col,'#');
    }
    for(i = 0;i < (nrows - 6);i++){
        for(int ii = 0;ii < ncols;ii++){
            if(st->map[i][ii] != (int) '#'){
                st->map[i][ii] = (int) ' ';
                //mvaddch(i,ii,(int) ' ');
            }else continue;
        }
    }
   
    geraParedes1(st);
    geraParedes1(st);
    geraParedes1(st);
    geraParedes2(st);
    geraParedes2(st);
    geraParedes2(st);
    //gera_elecsium(st);
    init_pair(ELSIU,COLOR_BLACK,COLOR_CYAN);
    for(int b = 0;b < 53;b++){//(nrows - 6);b++){
        for(int k = 0;k < 210;k++){//(ncols - 1);k++){
            if(st->map[b][k] == (int) '#') mvaddch(b,k,(int) '#' | COLOR_PAIR(COLOR_PAREDE));
            if(st->map[b][k] == (int) ' ') mvaddch(b,k,(int) ' ' | COLOR_PAIR(COLOR_CHAO));
            if(st->map[b][k] == (int) '^') mvaddch(b,k,(int) '^' | COLOR_PAIR(ELSIU));
        }
    }
    //luz(st);
    //drawHealth(st);
    //drawMana(st);
    refresh();
}

void drawElec(STATE *st){
    init_pair(ELSIU,COLOR_BLACK,COLOR_CYAN);
    for(int i = 0; i < 54;i++){
        for(int j = 0;j < 211;j++){
            if(st->map[i][j] == (int) '^') mvaddch(i,j,'^' | COLOR_PAIR(ELSIU));
        }
    }
}

void drawMobs(STATE *st,MOB *mobs){
    init_pair(MOBS,COLOR_RED,CHAO);
    init_pair(BOSS,COLOR_CYAN,COLOR_RED);
    for(int i = 0;i < st->mobs_TOTAIS; i++){
        if(mobs[i]->vida != 0){
            switch (mobs[i]->qual_mob){
                case 0:
                    st->map[mobs[i]->mobX][mobs[i]->mobY] = 's';
                    mvaddch(mobs[i]->mobX,mobs[i]->mobY, 's' | COLOR_PAIR(MOBS));
                    break;
                case 1:
                    st->map[mobs[i]->mobX][mobs[i]->mobY] = 'c';
                    mvaddch(mobs[i]->mobX,mobs[i]->mobY, 'c' | COLOR_PAIR(MOBS));
                    break;
                case 2:
                    st->map[mobs[i]->mobX][mobs[i]->mobY] = 'p';
                    mvaddch(mobs[i]->mobX,mobs[i]->mobY, 'p' | COLOR_PAIR(MOBS));
                    break;
                case 3:
                    st->map[mobs[i]->mobX][mobs[i]->mobY] = 'G';
                    mvaddch(mobs[i]->mobX,mobs[i]->mobY, 'G' | COLOR_PAIR(BOSS));
                    break;
            }
        }
        else{
            st->map[mobs[i]->mobX][mobs[i]->mobY] = ' ';
            mvaddch(mobs[i]->mobX,mobs[i]->mobY,' ' | COLOR_PAIR(COLOR_CHAO));
        }
    }
}

void redrawMap(STATE *st){
    init_color(CHAO,147 * 4, 157 * 4, 72 * 4);
    init_color(PAREDE,100 * 4, 64 * 4, 0 * 4);
    init_pair(COLOR_CHAO,CHAO,CHAO);
    init_pair(COLOR_PAREDE,PAREDE,PAREDE);
    init_pair(MOBS,COLOR_RED,CHAO);
    init_pair(BOSS,COLOR_CYAN,COLOR_RED);
    for(int i = 0;i < 54;i++){
        for(int j = 0;j < 211;j++){
            switch(st->map[i][j]){
            case '#':
                mvaddch(i,j,st->map[i][j] | COLOR_PAIR(COLOR_PAREDE));
                break;
            case ' ':
                mvaddch(i,j,st->map[i][j] | COLOR_PAIR(COLOR_CHAO));
                break;
            case 'c':
                mvaddch(i,j,'c' | COLOR_PAIR(MOBS));
                break;
            case 'p':
                mvaddch(i,j,'p' | COLOR_PAIR(MOBS));
                break;
            case 's':
                mvaddch(i,j,'s' | COLOR_PAIR(MOBS));
                break;
            case 'G':
                mvaddch(i,j,'G' | COLOR_PAIR(BOSS));
                break;
            }
        }
    }
    //drawElec(st);
    //drawMobs(st,mobs);
}