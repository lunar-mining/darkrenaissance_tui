#include <ncurses.h>
#include <panel.h>
#include "login.hpp"
#include "pages.hpp"
#include "menu.hpp"

void login_input()
{
    int c;
    login login;
    menu menu;

    //mvwprintw(login.login_window, 0, 0, "login started");
    while(true)
    {
        c = wgetch(login.login_window);
        switch(c)
        {
            case 10:
                menu.activate();
                break;
        }
        doupdate();
    }
}

int main()
{   
    int c;
    // loop in main function
    // only one loop in entire program
    initscr();
    start_color();
    clear();
    noecho();
    cbreak();

    //pages pages;
    //menu menu;

    while(true)
    {
        login_input();
        //refresh();
        //endwin();
    }

    endwin();
    curs_set(0);
    refresh();
    
    clrtoeol();
    refresh();
    endwin();
    return 0;
}



