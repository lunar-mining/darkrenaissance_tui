#include <ncurses.h>
#include <panel.h>
#include "pages.hpp"

pages::pages()
{
    create_windows(page_window, 5);

    page_panel[0] = new_panel(page_window[0]);
    page_panel[1] = new_panel(page_window[1]);
    page_panel[2] = new_panel(page_window[2]);
    page_panel[3] = new_panel(page_window[3]);
    page_panel[4] = new_panel(page_window[4]);

    set_panel_userptr(page_panel[0], page_panel[1]);
    set_panel_userptr(page_panel[1], page_panel[2]);
    set_panel_userptr(page_panel[2], page_panel[3]);
    set_panel_userptr(page_panel[3], page_panel[4]);
    set_panel_userptr(page_panel[4], page_panel[0]);

    update_panels();
    doupdate();
    top = page_panel[2];
}

void pages::create_windows(WINDOW **page_wins, int n)
{
    int x, y, i;
    char send[80];
    char receive[80];
    char balance[80];
    char history[80];
    char quit[80];
    //TODO: Calculate x and y according to screen size
    y = 4;
    x = 15.5;

    // rows, columns, y, x
    page_wins[0] = newwin(20, 50, y, x);
    sprintf(send, "*", 0);
    page_wins[1] = newwin(20, 50, y, x); 
    sprintf(receive, "o", 1);
    page_wins[2] = newwin(20, 50, y, x); 
    sprintf(balance, "<3", 2);
    page_wins[3] = newwin(20, 50, y, x); 
    sprintf(history, "?!", 3);
    page_wins[4] = newwin(20, 50, y, x); 
    sprintf(quit, ":D", 4);

    show_windows(page_wins[0], send, 1);
    show_windows(page_wins[1], receive, 2);
    show_windows(page_wins[2], balance, 3);
    show_windows(page_wins[3], history, 4);
    show_windows(page_wins[4], quit, 0);
}

void pages::show_windows(WINDOW *page_wins, char *label, int label_color)
{
    int x = 1;
    int y = 1;

    int startx, starty, height, width, i;
    getbegyx(page_wins, starty, startx);
    getmaxyx(page_wins, height, width);
    box(page_wins, 0, 0);
    mvwaddch(page_wins, 2, 0, ACS_LTEE);
    mvwaddch(page_wins, 2, width - 1, ACS_RTEE);
    mvwprintw(page_wins, 5, 23, label);
    // TODO: implement page functionality
}

