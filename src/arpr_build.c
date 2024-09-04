#include "arpr_build.h"

void arpr_build(const char *ip_dest, const char *mac_dest, const char *ip_src, const char *mac_src, unsigned char *packet) {
    struct ether_header *eth_header = (struct ether_header *) packet;
    struct ether_arp *arp_header = (struct ether_arp *) (packet + sizeof(struct ether_header));


    //ethernet
    sscanf(mac_dest, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &eth_header->ether_dhost[0], &eth_header->ether_dhost[1], &eth_header->ether_dhost[2],
           &eth_header->ether_dhost[3], &eth_header->ether_dhost[4], &eth_header->ether_dhost[5]);
    sscanf(mac_src, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &eth_header->ether_shost[0], &eth_header->ether_shost[1], &eth_header->ether_shost[2],
           &eth_header->ether_shost[3], &eth_header->ether_shost[4], &eth_header->ether_shost[5]);
    eth_header->ether_type = htons(ETHERTYPE_ARP);


    //arp
    arp_header->ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
    arp_header->ea_hdr.ar_pro = htons(ETHERTYPE_IP);
    arp_header->ea_hdr.ar_hln = ETHER_ADDR_LEN;
    arp_header->ea_hdr.ar_pln = sizeof(in_addr_t);
    arp_header->ea_hdr.ar_op = htons(ARPOP_REPLY);

    sscanf(mac_src, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &arp_header->arp_sha[0], &arp_header->arp_sha[1], &arp_header->arp_sha[2],
           &arp_header->arp_sha[3], &arp_header->arp_sha[4], &arp_header->arp_sha[5]);
    inet_pton(AF_INET, ip_src, arp_header->arp_spa);
    sscanf(mac_dest, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &arp_header->arp_tha[0], &arp_header->arp_tha[1], &arp_header->arp_tha[2],
           &arp_header->arp_tha[3], &arp_header->arp_tha[4], &arp_header->arp_tha[5]);
    inet_pton(AF_INET, ip_dest, arp_header->arp_tpa);

    printf("%s : %s || %s : %s", ip_dest, mac_dest, ip_src, mac_src);

}
