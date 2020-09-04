#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include "menu.hpp"
#include "pages.hpp"

menu::menu()
{
    int n_lines = 3;
    int n_columns = 50;

    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    menu_window = newwin(n_lines, n_columns, 1, 15.5);
    print_menu(menu_window, highlight);

}

void menu::print_menu(WINDOW *menu_window, int highlight)
{    
    int x = 3;
    int y = 1;
    int i;

    box(menu_window, 0, 0);
    const char *choices[] = 
    {
        "   SEND",
        "RECEIVE",
        "BALANCE",
        "HISTORY",
        "QUIT",
    };

    int n_choices = sizeof(choices) / sizeof(char *);

    for (i = 0; i < n_choices; i++)
    {
        //mvwprintw(menu_window, 0, 0, "for loop started");
        if (highlight == i +1) // if i + highlight = selection
        {
            //mvwprintw(menu_window, 0, 0, "if executed");
            wattron(menu_window, COLOR_PAIR(1) | A_BOLD);
            mvwprintw(menu_window, y, x, choices[i]);
            wattroff(menu_window, COLOR_PAIR(1)| A_BOLD);
        }
        else
            //mvwprintw(menu_window, 0, 0, "else executed");
            mvwprintw(menu_window, y, x, choices[i]);
        x += 9;
    }
    wrefresh(menu_window);
}

void menu::activate()
{
    const char *choices[] = 
    {
        "   SEND",
        "RECEIVE",
        "BALANCE",
        "HISTORY",
        "QUIT",
    };

    int n_choices = sizeof(choices) / sizeof(char *);
    menu menu;
    pages pages;
    int choice = 0;
    int highlight = 0;

    while (1)
    {
        c = wgetch(menu_window);
        switch(c)
        {
            case KEY_LEFT:
                pages.top = (PANEL *)panel_userptr(pages.top);
                top_panel(pages.top);
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_RIGHT:
                pages.top = (PANEL *)panel_userptr(pages.top);
                top_panel(pages.top);
                if(highlight== n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 9:
                pages.top = (PANEL *)panel_userptr(pages.top);
                top_panel(pages.top);
                // reads: if highlight = 5, set highlight to one 
                // iterate
                // should read: 
                // for highlight = 1, highlight != 5, ++highlight;
                if(highlight== n_choices)
                    highlight =1;
                else
                    ++highlight;
                break;
            default:
                refresh();
                break;
        }
        update_panels();
        doupdate();
        print_menu(menu_window, highlight);
        if (choice != 0)
            break;
    }
    clrtoeol();
    refresh();    
    endwin();
}

