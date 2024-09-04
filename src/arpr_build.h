#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>

void arpr_build(const char *ip_dest, const char *mac_dest, const char *ip_src, const char *mac_src, unsigned char *packet);