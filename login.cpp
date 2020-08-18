#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include "login.hpp"

login::login()
{
    const char *welcome_msg = "D A R K  R E N A I S S A N C E  W A L L E T";
    const char *enter_msg = "PRESS ENTER";
    const char *heart = "<3";

    curs_set(0);
    login_window = newwin(0, 0, 0, 0);
    login_panel = new_panel(login_window);

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

    mvwprintw(login_window, 10, 38, heart);
    mvwchgat(login_window, 10, 10, -1, A_BLINK, 2, NULL);

    //mvwprintw(login_window, 16, 38, heart);
    //mvwchgat(login_window, 16, 10, -1, A_BLINK, 2, NULL);

    mvwprintw(login_window, 14, 33, enter_msg);
    mvwchgat(login_window, 14, 33, -1, A_ITALIC, 1, NULL);

    print_in_middle(login_window, LINES / 2, 0, 0, welcome_msg);
}

void login::print_in_middle(WINDOW *win, int starty, int startx, int width, const char *string)
{
    int length, x, y;
    float temp;
    if(win == NULL)
        win = login_window;
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
    mvwchgat(win, y, x, -1, A_BOLD, 1, NULL);
    refresh();
}       

/*void login::enter_press()
{
    while(1)
    {
        c = wgetch(login_window);
        switch(c)
        {
            case KEY_ENTER:
            activate_wallet();
        }
        doupdate();
    }
    endwin();
}

void login::activate_wallet()
{
  // need to passs reference to menu and pages (or menu+pages)
  // that activates on key press
}*/
