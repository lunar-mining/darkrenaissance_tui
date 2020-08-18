#include <iostream>
#include <cassert>

popup::popup(sendw* sw)
{
    sw_ = sw;
}

void popup::foo()
{
    std::cout << "Hello!" << std::endl;
    // See 'enforce logic' with assert
    // Enforce that sw_ is not-null
    assert(sw_);

    // In some function in the popup class
    // Now we want to call some functions on sendw / get some data from it
    ///////////////////////////
    std::cout << "popup::foo(): Name is " << sw_->name << std::endl;
    // NOTE: x->y is short from (*x).y
    ///////////////////////////
}
