#include "get_mac.h"

// $ arp -a 10.0.1.1
// pfSense.mylocal (10.0.1.1) at ##:##:##:##:##:## [ether] on eth0

char *get_mac_address(const char *ip_address){
    char command[128];
    snprintf(command, sizeof(command), "arp -a %s", ip_address);

    FILE *fp = popen(command, "r"); //open command pipe
    if (fp == NULL) {
        perror("error encountered while resolving MAC addresses");
    }

    char line[256];
    while(fgets(line, sizeof(line), fp) != NULL){ // while there are lines in file
        
        if(strstr(line, ip_address) != NULL){ // if in line theres the ip
            
            char *mac_start = strstr(line, ":") - 2;
            char *mac_end = strstr(mac_start, " ");
            short len = mac_end - mac_start;

            char *mac = (char *)malloc(len + 1);
            strncpy(mac, mac_start, len);
            mac[len] = '\0';

            return mac;
        }
        
    }
    char error[64];
    snprintf(error, sizeof(error), "no MAC address found for %s", ip_address);
    perror(error);
    return "";
}