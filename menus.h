#include "estado.h"


void drawHealth(STATE *st){
    start_color();
    init_pair(9,COLOR_GREEN,COLOR_GREEN);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    WINDOW *life = newwin(3,50,55,40);
    box(life,'*','-');
    attron(COLOR_PAIR(2));
    mvprintw(54+1,20,"88  88 88\"\"Yb");
    mvprintw(55+1,20,"88  88 88__dP");
    mvprintw(56+1,20,"888888 88\"\"\"");
    mvprintw(57+1,20,"88  88 88");
    attroff(COLOR_PAIR(2));
    for (int i = 1; i < st->playerHP; i++)
    {
        mvwaddch(life,1,i,' ' | COLOR_PAIR(9));
    }
    wrefresh(life);
    refresh();
}

void drawMana(STATE *st){
    //start_color();
    init_pair(69,COLOR_CYAN,COLOR_CYAN);
    init_pair(88,COLOR_CYAN,COLOR_BLACK);
    WINDOW *mana = newwin(3,50,55,125);
    box(mana,'*','-');
    attron(COLOR_PAIR(88));
    mvprintw(54+1,105,"8b    d8 88\"\"Yb");
    mvprintw(55+1,105,"88b  d88 88__dP");
    mvprintw(56+1,105,"88YbdP88 88\"\"\"");
    mvprintw(57+1,105,"88 YY 88 88");
    attroff(COLOR_PAIR(88));
    for (int i = 1; i < st->playerMP; i++)
    {   
        mvwaddch(mana,1,i,' ' | COLOR_PAIR(69));
    }
    wrefresh(mana);
    refresh();
}

void menuDiff(STATE *st){
    //clear();
    WINDOW * menu = newwin(40,110,8,50);
    //wrefresh(menu);
    refresh();

    start_color();

    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    mvwprintw(menu,4,6+2,"   ______ __                                     __ _  ____ ____ _               __ __        ");
	mvwprintw(menu,5,6+2,"  / ____// /_   ____   ____   _____ ___     ____/ /(_)/ __// __/(_)_____ __  __ / // /_ __  __");
	mvwprintw(menu,6,6+2," / /    / __ \\ / __ \\ / __ \\ / ___// _ \\   / __  // // /_ / /_ / // ___// / / // // __// / / /");
	mvwprintw(menu,7,6+2,"/ /___ / / / // /_/ // /_/ /(__  )/  __/  / /_/ // // __// __// // /__ / /_/ // // /_ / /_/ / ");
	mvwprintw(menu,8,6+2,"\\____//_/ /_/ \\____/ \\____//____/ \\___/   \\__,_//_//_/  /_/  /_/ \\___/ \\__,_//_/ \\__/ \\__, /  ");
	mvwprintw(menu,9,6+2,"                                                                                     /____/   ");
    //wrefresh(menu);

    attron(A_BOLD);
    attron(COLOR_PAIR(1));
    mvwprintw(menu,19-4,50,"1) Coward");
    mvwprintw(menu,24-4,50,"2) Normie");
    mvwprintw(menu,29-4,50,"3) Godlike");
    mvwprintw(menu,34-4,50,"q) EXIT");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));
    box(menu,'*','|');
    wrefresh(menu);
    int w = getch();
    switch(w){
        case (int) '1':
            st->dif = 1;
            break;
        case (int) '2':
            st->dif = 2;
            break;
        case (int) '3':
            st->dif = 3;
            break;
        case (int) 'q':
            endwin();
            exit(0);
            break;
    }
    //endwin();
    //exit(0);
}



void menu1(STATE *st){
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

    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);

    attron(A_BOLD);
    attron(COLOR_PAIR(1));
    mvwprintw(menuIn,10+3,51,"1) Human");
    mvwprintw(menuIn,15+3,51,"2) Wizard");
    mvwprintw(menuIn,20+3,51,"3) Orc");
    mvwprintw(menuIn,25+3,51,"4) Assassin");
    mvwprintw(menuIn,30+3,51,"q) EXIT");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));
    box(menuIn,'&','|');
    curs_set(0);
    wrefresh(menuIn);
    int ch = wgetch(menuIn);
    switch(ch){
        case (int) '1':
            st->race = 1;
            clear();
            endwin();
            menuDiff(st);
            break;
        case (int) '2':
            st->race = 2;
            clear(); 
            endwin();
            menuDiff(st);
            break;
        case (int) '3':
            st->race = 3;
            clear();
            endwin();
            menuDiff(st);
            break;
        case (int) '4':
            st->race = 4;
            clear();
            endwin();
            menuDiff(st);
            break;
        case (int) 'q':
            endwin();
            exit(0);
            break;
    }
}   