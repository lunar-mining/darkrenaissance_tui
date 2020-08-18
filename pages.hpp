#ifndef PAGES_HPP
#define PAGES_HPP

#include <ncurses.h>
#include <panel.h>

class pages
{
public:
    pages();
    WINDOW *page_window[5];
    PANEL *page_panel[5];
    PANEL *top;

    void create_windows(WINDOW **page_wins, int n);
    void show_windows(WINDOW *page_wins, char *label, int label_color);
};

#endif
