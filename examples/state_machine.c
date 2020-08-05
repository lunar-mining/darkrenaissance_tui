#include <iostream>

enum class parser_state
{
    start = 0,
    n_found,
    i_found,
    c_found,
    success,
    error
};

class nice_parser
{
public:
    nice_parser()
    {
    }

    void process(char letter)
    {
        switch (state_)
        {
            case parser_state::start:
                if (letter == 'n')
                    state_ = parser_state::n_found;
                else
                    state_ = parser_state::error;
                break;
            case parser_state::n_found:
                if (letter == 'i')
                    state_ = parser_state::i_found;
                else
                    state_ = parser_state::error;
                break;
            case parser_state::i_found:
                if (letter == 'c')
                    state_ = parser_state::c_found;
                else
                    state_ = parser_state::error;
                break;
            case parser_state::c_found:
                if (letter == 'e')
                    state_ = parser_state::success;
                else
                    state_ = parser_state::error;
                break;
        }
    }

    parser_state state()
    {
        return state_;
    }

private:
    parser_state state_ = parser_state::start;
};

int main()
{
    nice_parser nice;
    for (auto c: "nice")
    {
        std::cout << c << std::endl;
        nice.process(c);
        if (nice.state() == parser_state::success)
        {
            std::cout << "success!" << std::endl;
            break;
        }
        else if (nice.state() == parser_state::error)
        {
            std::cout << "error!" << std::endl;
            break;
        }
    }
    return 0;
}
