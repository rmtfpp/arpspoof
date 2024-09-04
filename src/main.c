#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "arpr_build.h"
#include "arpr_send.h"

int running = 1;

void sigint(int sig){
    sleep(2);
    printf("exiting now\n");
    running = 0;
}

int main(int argc, char *argv[]){

    signal(SIGINT, sigint);

    while(running){
        printf("%s | running...\n", argv[0]);
        sleep(1);
    }

    printf("exited the loop\n");

    return 0;
}
