#include <stdio.h> 
#include <ncurses.h>
#include <menu.h>

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

int main(int argc, char* argv[])
{
    WINDOW *menu_window;

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
    endwin();                       /* End curses mode                */
    return 0;
}

void print_menu(WINDOW *menu_window, int highlight)
{
    int x, y, i;
    x = 2;
    y = 2;
   // box(menu_window, 0, 0);
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

