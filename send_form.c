#include <form.h>

int main()

{
    FIELD *field[4];
    FORM *send_form;
    int ch;
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    field[0] = new_field(1, 35, 4, 18, 0, 0);
    field[1] = new_field(1, 35, 6, 18, 0, 0);
    field[2] = new_field(1, 35, 8, 18, 0, 0);
    field[3] = NULL;

    set_field_fore(field[0], COLOR_PAIR(1));
    set_field_back(field[0], COLOR_PAIR(2));

    set_field_fore(field[1], COLOR_PAIR(1));
    set_field_fore(field[1], COLOR_PAIR(2));

    set_field_fore(field[2], COLOR_PAIR(1));
    set_field_fore(field[2], COLOR_PAIR(2));

    field_opts_off(field[0], O_AUTOSKIP);
    field_opts_off(field[1], O_AUTOSKIP);
    field_opts_off(field[2], O_AUTOSKIP);

    set_field_back(field[0], A_UNDERLINE);
    set_field_back(field[1], A_UNDERLINE);
    set_field_back(field[2], A_UNDERLINE);

    set_field_just(field[0], JUSTIFY_CENTER);
    set_field_just(field[1], JUSTIFY_CENTER);
    set_field_just(field[2], JUSTIFY_CENTER);

    send_form = new_form(field);
    post_form(send_form);

    refresh();

    set_current_field(send_form, field[0]);
    mvprintw(6, 2, "ENTER AMOUNT:");
    mvprintw(8, 2, "ENTER FEE:");
    mvprintw(4, 2, "ENTER ADDRESS:");

    refresh();

    while((ch = getch()) != KEY_F(1))
    {
        switch(ch)
        {
            case KEY_DOWN:
                form_driver(send_form, REQ_NEXT_FIELD);
                form_driver(send_form, REQ_END_LINE);
                break;
            case KEY_UP:
                form_driver(send_form, REQ_PREV_FIELD);
                form_driver(send_form, REQ_END_LINE);
                break;
            default:
                form_driver(send_form, ch);
                break;
        }
    }
    //pos_form_cursor(send_form);
    unpost_form(send_form);
    free_form(send_form);
    free_field(field[0]);
    free_field(field[1]);
    free_field(field[2]);
    endwin();
    return 0;
}


