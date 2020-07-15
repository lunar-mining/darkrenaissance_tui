#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);

int main(int argc, char *argv[])
{
    initscr();/* Start curses mode            */
    start_color();/* Start color                  */

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    print_in_middle(stdscr, LINES / 2, 0, 0, "PRESS ENTER");

    mvprintw(2, 20, "D A R K  R E N A I S S A N C E  W A L L E T");

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

/*int main(int argc, char* argv[])
{
    WINDOW *welcome_window;

    welcome_window = newwin(10, 70, 4, 4);

    initscr();
    mvprintw(welcome_window, 0, 0, "WELCOME TO THE WALLET");
    clear();
    noecho();
    cbreak(); // line buffering disabled

    keypad(welcome_window, TRUE);
    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    mvprintw(10, 20, "ENTER");
    mvchgat(0, 0, -1, A_BLINK, 1, NULL);

    box(welcome_window, 0, 0);
    refresh();

    clrtoeol();
    refresh();
    endwin();
    return 0;      
}*/
