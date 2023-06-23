#include "music.h"
//#include "estado.h"
//#include "utils.h"

//----------------------------------------



//menu saÃ­da
void menuNoob(){

    clear();
    WINDOW * menu = newwin(40,160,8,16);
    //WINDOW * opt = newwin(15,50,35,75);
    //wrefresh(menu);
    refresh();


    mvwprintw(menu,6 ,6+2+11,"        ____            ______                ________________                    ________________                ________________        ");
    mvwprintw(menu,7 ,6+2+11,"        ____            ______                ________________                    ________________                ________________        ");
    mvwprintw(menu,8 ,6+2+11,"    ||||    \\\\\\\\    ||||    ||||        ////    ________    \\\\\\\\            ////    ________    \\\\\\\\        ||||        ____    \\\\\\\\    ");
    mvwprintw(menu,9 ,6+2+11,"    ||||    \\\\\\\\    ||||    ||||        ////    ________    \\\\\\\\            ////    ________    \\\\\\\\        ||||        ____    \\\\\\\\    ");
    mvwprintw(menu,10 ,6+2+11,"    ||||        \\\\\\\\||||    ||||    ||||    ||||        ||||    ||||    ||||    ||||        ||||    ||||    ||||    ||||____))))    ||||");
    mvwprintw(menu,11 ,6+2+11,"    ||||        \\\\\\\\||||    ||||    ||||    ||||        ||||    ||||    ||||    ||||        ||||    ||||    ||||    ||||____))))    ||||");
    mvwprintw(menu,12 ,6+2+11,"    ||||    ....    ````    ||||    ||||    ||||        ||||    ||||    ||||    ||||        ||||    ||||    ||||        ____    <<<<     ");
    mvwprintw(menu,13 ,6+2+11,"    ||||    ....    ````    ||||    ||||    ||||        ||||    ||||    ||||    ||||        ||||    ||||    ||||        ____    <<<<     ");
    mvwprintw(menu,14 ,6+2+11,"    ||||    ||||\\\\\\\\        ||||    ||||    ||||________||||    ||||    ||||    ||||________||||    ||||    ||||    ||||____))))    ||||");
    mvwprintw(menu,15 ,6+2+11,"    ||||    ||||\\\\\\\\        ||||    ||||    ||||________||||    ||||    ||||    ||||________||||    ||||    ||||    ||||____))))    ||||");
    mvwprintw(menu,16 ,6+2+11,"    ||||____||||    \\\\\\\\____||||        \\\\\\\\________________////            \\\\\\\\________________////        ||||________________////    ");
    mvwprintw(menu,17 ,6+2+11,"    ||||____||||    \\\\\\\\____||||        \\\\\\\\________________////            \\\\\\\\________________////        ||||________________////    ");
    mvwprintw(menu,18 ,6+2+11,"                                                                          ");

    wrefresh(menu);
}



//----------------------------------------

void background(STATE *st, AUDIO *audios){

    //continua a musica onde parou no jogo
    if (st->sound == -3){
    sfMusic_pause(audios->music);
    sfMusic_play(audios->jusic);
    }

    //continua a musica onde parou no menu
    else if (st->sound == -2){
    sfMusic_pause(audios->jusic);
    sfMusic_play(audios->music);
    }
    
    //musica background nos menus
    else if(st->sound == 0){
    audios->music = sfMusic_createFromFile("bmenus.wav");
    sfMusic_setVolume(audios->music, 20);

    sfMusic_setLoop(audios->music, sfTrue);
    sfMusic_play(audios->music);   
   }

    //musica background a jogar
    else if(st->sound == 1){
    sfMusic_pause(audios->music);

    audios->jusic = sfMusic_createFromFile("bplay1.wav");
    sfMusic_setVolume(audios->jusic, 10);

    sfMusic_setLoop(audios->jusic, sfTrue);
    sfMusic_play(audios->jusic);
   }

    //musica background a jogar
    else if(st->sound == 2){
    sfMusic_pause(audios->music);

    audios->jusic = sfMusic_createFromFile("bplay2.wav");
    sfMusic_setVolume(audios->jusic, 10);

    sfMusic_setLoop(audios->jusic, sfTrue);
    sfMusic_play(audios->jusic);
   }

    //musica background a jogar
    else if(st->sound == 3){
    sfMusic_pause(audios->music);

    audios->jusic = sfMusic_createFromFile("bplay3.wav");
    sfMusic_setVolume(audios->jusic, 5);

    sfMusic_setLoop(audios->jusic, sfTrue);
    sfMusic_play(audios->jusic);
   }
}


