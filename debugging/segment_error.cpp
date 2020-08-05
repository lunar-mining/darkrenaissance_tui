#include <signal.h>
#include <stdio.h>

// first catch stack error with signal
// then print hello

void my_signal_handler(int sig)
{
    write(STDERR_FILENO, "SEGFAULT!\n", 10); // write to file
    signal(SIGSEGV, my_signal_handler); // reset the signal handler for SIGSEGV
    abort();
}

int main()
{
   signal(SIGSEGV, my_signal_handler); // initial set of signal handler
   /* do stuff here  */
   signal(SIGSEGV, SIG_DFL);  // restore default behavior

}
