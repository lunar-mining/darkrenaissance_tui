#include <stdio.h> 
#include <ncurses.h>
#include <panel.h>  
#include <string.h>

//#define NLINES 24
//#define NCOLS 60

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
/*enum class wallet_menu
{
    "SEND",
    "RECIEVE",
    "BALANCE",
    "HISTORY",
    "QUIT",
};*/

int n_choices = sizeof(choices) / sizeof(char *);

int main(int argc, char* argv[])
{
    WINDOW *menu_window;

    int highlight = 1;
    int choice = 0;
    int c;
    int selection;

    initscr();
    clear();
    noecho();
    cbreak(); // line buffering disabled
    
    menu_window = newwin(10, 20, 0, 0);

    keypad(menu_window, TRUE);
    start_color();

    refresh();

    while(choice = getch() != 5)
    {
        switch(choice)
        {
            case 1:
                //do something
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                refresh();
                break;
        }

    }

    print_menu(menu_window, highlight);
    while(1)
    {
        c = wgetch(menu_window); // takes key input from menu
        switch(c) // sets key input as switch variable
        {
            case KEY_UP: // if key up is pressed...
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

