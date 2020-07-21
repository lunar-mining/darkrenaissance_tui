#include <stdio.h> 
#include <ncurses.h>
#include <panel.h>  
#include <string.h>

#define NLINES 18
#define NCOLS 40

int startx = 0;
int starty = 0;
char *choices[] = 
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
void activate_panels(WINDOW *my_wins[3], PANEL *my_panels[3], PANEL *top);

int main()
{
    WINDOW *menu_window;

    WINDOW *my_wins[3];
    PANEL  *my_panels[3];
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

    while(1)
    {
        c = wgetch(menu_window);
        switch(c)
        {
            case KEY_UP:
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight== n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            case 9:
                activate_panels(my_wins, my_panels, top);
            default:
                mvprintw(24, 0, "oh hi");
                refresh();
                break;
        }
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
    char label[80];
    y = 2;
    x = 35;

    for(i = 0; i < n; ++i)
    {
        wins[i] = newwin(NLINES, NCOLS, y, x);
        sprintf(label, "Window Number %d", i + 1);
        win_show(wins[i], label, i + 1);
       // y += 3;
        //x += 7;
    }
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
            mvwprintw(menu_window, y, x, "%s", choices[i]);
            wattroff(menu_window, A_REVERSE);
        }
        else
            mvwprintw(menu_window, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_window);
}

void activate_panels(WINDOW *my_wins[3], PANEL *my_panels[3], PANEL *top)
{
    int ch;
     
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
      
    init_wins(my_wins, 3);

    my_panels[0] = new_panel(my_wins[0]);
    my_panels[1] = new_panel(my_wins[1]);
    my_panels[2] = new_panel(my_wins[2]);

    set_panel_userptr(my_panels[0], my_panels[1]);
    set_panel_userptr(my_panels[1], my_panels[2]);
    set_panel_userptr(my_panels[2], my_panels[0]);

    update_panels();

    attron(COLOR_PAIR(4));
    attroff(COLOR_PAIR(4));

    doupdate();
    top = my_panels[2];

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
    refresh();
}
