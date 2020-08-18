#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <ncurses.h>
#include <panel.h>

class login
{
public:
    login();
    WINDOW *login_window;
    PANEL *login_panel;

    const char *welcome_msg;
    const char *enter_msg;
    const char *heart;

    int row, col;
    int c;

    //void activate_wallet();
    //void enter_press();
    void print_in_middle(WINDOW *win, int starty, int startx, int width, const char *string);
};

#endif
