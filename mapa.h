#include "menus.h"
#include <math.h>

/*void algorithm(STATE *st){
    for(int i = 1;i < 55;i+=3){
        for(int j = 1;j < 210;j++){
            st->map[i+1][j] = st->map[i][j];
            st->map[i+2][j] = st->map[i][j];
            st->map[i+3][j] = st->map[i][j];
            st->map[i+4][j] = st->map[i][j];
            mvaddch(i+1,j,st->map[i][j]);
            mvaddch(i+2,j,st->map[i][j]);
            mvaddch(i+3,j,st->map[i][j]);
            mvaddch(i+4,j,st->map[i][j]);
        }
    }
}*/





int contaVizinhos1(STATE *st,int x,int y){
    int vizinhos = 0;
    for(int i = -1;i < 2;i++){
        for(int j = -1;j < 2;j++){
            if(st->map[x+i][y+j] == (int) '#') vizinhos++;
            else continue;
        }
    }
    //if(st->map[x][y] == (int) '#') vizinhos++;
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
    //if(st->map[x][y] == (int) '#') vizinhos++;
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





void drawMap(STATE *st){
    clear();
    for(int p = 0;p < 53;p++){
        for(int u = 0;u < 211;u++){
            st->map[p][u] = (int) ' ';
        }
    }
    float percentagem = 0.0;
    if(st->dif == 1) percentagem = 0.5;
    if(st->dif == 2) percentagem = 0.55;
    if(st->dif == 3) percentagem = 0.6;
    int max = percentagem * (54 * 210), count = 0;//,total = 58 * 210;


    //linhas e colunas limites do mapa ****************************
    for(int y = 0;y < 54;y++){
        st->map[y][0] = (int) '#';
        move(y,0);
        addch((int) '#');
        st->map[y][210] = (int) '#';
        move(y,210);
        addch((int) '#');
        count += 2;
    }
    for(int yy = 0;yy < 211;yy++){
        st->map[0][yy] = (int) '#';
        move(0,yy);
        addch((int) '#');
        st->map[53][yy] = (int) '#';
        move(53,yy);
        addch((int) '#');
        count += 2;
    }
    //************************************************************


    int i = 0;
    for(;i < max;i++){
        int row = rand() % (54 - 2) + 1;
        int col = rand() % (211 - 2) + 1;
        st->map[row][col] = (int) '#';
        //mvaddch(row,col,'#');
    }
    for(i = 0;i < 53;i++){
        for(int ii = 0;ii < 211;ii++){
            if(st->map[i][ii] != (int) '#'){
                st->map[i][ii] = (int) ' ';
                //mvaddch(i,ii,(int) ' ');
            }else continue;
        }
    }
    //clear();
    //algorithm(st);
    /*int x = rand() % 57;
    int y = rand() % 209;
    while(1){
        if((x != 0 && x != 1) && (y != 0 && y != 1)){
            st->objetivoX = x;
            st->objetivoY = y;
            break;
        }else {
            if(x == 0 || x == 1){
                x = rand() % 57;
            }
            if(y == 0 || y == 1){
                y = rand() % 209;
                continue;
            }
            break;
        }
    }
    mvaddch(st->objetivoX,st->objetivoY,(int) 'V' | A_REVERSE);*/

    
    /*for(int i = 1;i < 58;i++){
        for(int j = 1;j < 210;j++){
            if(count != max){
                if(rand() % 2 == 1){
                    st->map[i][j] = (int) '#';
                    move(i,j);
                    addch((int) '#');
                    count++;
                }else{
                    st->map[i][j] = (int) '.';
                    move(i,j);
                    addch((int) '.');
                }
            }else{
                st->map[i][j] = (int) '.';
                move(i,j);
                addch((int) '.');
            }
        }
    }*/
    geraParedes1(st);
    geraParedes1(st);
    geraParedes1(st);
    geraParedes2(st);
    for(int b = 0;b < 53;b++){
        for(int k = 0;k < 210;k++){
            if(st->map[b][k] == (int) '#') mvaddch(b,k,(int) '#');
            if(st->map[b][k] == (int) ' ') mvaddch(b,k,(int) ' ');
        }
    }
    //drawHealth(st);
    //drawMana(st);
    refresh();
}

/*int quadrados(int r){
    int ans = 0;
    ans = pow(r+1,2) + pow(r,2);
    return ans; 
}*/