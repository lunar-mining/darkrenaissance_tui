#include <stdio.h>
#include <iostream>
#include <ncurses.h>
#include <panel.h>
#include <string.h>

#define NLINES 20
#define NCOLS 50   

int startx = 0;
int starty = 0;     

const char *choices[] = 
{
    "SEND",
    "RECIEVE",
    "BALANCE",
    "HISTORY",
    "QUIT",
};

int n_choices = sizeof(choices) / sizeof(char *);
//void print_menu(WINDOW *menu_window, int highlight);
void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

int main()
{
    WINDOW *menu_window;
    WINDOW *page_window[5]; // windows are attached to panels
    PANEL *page_panel[5];
    PANEL *top;

    int c;
    int choice = 0;
    int highlight = 1;

    initscr();
    clear();
    noecho();
    cbreak();

    menu_window = newwin(0, 0, 0, 0);

    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    refresh();

    //print_menu(menu_window, highlight); 

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
            if(highlight == n_choices)
                highlight = 1;
            else
                ++ highlight;
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
    sprintf(send, "  SEND", 0);
    wins[1] = newwin(NLINES, NCOLS, y, x); 
    sprintf(receive, "RECEIVE", 1);
    wins[2] = newwin(NLINES, NCOLS, y, x); 
    sprintf(balance, "BALANCE", 2);
    wins[3] = newwin(NLINES, NCOLS, y, x); 
    sprintf(history, "HISTORY", 3);
    wins[4] = newwin(NLINES, NCOLS, y, x); 
    sprintf(quit, "  QUIT", 4);

    win_show(wins[0], send, 1);
    win_show(wins[1], receive, 2);
    win_show(wins[2], balance, 3);
    win_show(wins[3], history, 4);
    win_show(wins[4], quit, 0);

   //for (i = 0; i < n; ++i)
    //{
        //mvwprintw(stdscr, x, y, send);
        //y += 7;

    //print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void win_show(WINDOW *win, char *label, int label_color)
{
    int x = 1;
    int y = 1;
    int highlight;

    int startx, starty, height, width, i;
    getbegyx(win, starty, startx);
    getmaxyx(win, height, width);
    box(win, 0, 0);
    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, width - 2);
    mvwaddch(win, 2, width - 1, ACS_RTEE);

    for(i = 0; i < n_choices; ++i)
    {
        if (highlight = i +1)
        {
            wattron(win, COLOR_PAIR(4));
            mvwprintw(win, x, y, choices[i]);
            wattroff(win, COLOR_PAIR(4));
        }
        else
            mvwprintw(win, x, y, choices[i]);
        y +=10;
    }
}

/*void print_menu(WINDOW *menu_window, int highlight)
{
    int x, y, i;
    x = 3;
    y = 15;
    //box(menu_window, 0, 0);
    for(i = 0; i < n_choices; ++i)
    {
        if(highlight == i +1)
        {
            wattron(menu_window, A_REVERSE);
            mvwprintw(menu_window, x, y, "%s", choices[i]);
            wattroff(menu_window, A_REVERSE);
        }
        else
            mvwprintw(menu_window, x, y, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_window);
}*/
/*void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
    int length, x, y, i;
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

    //length = strlen(string);
    //temp = (width - length)/ 2;
    //x = startx + (int)temp;
    wattron(win, color);

    for(i = 0; i < 5; ++i)
    {
        int x = 1;
        int y = 1;
       // wattron(stdscr, A_REVERSE);
        mvwprintw(win, x, y, string); 
        //wattroff(stdscr, A_REVERSE);
        y += 7;
        x += 3;
    }

   for(i = 0; i < n; ++i)
	{
        wins[i] = newwin(NLINES, NCOLS, y, x);
		sprintf(label, "Window Number %d", i + 1);
		win_show(wins[i], label, i + 1);
		y += 3;
		x += 7;
	}
   // mvwprintw(win, 1, 1, "%s", string); 
    wattroff(win, color);
    refresh();
}*/

