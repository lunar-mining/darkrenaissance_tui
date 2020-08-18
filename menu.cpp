#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include "menu.hpp"
#include "pages.hpp"

menu::menu()
{
    int n_lines = 3;
    int n_columns = 50;
    int x = 3;
    int y = 1;
    int highlight = 1;
    int i;

    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    menu_window = newwin(n_lines, n_columns, y, 15.5);
    //print_menu(menu_window, highlight);
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
    for (i = 0; i < n_choices; ++i)
    {
        if (highlight = i +1)
        {
            mvwprintw(menu_window, 0, 0, "highlight activated");
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

void menu::print_menu(WINDOW *menu_window, int highlight)
{    
   /* const char *choices[] = 
    {
        "   SEND",
        "RECEIVE",
        "BALANCE",
        "HISTORY",
        "QUIT",
    };

    int n_choices = sizeof(choices) / sizeof(char *);
    for (i = 0; i < n_choices; ++i)
    {
        if (highlight = i +1)
        {
            mvwprintw(menu_window, 0, 0, "highlight activated");
            wattron(menu_window, COLOR_PAIR(1));
            mvwprintw(menu_window, y, x, choices[i]);
            wattroff(menu_window, COLOR_PAIR(1));
        }
        else
            mvwprintw(menu_window, y, x, choices[i]);
        x += 9;
    }
    wrefresh(menu_window);*/
}

void menu::activate()
{
    pages pages;
    int choice = 0;

    while (1)
    {
        c = wgetch(menu_window);
        /*switch(c)
        {
            case KEY_LEFT:
                mvwprintw(menu_window, 0, 0, "key left pressed");
                pages.top = (PANEL *)panel_userptr(pages.top);
                top_panel(pages.top);
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_RIGHT:
                mvwprintw(menu_window, 0, 0, "key right pressed");
                pages.top = (PANEL *)panel_userptr(pages.top);
                top_panel(pages.top);
                if(highlight== n_choices)
                    highlight = 1;
                else
                    ++highlight;
            case 9:
                mvwprintw(menu_window, 0, 0, "tab pressed");
                pages.top = (PANEL *)panel_userptr(pages.top);
                top_panel(pages.top);
                if(highlight == 1)
                    highlight = n_choices;
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
            break;*/
    }
    clrtoeol();
    refresh();    
    endwin();
}

