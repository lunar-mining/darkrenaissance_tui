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
    login_window = newwin(20, 0, 0, 0);
    login_panel = new_panel(login_window);
    box(login_window, 0, 0);

    flame_window = newwin(20, 50, 18, 4);
    flame_panel = new_panel(flame_window);
    box(flame_window, 0, 0);
    mvwprintw(flame_window, 10, 38, heart);
    wrefresh(flame_window);

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_MAGENTA);

    mvwprintw(login_window, 10, 38, heart);
    mvwchgat(login_window, 10, 10, -1, A_BLINK, 2, NULL);

    mvwprintw(login_window, 17, 33, enter_msg);
    mvwchgat(login_window, 17, 33, -1, A_DIM, 2, NULL);

    mvwprintw(login_window, 13, 18, welcome_msg);
    mvwchgat(login_window, 13, 18, -1, A_ITALIC, 1, NULL);

    mvwprintw(login_window, 14, 18, welcome_msg);
    mvwchgat(login_window, 14, 18, -1, A_ITALIC | A_DIM, 1, NULL);

    print_in_middle(login_window, LINES / 2, 0, 0, welcome_msg);

    //flames();
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
    mvwchgat(win, y, x, -1, A_BOLD | A_ITALIC, 1, NULL);
    refresh();
}       

// TODO: refactor into proper C++ code
// i.e. use 'new'
void login::flames(void)
	{
	int width, height, size, i;
	const char characters[] = {' ', '.', ':', '^', '*', 'x', 's', 'S', '#', '$'};
	
	getmaxyx(login_window,height,width);
	size=width*height;
	init_pair(1,0,0);
	init_pair(2,6,0);
	init_pair(3,5,0);
	init_pair(4,6,0);
	clear();
	
	int *b= (int *) calloc((size+width+1),sizeof(int));
	nodelay(login_window,TRUE);
	srand(time(NULL));

	for (;;)
		{
		for (i =0; i < width/20; i++)
			b[(int)(((float)rand()/(float)RAND_MAX)*width+width*(height-1))]=65;
		for (i=0; i < size; i++)
			{
			b[i]=(b[i]+b[i+1]+b[i+width]+b[i+width+1])/4;
			if (b[i] > 15)
				wattrset(login_window, COLOR_PAIR(4)|A_DIM);
			else if (b[i] > 9)
				wattrset(login_window, COLOR_PAIR(3)|A_DIM);
			else if (b[i] > 4)
				wattrset(login_window, COLOR_PAIR(2)|A_DIM);
			else
				wattrset(login_window, COLOR_PAIR(1)|A_DIM);
			if (i < size-1)
				{
				move(i/width, i%width);
				if (b[i] > 9)
					waddch(login_window, characters[9]);
				else
					waddch(login_window, characters[b[i]]);
				}
			}
		refresh();
		timeout(30);
		//if (getch() != ERR)
			//break;
		}
	
	free(b);
	return;
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
