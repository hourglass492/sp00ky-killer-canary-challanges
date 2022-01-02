#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//python3 -c "print('A' * 400)" | ./level1

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("Caught segfault at address %p", si->si_addr);
    printf("The signal is %d ", signal);
    printf("the flag is:");

    FILE *fptr;

    char c;

    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }


    exit(0);
}

int main(void)
{
    
    int string[200];
    struct sigaction sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags   = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
    

    puts("Input please");
    /* Cause a seg fault */
    gets(string);

    puts("recived: ");
    puts(string);

    puts("thank you :)");

    printf("Return to %p", __builtin_return_address(0));

    return 0;
}