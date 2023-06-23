#include "menus.h"
//#include "utils.h"

/*#define HP 2
#define HBAR 9
#define MP 88
#define MBAR 69
#define ELSIU 110
#define PAUSE 90*/



void drawHP(){
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    attron(COLOR_PAIR(HP));
    mvprintw(54+1,20,"88  88 88\"\"Yb");
    mvprintw(55+1,20,"88  88 88__dP");
    mvprintw(56+1,20,"888888 88\"\"\"");
    mvprintw(57+1,20,"88  88 88");
    attroff(COLOR_PAIR(HP));
    refresh();
}

void drawHealth(STATE *st){
    init_pair(9,COLOR_GREEN,COLOR_GREEN);
    WINDOW *life = newwin(3,50,55,40);
    box(life,'*','-');
    for (int i = 1; i < st->playerHP; i++)
    {
        mvwaddch(life,1,i,' ' | COLOR_PAIR(HBAR));
    }
    wrefresh(life);
    delwin(life);
}

void drawMP(){
    //start_color();
    init_pair(88,COLOR_BLUE,COLOR_BLACK);
    attron(COLOR_PAIR(MP));
    mvprintw(54,105,"d88888b  .o88b. ");
    mvprintw(55,105,"88'     d8P  Y8 ");
    mvprintw(56,105,"88ooooo 8P      ");
    mvprintw(57,105,"88.     Y8b  d8 ");
    mvprintw(58,105,"Y88888P  `Y88P' ");
    attroff(COLOR_PAIR(MP));
    refresh();
}

void drawMana(STATE *st){
    init_pair(69,COLOR_BLUE,COLOR_BLUE);
    WINDOW *mana = newwin(3,50,55,125);
    box(mana,'*','-');
    for (int i = 1; i < st->playerMP; i++)
    {   
        mvwaddch(mana,1,i,' ' | COLOR_PAIR(MBAR));
    }
    wrefresh(mana);
    delwin(mana);
}

void menuDiff(STATE *st,MOB *mobs, AUDIO *audios){
    //clear();
    WINDOW * menu = newwin(40,110,8,50);
    //wrefresh(menu);
    refresh();

    start_color();
    


    mvwprintw(menu,4,6+2,"   ______ __                                     __ _  ____ ____ _               __ __        ");
	mvwprintw(menu,5,6+2,"  / ____// /_   ____   ____   _____ ___     ____/ /(_)/ __// __/(_)_____ __  __ / // /_ __  __");
	mvwprintw(menu,6,6+2," / /    / __ \\ / __ \\ / __ \\ / ___// _ \\   / __  // // /_ / /_ / // ___// / / // // __// / / /");
	mvwprintw(menu,7,6+2,"/ /___ / / / // /_/ // /_/ /(__  )/  __/  / /_/ // // __// __// // /__ / /_/ // // /_ / /_/ / ");
	mvwprintw(menu,8,6+2,"\\____//_/ /_/ \\____/ \\____//____/ \\___/   \\__,_//_//_/  /_/  /_/ \\___/ \\__,_//_/ \\__/ \\__, /  ");
	mvwprintw(menu,9,6+2,"                                                                                     /____/   ");
    //wrefresh(menu);

    attron(A_BOLD);
    mvwprintw(menu,19-4,50,"1) Coward");
    mvwprintw(menu,24-4,50,"2) Normie");
    mvwprintw(menu,29-4,50,"3) Godlike");
    mvwprintw(menu,34-4,50,"q) EXIT");
    attroff(A_BOLD);
    box(menu,'*','|');
    wrefresh(menu);
    int w = getch();
    switch(w){
        case (int) '1':
            st->dif = 1;
            st->sound = 1;
            delwin(menu);
            //endwin();
            break;
        case (int) '2':
            st->dif = 2;
            st->sound = 2;
            delwin(menu);
            //endwin();
            break;
        case (int) '3':
            st->dif = 3;
            st->sound = 3;
            delwin(menu);
            //endwin();
            break;
        case (int) 'q':
            st->sound = 11;
            effects(st,mobs,audios);
            delwin(menu);
            FREE_MOB(mobs);
            endwin();
            exit(0);
            break;
    }
    //endwin();
    //exit(0);
}

