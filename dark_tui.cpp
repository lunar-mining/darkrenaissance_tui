// newterm to open ncurses file (i.e. wallet intro)
#include <iostream>
#include <ncurses.h>
#include <panel.h>
#include <menu.h>

// TODO: make box into simple rectangle. make new menu to cycle through pages

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

class menu
{
public:
    menu();
    WINDOW *menu_window;

    int n_choices, i, c; 
    int x, y;
    int n_lines, n_columns;
    int highlight;
    const char *choices[];
};

menu::menu()
{
    int n_lines = 3;
    int n_columns = 50;
    int x = 3;
    int y = 1;
    int highlight = 1;

    init_pair(1, COLOR_CYAN, COLOR_BLACK);

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
        if (highlight = i + 1)
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
    box(page_wins, 0, 0);      wallet_menu.
    mvwaddch(page_wins, 2, 0, ACS_LTEE);
    mvwaddch(page_wins, 2, width - 1, ACS_RTEE);
    mvwprintw(page_wins, 5, 23, label);
    // TODO: implement page functionality
}

int main()
{   
    initscr();
    int c;
    
    clear();
    noecho();
    cbreak();

    pages wallet_pages;
    menu wallet_menu;

    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    refresh();
    
    while (1)
    {
        c = wgetch(wallet_menu.menu_window);
        switch(c)
        {
            case KEY_RIGHT:
            wallet_pages.top_page = (PANEL *)panel_userptr(wallet_pages.top_page);
            top_panel(wallet_pages.top_page);
            if(wallet_menu.highlight == 1)
                wallet_menu.highlight = wallet_menu.n_choices;
            else
                --wallet_menu.highlight;
            break;
            case KEY_LEFT:
            wallet_pages.top_page = (PANEL *)panel_userptr(wallet_pages.top_page);
            top_panel(wallet_pages.top_page);
            if(wallet_menu.highlight == 1)
                wallet_menu.highlight = wallet_menu.n_choices;
            else
                ++wallet_menu.highlight;
            break;
            case 9:
            wallet_pages.top_page = (PANEL *)panel_userptr(wallet_pages.top_page);
            top_panel(wallet_pages.top_page);
            if(wallet_menu.highlight == wallet_menu.n_choices)
                wallet_menu.highlight == 1;
            else 
                ++ wallet_menu.highlight;
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

