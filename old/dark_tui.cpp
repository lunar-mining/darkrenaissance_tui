// newterm to open ncurses file (i.e. wallet intro)
#include <iostream>
#include <ncurses.h>
#include <panel.h>
#include <menu.h>
#include <string.h>

// TODO: make box into simple rectangle. make new menu to cycle through pages

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

//TODO:: flashing love hearts
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

    void activate_wallet();
    void enter_press();
    void print_in_middle(WINDOW *win, int starty, int startx, int width, const char *string);
};

login::login()
{
    const char *welcome_msg = "WELCOME TO THE DARK RENAISSANCE";
    const char *enter_msg = "PRESS ENTER";
    const char *heart = "<3";

    curs_set(0);
    login_window = newwin(0, 0, 0, 0);
    login_panel = new_panel(login_window);

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);

   // wattron(login_window, COLOR_PAIR(1));
    print_in_middle(login_window, LINES / 2, 0, 0, enter_msg);
    //wattroff(login_window, COLOR_PAIR(1));
    wattron(login_window, COLOR_PAIR(2));

    mvwprintw(login_window, 3, 38, heart);
    mvwchgat(login_window, 3, 10, -1, A_BLINK, 2, NULL);

    wattron(login_window, COLOR_PAIR(3));
    getmaxyx(login_window, row, col);
    mvwprintw(login_window, 2, 25, welcome_msg);
    mvwchgat(login_window, 2, 0, -1, A_REVERSE, 3, NULL);

    wattroff(login_window, COLOR_PAIR(3));
    enter_press();
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
    //mvwchgat(win, y, x, -1, A_BLINK, 1, NULL);
    refresh();
}       

void login::enter_press()
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
}

class wallet_gui
{
public:
    wallet_gui();
    class login;
    class menu;
    class pages;
};

wallet_gui::wallet_gui()
{
}

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
    const char *choices[];
    void menu_scroll();
};

menu::menu()
{
    int n_lines = 3;
    int n_columns = 50;
    int x = 3;
    int y = 1;
    int highlight = 1;

   // init_pair(1, COLOR_CYAN, COLOR_BLACK);

    const char *choices[] = 
    {
        "   SEND",
        "RECEIVE",
        "BALANCE",
        "HISTORY",
        "QUIT",
    };

    int n_choices = sizeof(choices) / sizeof(char *);
    menu_window = newwin(n_lines, n_columns, y, 15.5);
    box(menu_window, 0, 0);

    for (i = 0; i < n_choices; ++i)
    {
        if (highlight = i +1)
        {
            wattron(menu_window, COLOR_PAIR(1));
            mvwprintw(menu_window, y, x, choices[i]);
            wattroff(menu_window, COLOR_PAIR(1));
        }
        else
            mvwprintw(menu_window, y, x, choices[i]);
        x += 9;
    }
    
    wrefresh(menu_window);
}

void menu::menu_scroll()
{
    int choice = 0;
    while (1)
    {
        c = wgetch(menu_window);
        switch(c)
        {
            case 9:
                //pages.top_page = (PANEL *)panel_userptr(top_page);
                //top_panel(top_page);
                if(highlight == n_choices)
                    highlight == 1;
                else 
                    highlight;
                break;
            default:
                refresh();
                break;
        }
        update_panels();
        doupdate();
        if (choice != 0)
            break;
    }
}

class pages
{
public:
    pages();
    WINDOW *page_window[5];
    PANEL *page_panel[5];
    PANEL *top_page;

    void create_windows(WINDOW **page_wins, int n);
    void show_windows(WINDOW *page_wins, char *label, int label_color);
};

pages::pages()
{
    create_windows(page_window, 5);

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
    doupdate();
    top_page = page_panel[2];
}

void pages::create_windows(WINDOW **page_wins, int n)
{
    int x, y, i;
    char send[80];
    char receive[80];
    char balance[80];
    char history[80];
    char quit[80];
    //TODO: Calculate x and y according to screen size
    y = 4;
    x = 15.5;

    // rows, columns, y, x
    page_wins[0] = newwin(20, 50, y, x);
    sprintf(send, "*", 0);
    page_wins[1] = newwin(20, 50, y, x); 
    sprintf(receive, "o", 1);
    page_wins[2] = newwin(20, 50, y, x); 
    sprintf(balance, "<3", 2);
    page_wins[3] = newwin(20, 50, y, x); 
    sprintf(history, "?!", 3);
    page_wins[4] = newwin(20, 50, y, x); 
    sprintf(quit, ":D", 4);

    show_windows(page_wins[0], send, 1);
    show_windows(page_wins[1], receive, 2);
    show_windows(page_wins[2], balance, 3);
    show_windows(page_wins[3], history, 4);
    show_windows(page_wins[4], quit, 0);
}

void pages::show_windows(WINDOW *page_wins, char *label, int label_color)
{
    int x = 1;
    int y = 1;

    int startx, starty, height, width, i;
    getbegyx(page_wins, starty, startx);
    getmaxyx(page_wins, height, width);
    box(page_wins, 0, 0);
    mvwaddch(page_wins, 2, 0, ACS_LTEE);
    mvwaddch(page_wins, 2, width - 1, ACS_RTEE);
    mvwprintw(page_wins, 5, 23, label);
    // TODO: implement page functionality
}

int main()
{   
    initscr();
    start_color();
    clear();
    noecho();
    cbreak();

    login login;
    //pages wallet_pages;
    //menu wallet_menu;

    //keypad(stdscr, TRUE);
    curs_set(0);
    refresh();
    
    clrtoeol();
    refresh();
    endwin();
    return 0;
}

