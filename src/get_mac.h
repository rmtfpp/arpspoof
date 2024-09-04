#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>

char *get_mac_address(const char *ip_address);

char* interface_mac_address(const char *interface);