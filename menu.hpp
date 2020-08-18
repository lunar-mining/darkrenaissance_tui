#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include <panel.h>

class menu
{
public:
    menu();
    WINDOW *menu_window;
    PANEL *menu_top;

    int n_choices, i, c; 
    int x, y;
    int n_lines, n_columns;
    int highlight;
    void print_menu(WINDOW *menu_window, int highlight);
    void activate();
};

#endif