void effects(STATE *st,MOB *mobs,AUDIO *audios){

    //sound effect quando o jogador sai do jogo
    if(st->sound == 11){
    
    menuNoob();

    //destruir todos os audios antes de sair
    if(audios->jusic != NULL){
    sfMusic_pause(audios->jusic);
    sfMusic_destroy(audios->jusic);
    }
    if(audios->music != NULL){
    sfMusic_pause(audios->music);
    sfMusic_destroy(audios->music);
    }
    if(audios->siu != NULL){
    sfSound_pause(audios->siu);
    sfSound_destroy(audios->siu);
    sfSoundBuffer_destroy(audios->buffersiu);
    }
    if(audios->elecsium != NULL){
    sfSound_pause(audios->elecsium);
    sfSound_destroy(audios->elecsium);
    sfSoundBuffer_destroy(audios->bufferelecsium);
    }
    if(audios->tp != NULL){
    sfSound_pause(audios->tp);
    sfSound_destroy(audios->tp);
    sfSoundBuffer_destroy(audios->buffertp);
    }
    if(audios->mk != NULL){
    sfSound_pause(audios->mk);
    sfSound_destroy(audios->mk);
    sfSoundBuffer_destroy(audios->buffermk);
    }

    audios->buffersaiu = sfSoundBuffer_createFromFile("saiu.wav");

    audios->saiu = sfSound_create();
    sfSound_setBuffer(audios->saiu, audios->buffersaiu);

    sfSound_setVolume(audios->saiu, 100);
    sfSound_play(audios->saiu);

    while (sfSound_getStatus(audios->saiu) == sfPlaying) {}


    sfSound_destroy(audios->saiu);
    sfSoundBuffer_destroy(audios->buffersaiu);
    
    endwin();
    exit(0);
    FREE_MOB(mobs);
    }

    //sound effect menu vitÃ³ria
    else if(st->sound == 5){

    //destruir todos os audios antes de sair
    if(audios->jusic != NULL){
    sfMusic_pause(audios->jusic);
    sfMusic_destroy(audios->jusic);
    }
    if(audios->music != NULL){
    sfMusic_pause(audios->music);
    sfMusic_destroy(audios->music);
    }
    if(audios->siu != NULL){
    sfSound_pause(audios->siu);
    sfSound_destroy(audios->siu);
    sfSoundBuffer_destroy(audios->buffersiu);
    }
    if(audios->elecsium != NULL){
    sfSound_pause(audios->elecsium);
    sfSound_destroy(audios->elecsium);
    sfSoundBuffer_destroy(audios->bufferelecsium);
    }
    if(audios->tp != NULL){
    sfSound_pause(audios->tp);
    sfSound_destroy(audios->tp);
    sfSoundBuffer_destroy(audios->buffertp);
    }
    if(audios->mk != NULL){
    sfSound_pause(audios->mk);
    sfSound_destroy(audios->mk);
    sfSoundBuffer_destroy(audios->buffermk);
    }

    audios->bufferganhou = sfSoundBuffer_createFromFile("ganhou.wav");

    audios->ganhou = sfSound_create();
    sfSound_setBuffer(audios->ganhou, audios->bufferganhou);

    sfSound_setVolume(audios->ganhou, 100);
    sfSound_play(audios->ganhou);

    while (sfSound_getStatus(audios->ganhou) == sfPlaying) {}

    sfSound_destroy(audios->ganhou);
    sfSoundBuffer_destroy(audios->bufferganhou);

    endwin();
    exit(0);
    FREE_MOB(mobs);
    }

    //sound effect quando o jogador avancou para outro floor
    else if(st->playerX == st->objetivoX && st->playerY == st->objetivoY){

    audios->buffersiu = sfSoundBuffer_createFromFile("siu.wav");

    audios->siu = sfSound_create();
    sfSound_setBuffer(audios->siu, audios->buffersiu);

    sfSound_setVolume(audios->siu, 60);
    sfSound_play(audios->siu);
    }

    //sound effect quando o jogador consome elecsium
    else if(st->sound == 6){

    audios->bufferelecsium = sfSoundBuffer_createFromFile("elecsium.wav");

    audios->elecsium = sfSound_create();
    sfSound_setBuffer(audios->elecsium, audios->bufferelecsium);

    sfSound_setPitch(audios->elecsium, 1.5);

    sfSound_setVolume(audios->elecsium, 100);
    sfSound_play(audios->elecsium);
    }

    //sound effect quando o jogador usa o teletransporte
    else if(st->sound == 7){

    audios->buffertp = sfSoundBuffer_createFromFile("teletransporte.wav");

    audios->tp = sfSound_create();
    sfSound_setBuffer(audios->tp, audios->buffertp);

    sfSound_setVolume(audios->tp, 100);
    sfSound_play(audios->tp);
    }

    //sound effect quando o jogador mata o boss
    else if(st->sound == 9){

    audios->buffermk = sfSoundBuffer_createFromFile("boss.wav");

    audios->mk = sfSound_create();
    sfSound_setBuffer(audios->mk, audios->buffermk);

    sfSound_setVolume(audios->mk, 100);
    sfSound_play(audios->mk);
    }
}


void som(STATE *st,MOB *mobs,AUDIO *audios){
    background(st, audios);
    effects(st,mobs,audios);
}