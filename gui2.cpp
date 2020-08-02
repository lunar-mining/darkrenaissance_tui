#include <stdio.h>
#include <ncurses.h>
#include <panel.h>
#include <string.h>

#define NLINES 20
#define NCOLS 50   

int startx = 0;
int starty = 0;     

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

int main()
{
    WINDOW *page_window[5]; // windows are attached to panels
    PANEL *page_panel[5];
    PANEL *top;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    refresh();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);

    init_wins(page_window, 5);

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

    attron(COLOR_PAIR(5));
    attroff(COLOR_PAIR(5));
    
    doupdate();
    top = page_panel[2];

    while(1)
    {
        c = wgetch(stdscr);
        switch(c)
        {
        case 9:
            top = (PANEL *)panel_userptr(top);
            top_panel(top);
        default:
            refresh();
            break;
        }
    update_panels();
    doupdate();
    }
    clrtoeol();
    refresh();
    endwin();
    return 0;
}

void init_wins(WINDOW **wins, int n)
{
    int x, y, i;
    char send[80];
    char receive[80];
    char balance[80];
    char history[80];
    char quit[80];
    //TODO: Calculate x and y according to screen size
    y = 2;
    x = 15.5;

    wins[0] = newwin(NLINES, NCOLS, y, x);
    sprintf(send, "SEND", 0);
    wins[1] = newwin(NLINES, NCOLS, y, x); 
    sprintf(receive, "RECEIVE", 1);
    wins[2] = newwin(NLINES, NCOLS, y, x); 
    sprintf(balance, "BALANCE", 2);
    wins[3] = newwin(NLINES, NCOLS, y, x); 
    sprintf(history, "HISTORY", 3);
    wins[4] = newwin(NLINES, NCOLS, y, x); 
    sprintf(quit, "QUIT", 4);

    win_show(wins[0], send, 0);
    win_show(wins[1], receive, 1);
    win_show(wins[2], balance, 2);
    win_show(wins[3], history, 3);
    win_show(wins[4], quit, 4);
}

void win_show(WINDOW *win, char *label, int label_color)
{
    int startx, starty, height, width;
    getbegyx(win, starty, startx);
    getmaxyx(win, height, width);
    box(win, 0, 0);
    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, width - 2);
    mvwaddch(win, 2, width - 1, ACS_RTEE);
    print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
    int length, x, y;
    float temp;

    if(win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if(startx != 0)
        x = startx;
    if(starty != 0)
        y = starty;
    if(width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - length)/ 2;
    x = startx + (int)temp;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string); 
    wattroff(win, color);
    refresh();
}

