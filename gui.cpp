#include <ncurses.h>

int main(int argc, char* argv[])
{
    initscr();
    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    printw("DARK RENAISSANCE WALLET");
    mvchgat(0, 0, -1, A_BLINK, 1, NULL);

    refresh();
    getch();
    endwin();
    return 0;
}


