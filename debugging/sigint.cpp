#include <stdio.h> 
#include <signal.h> 
#include <iostream>

void handle_sigint(int sig)
{
    std::cout << "Interrupt signal received.\n";
}

int main() 
{ 
    signal(SIGINT, handle_sigint); 
    while(1) ;
    return 0; 
} 
