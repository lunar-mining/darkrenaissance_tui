// newterm to open ncurses file (i.e. wallet intro)
#include <iostream>
#include <ncurses.h>
#include <panel.h>
#include <menu.h>

class menu
{
public:
    menu();
    
    ITEM **menu_items;
    MENU *wallet_menu;

    // menu scroll
};

menu::menu()
{
    wallet_menu = new_menu((ITEM **)menu_items);
    post_menu(wallet_menu);
    refresh();
}

enum class options
{
    Send,
    Receive,
    Balance,
    History,
    Quit,
};

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
    y = 2;
    x = 15.5;

    page_wins[0] = newwin(20, 50, y, x);
    sprintf(send, "  SEND", 0);
    page_wins[1] = newwin(20, 50, y, x); 
    sprintf(receive, "RECEIVE", 1);
    page_wins[2] = newwin(20, 50, y, x); 
    sprintf(balance, "BALANCE", 2);
    page_wins[3] = newwin(20, 50, y, x); 
    sprintf(history, "HISTORY", 3);
    page_wins[4] = newwin(20, 50, y, x); 
    sprintf(quit, "  QUIT", 4);

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
    int highlight;

    int startx, starty, height, width, i;
    getbegyx(page_wins, starty, startx);
    getmaxyx(page_wins, height, width);
    box(page_wins, 0, 0);
    mvwaddch(page_wins, 2, 0, ACS_LTEE);
    mvwhline(page_wins, 2, 1, ACS_HLINE, width - 2);
    mvwaddch(page_wins, 2, width - 1, ACS_RTEE);
    mvwprintw(page_wins, x, y, label);
}

int main()
{   
    initscr();
    int c;
    
    clear();
    noecho();
    cbreak();

    pages wallet_pages;
    //menu wallet_menu;

    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    
    while (1)
    {
        c = wgetch(stdscr);
        /*switch(c)
        {
        case 9:
            wallet_pages.top_page = (PANEL *)panel_userptr(wallet_pages.top_page);
            top_panel(wallet_pages.top_page);
        default:
            refresh();
            break;
        }
        update_panels();
        doupdate();*/
    }

    clrtoeol();
    refresh();
    endwin();
    return 0;
}

