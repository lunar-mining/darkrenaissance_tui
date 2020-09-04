#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>
#include <time.h>

class login
{
public:
    login();
    WINDOW *login_window;
    WINDOW *flame_window;
    PANEL *login_panel;
    PANEL *flame_panel;

    const char *welcome_msg;
    const char *enter_msg;
    const char *heart;

    int row, col;
    int c;

    //void activate_wallet();
    //void enter_press();
    void print_in_middle(WINDOW *win, int starty, int startx, int width, const char *string);
    void flames(void);
};

#endif
