#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

// TODO: white pattern flashing, white text 

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);

int main(int argc, char *argv[])
{
    int row,col;
    char welcome[]="DARK RENAISSANCE WALLET <3";
    initscr();/* Start curses mode            */
    start_color();/* Start color                  */

    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    print_in_middle(stdscr, LINES / 2, 0, 0, "PRESS ENTER");

    getmaxyx(stdscr,row, col);
    mvprintw(0, (col-strlen(welcome)/2), welcome);
    //mvprintw(2, 20, "DARK RENAISSANCE WALLET");
    attroff(COLOR_PAIR(1));
    getch();
    endwin();
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
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
    mvwprintw(win, y, x, "%s", string);
    mvchgat(y, x, -1, A_BLINK, 1, NULL);
    refresh();
}       
