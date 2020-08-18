void process_input()
{
    while (true)
    {
        input_event* event = get_event();
        if (!event)
            return;
        switch (event->type())
        {
            case input_event_commands::key_press_up:
                // ...
                break;

            case input_event_commands::mouse_move:
                auto (x, y) = event->get_mouse_xy();
                // ...
                break;
        }
    }
}

int main()
{
    while (true)
    {
        process_input();
        update();
        render();
    }
}
