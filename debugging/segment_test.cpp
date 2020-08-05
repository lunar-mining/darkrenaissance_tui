#include <signal.h> 
#include <stdio.h>
#include <iostream>

void signal_handler(int signal_num)
{
    std::cout << "helooh\n";
    exit(signal_num);
}

int main() 
{ 
   char *str;  

   signal(SIGSEGV, signal_handler);
   /* Stored in read only part of data segment */
   str = "GfG";      
  
   /* Problem:  trying to modify read only memory */
   *(str+1) = 'n';  
   return 0; 
} 
