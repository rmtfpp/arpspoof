#include "arpr_send.h"

void arpr_send(unsigned char *packet, const char *interface) {
    int sockfd;
    struct ifreq if_idx;
    struct sockaddr_ll socket_address;

    // raw socket
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // interface index
    memset(&if_idx, 0, sizeof(struct ifreq));
    strncpy(if_idx.ifr_name, interface, IFNAMSIZ-1);
    if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0) {
        perror("SIOCGIFINDEX");
        exit(EXIT_FAILURE);
    }

    // bind
    memset(&socket_address, 0, sizeof(struct sockaddr_ll));
    socket_address.sll_ifindex = if_idx.ifr_ifindex;
    socket_address.sll_halen = ETH_ALEN;
    memcpy(socket_address.sll_addr, packet + 6, 6);

    // send
    if (sendto(sockfd, packet, sizeof(struct ether_header) + sizeof(struct ether_arp), 0, 
               (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }

    close(sockfd);
}
