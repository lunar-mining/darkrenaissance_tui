#include <stdio.h> 
#include <ncurses.h>
#include <panel.h>  
#include <string.h>

#define NLINES 18
#define NCOLS 40

// TODO: refactor as ENUM
// classes for each enum variable i.e. class send{} etc
// refactor into object orientated style i.e. isolate objects into classes
// Object-orientated design: combining data and its operation into context-bound
// entity (class, struct)

int startx = 0;
int starty = 0;
const char *choices[] = 
{
    "SEND",
    "RECIEVE",
    "BALANCE",
    "HISTORY",
    "QUIT",
};

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_window, int highlight);
void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
//void activate_panels(WINDOW *page_window[3], PANEL *pages[3], PANEL *top);

int main()
{
    WINDOW *menu_window;
    WINDOW *page_window[5];
    PANEL  *pages[5];
    PANEL  *top;
    int ch;

    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak(); // line buffering disabled
    
    menu_window = newwin(10, 20, 0, 0);

    keypad(menu_window, TRUE);
    start_color();

    refresh();

    print_menu(menu_window, highlight); 

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
      
    init_wins(page_window, 5);

    pages[0] = new_panel(page_window[0]);
    pages[1] = new_panel(page_window[1]);
    pages[2] = new_panel(page_window[2]);
    pages[3] = new_panel(page_window[3]);
    pages[4] = new_panel(page_window[4]);

    set_panel_userptr(pages[0], pages[1]);
    set_panel_userptr(pages[1], pages[2]);
    set_panel_userptr(pages[2], pages[3]);
    set_panel_userptr(pages[3], pages[4]);
    set_panel_userptr(pages[4], pages[0]);

    update_panels();

    attron(COLOR_PAIR(5));
    attroff(COLOR_PAIR(5));

    doupdate();
    top = pages[2];

    while(1)
    {
        c = wgetch(menu_window);
        switch(c)
        {
            /*case KEY_UP:
                top = (PANEL *)panel_userptr(top);
                top_panel(top);
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                top = (PANEL *)panel_userptr(top);
                top_panel(top);
                if(highlight== n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                top = (PANEL *)panel_userptr(top);
                top_panel(top);
                choice = highlight;
                break;*/
            case 9:
                top = (PANEL *)panel_userptr(top);
                top_panel(top);
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            default:
                mvprintw(24, 0, "oh hi");
                refresh();
                break;
        }
        // ++panel
        update_panels();
        doupdate(); 
        print_menu(menu_window, highlight);
        if(choice != 0)
            break;
    }
    clrtoeol();
    refresh();    

    endwin();
    return 0;
}

void init_wins(WINDOW **wins, int n)
{
    int x, y, i;
    char send[80];
    char receive[80];
    char balance[80];
    char history[80];
    char quit[80];
    y = 2;
    x = 35;

    wins[0] = newwin(NLINES, NCOLS, y, x);
    sprintf(send, "SEND", 0);
    wins[1] = newwin(NLINES, NCOLS, y, x); 
    sprintf(receive, "RECEIVE", 1);
    wins[2] = newwin(NLINES, NCOLS, y, x); 
    sprintf(balance, "BALANCE", 2);
    wins[3] = newwin(NLINES, NCOLS, y, x); 
    sprintf(history, "HISTORY", 3);
    wins[4] = newwin(NLINES, NCOLS, y, x); 
    sprintf(quit, "QUIT", 4);

    win_show(wins[0], send, 0);
    win_show(wins[1], receive, 1);
    win_show(wins[2], balance, 2);
    win_show(wins[3], history, 3);
    win_show(wins[4], quit, 4);

    /*for(i = 0; i < n; ++i)
    {
        wins[i] = newwin(NLINES, NCOLS, y, x);
        sprintf(label, "Window Number %d", i + 1);
        win_show(wins[i], label, i + 1);
       // y += 3;
        //x += 7;
    }*/
}

void win_show(WINDOW *win, char *label, int label_color)
{
    int startx, starty, height, width;
    getbegyx(win, starty, startx);
    getmaxyx(win, height, width);
    box(win, 0, 0);
    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, width - 2);
    mvwaddch(win, 2, width - 1, ACS_RTEE);
    print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
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
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string); 
    wattroff(win, color);
    refresh();
}

void print_menu(WINDOW *menu_window, int highlight)
{
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_window, 0, 0);
    for(i = 0; i < n_choices; ++i)
    {
        if(highlight == i +1)
        {
            wattron(menu_window, A_REVERSE);
            mvwprintw(menu_window, y, x,  choices[i]);
            wattroff(menu_window, A_REVERSE);
        }
        else
            mvwprintw(menu_window, y, x,  choices[i]);
        ++y;
    }
    wrefresh(menu_window);
}

/*void activate_panels(WINDOW *page_window[3], PANEL *pages[3], PANEL *top)
{
    int ch;
     
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
      
    init_wins(page_window, 3);
    pages[0] = new_panel(page_window[0]);
    pages[1] = new_panel(page_window[1]);
    pages[2] = new_panel(page_window[2]);
    set_panel_userptr(pages[0], pages[1]);
    set_panel_userptr(pages[1], pages[2]);
    set_panel_userptr(pages[2], pages[0]);
    update_panels();
    attron(COLOR_PAIR(4));
    attroff(COLOR_PAIR(4));
    doupdate();
    top = pages[2];
    while((ch = getch()) != KEY_F(1))
    {
        switch(ch)
        {
            case 9:
                top = (PANEL *)panel_userptr(top);
                top_panel(top);
                break;
        }
        update_panels();
        doupdate(); 
    }
    //refresh();
}*/