void menu1(STATE *st,MOB *mobs, AUDIO *audios){

    //inicializar audio
    st->sound = 0;
    som(st,mobs,audios);

    clear();
    noecho();
    WINDOW * menuIn = newwin(40, 110, 8, 50);
    refresh();
    
     
    mvwprintw(menuIn,3,4,"    ______ __     ______ ______ _____  ____ __  __ __  ___   __     ______ ______ ___    ________  __");
	mvwprintw(menuIn,4,4,"   / ____// /    / ____// ____// ___/ /  _// / / //  |/  /  / /    / ____// ____//   |  / ____/\\ \\/ /");
	mvwprintw(menuIn,5,4,"  / __/  / /    / __/  / /     \\__ \\  / / / / / // /|_/ /  / /    / __/  / / __ / /| | / /      \\  /  ");
	mvwprintw(menuIn,6,4," / /___ / /___ / /___ / /___  ___/ /_/ / / /_/ // /  / /  / /___ / /___ / /_/ // ___ |/ /___    / /  ");
	mvwprintw(menuIn,7,4,"/_____//_____//_____/ \\____/ /____//___/ \\____//_/  /_/  /_____//_____/ \\____//_/  |_|\\____/   /_/   ");
	mvwprintw(menuIn,8,4,"                                                                                                     ");
    
    start_color();

    init_pair(110,COLOR_CYAN,COLOR_BLACK);
    //init_pair(2,COLOR_WHITE,COLOR_BLACK);

    //attron(A_BOLD);
    attron(COLOR_PAIR(110));
    mvwprintw(menuIn,10+3,51,"1) Human");
    mvwprintw(menuIn,15+3,51,"2) Wizard");
    mvwprintw(menuIn,20+3,51,"3) Orc");
    mvwprintw(menuIn,25+3,51,"4) Assassin");
    mvwprintw(menuIn,30+3,51,"q) EXIT");
    attroff(COLOR_PAIR(110));
    //attroff(A_BOLD);
    box(menuIn,'&','|');
    curs_set(0);
    wrefresh(menuIn);
    int ch = wgetch(menuIn);
    switch(ch){
        case (int) '1':
            st->race = 1;
            clear();
            //endwin();
            delwin(menuIn);
            menuDiff(st,mobs,audios);
            break;
        case (int) '2':
            st->race = 2;
            clear(); 
            //endwin();
            delwin(menuIn);
            menuDiff(st,mobs,audios);
            break;
        case (int) '3':
            st->race = 3;
            clear();
            //endwin();
            delwin(menuIn);
            menuDiff(st,mobs,audios);
            break;
        case (int) '4':
            st->race = 4;
            clear();
            //endwin();
            delwin(menuIn);
            menuDiff(st,mobs,audios);
            break;
        case (int) 'q':
            st->sound = 11;
            effects(st,mobs,audios);
            delwin(menuIn);
            endwin();
            FREE_MOB(mobs);
            exit(0);
            break;
        default:
            delwin(menuIn);
            endwin();
            FREE_MOB(mobs);
            exit(0);
            break; 
    }
}

void menuPause(STATE *st, MOB *mobs,AUDIO *audios){

    clear();
    WINDOW * menu = newwin(20,110,8,50);
    WINDOW * opt = newwin(15,50,35,75);
    //wrefresh(menu);
    refresh();

    start_color();

    init_pair(REVERSO,COLOR_BLACK,COLOR_WHITE);
    


    mvwprintw(menu,4,6+2+11,"    __    _ __                                                      __  ");
	mvwprintw(menu,5,6+2+11,"   / /   (_) /_____     ____ _   ____  ___  ____ __________ _____  / /_ ");
	mvwprintw(menu,6,6+2+11,"  / /   / / //_/ _ \\   / __ `/  / __ \\/ _ \\/ __ `/ ___/ __ `/ __ \\/ __/");
	mvwprintw(menu,7,6+2+11," / /___/ / ,< /  __/  / /_/ /  / /_/ /  __/ /_/ (__  ) /_/ / / / / /_  ");
	mvwprintw(menu,8,6+2+11,"/_____/_/_/|_|\\___/   \\__,_/  / .___/\\___/\\__,_/____/\\__,_/_/ /_/\\__/  ");
	mvwprintw(menu,9,6+2+11,"                             /_/                                       ");
    mvwprintw(menu,10,6+6+16,"                                        __     ");
    mvwprintw(menu,11,6+6+16,"   __  ______  __  __   ________  _____/ /_    ");
    mvwprintw(menu,12,6+6+16,"  / / / / __ \\/ / / /  / ___/ _ \\/ ___/ __/    ");
    mvwprintw(menu,13,6+6+16," / /_/ / /_/ / /_/ /  / /  /  __(__  ) /__ _ _ ");
    mvwprintw(menu,14,6+6+16," \\__, /\\____/\\__,_/  /_/   \\___/____/\\__(_|_|_)");
    mvwprintw(menu,15,6+6+16,"/____/                                         ");
    //wrefresh(menu);

    wattron(opt,COLOR_PAIR(REVERSO));
    mvwprintw(opt,5 - 1,15,"FIGHT BACK ?");
    wattroff(opt,COLOR_PAIR(REVERSO));
    mvwprintw(opt,10 - 1,15,"RUN LIKE A COWARD...");
    box(opt,'*','*');
    wrefresh(menu);
    wrefresh(opt);
    keypad(opt, true);
    int flag = 0;
    int cursor = 0;
    while(flag == 0){
        int w = wgetch(opt);
        switch(w){
           case KEY_UP:
                wclear(opt);
                wattron(opt,COLOR_PAIR(REVERSO));
                    mvwprintw(opt,5 - 1,15,"FIGHT BACK ?");
                wattroff(opt,COLOR_PAIR(REVERSO));
                mvwprintw(opt,10 - 1,15,"RUN LIKE A COWARD...");
                cursor = 0;
                box(opt,'*','*');
                break;
            case KEY_DOWN:
                wclear(opt);
                mvwprintw(opt,5 - 1,15,"FIGHT BACK ?");
                wattron(opt,COLOR_PAIR(REVERSO));
                    mvwprintw(opt,10 - 1,15,"RUN LIKE A COWARD...");
                wattroff(opt,COLOR_PAIR(REVERSO));
                cursor = 1;
                box(opt,'*','*');
                break;
            default:
                flag = 1;
                if(cursor == 0){
                    st->sound = -3;
                    som(st,mobs,audios);
                    delwin(menu);
                    delwin(opt);
                    break;
                }
                else{
                    st->sound = 11;
                    effects(st,mobs,audios);
                    delwin(menu);
                    delwin(opt);
                    endwin();
                    exit(0);
                    FREE_MOB(mobs);
                    break;
                }
        }
    }

}

void victory(STATE *st,MOB *mobs,AUDIO *audios){
    clear();
    WINDOW * winner = newwin(50,210,0,0);
    refresh();

    start_color();

    init_pair(REVERSO,COLOR_BLACK,COLOR_WHITE);
    mvwprintw(winner,4 + 18,6+2+11 + 15,"          ______   ____     _   __   ______    ____     ___   ______   __  __    __     ___   ______    ____   ____     _   __   _____         ");
	mvwprintw(winner,5 + 18,6+2+11 + 15,"         / ____/  / __ \\   / | / /  / ____/   / __ \\   /   | /_  __/  / / / /   / /    /   | /_  __/   /  _/  / __ \\   / | / /  / ___/         ");
	mvwprintw(winner,6 + 18,6+2+11 + 15,"        / /      / / / /  /  |/ /  / / __    / /_/ /  / /| |  / /    / / / /   / /    / /| |  / /      / /   / / / /  /  |/ /   \\__ \\          ");
	mvwprintw(winner,7 + 18,6+2+11 + 15,"       / /___   / /_/ /  / /|  /  / /_/ /   / _, _/  / ___ | / /    / /_/ /   / /___ / ___ | / /     _/ /   / /_/ /  / /|  /   ___/ /");
	mvwprintw(winner,8 + 18,6+2+11 + 15,"       \\____/   \\____/  /_/ |_/   \\____/   /_/ |_|  /_/  |_|/_/     \\____/   /_____//_/  |_|/_/     /___/   \\____/  /_/ |_/   /____/");
	mvwprintw(winner,9 + 18,6+2+11 + 15,"                                                                                                                                               ");
    mvwprintw(winner,10 + 18,6+6+16 + 6,"__  __                                                      __     __                             _                                          __");
    mvwprintw(winner,11 + 18,6+6+16 + 6,"\\ \\/ /  ____   __  __         ____ _   _____  ___          / /_   / /_   ___         _      __   (_)   ____    ____   ___    _____          / /");
    mvwprintw(winner,12 + 18,6+6+16 + 6," \\  /  / __ \\ / / / /        / __ `/  / ___/ / _ \\        / __/  / __ \\ / _ \\       | | /| / /  / /   / __ \\  / __ \\ / _ \\  / ___/         / /");
    mvwprintw(winner,13 + 18,6+6+16 + 6," / /  / /_/ // /_/ /        / /_/ /  / /    /  __/       / /_   / / / //  __/       | |/ |/ /  / /   / / / / / / / //  __/ / /            /_/");
    mvwprintw(winner,14 + 18,6+6+16 + 6,"/_/   \\____/ \\__,_/         \\__,_/  /_/     \\___/        \\__/  /_/ /_/ \\___/        |__/|__/  /_/   /_/ /_/ /_/ /_/ \\___/ /_/            (_)   ");
    mvwprintw(winner,15 + 18,6+6+16 + 6,"                                                                                                                                               ");


    wrefresh(winner);

    st->sound = 5;
    effects(st,mobs,audios);  
    delwin(winner);    
}