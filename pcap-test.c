#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pcap.h>

#include "ethernet.h"
#include "ip.h"
#include "tcp.h"

#define SIZE_ETHERNET 14
#define SIZE 1024

void print_line()
{
    printf("==========================================================\n");
}

void usage()
{
    printf("syntax: pcap-test <interface>\n");
    printf("sample: pcap_test wlan0\n");
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        usage();
        return -1;
    }

    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    char s_ip[SIZE], d_ip[SIZE];
    int i;

    struct ethernet_hdr *ethernet;
	struct ip_hdr *ip;
	struct tcp_hdr *tcp;
	const char *payload;

	uint32_t size_ip;
	uint32_t size_tcp;


    if((handle = pcap_open_live(argv[1], BUFSIZ, 1, 1000, errbuf)) == NULL)
    {
        fprintf(stderr, "%s can't be opend\n", argv[1]);
        return 1;
    }

    while(1)
    {
        struct pcap_pkthdr *header;
        const u_char *packet;
        int res = pcap_next_ex(handle, &header, &packet);
        if(res == 0) continue;
        if(res == -1 || res == -2)
        {
            printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(handle));
            break;
        }

        ethernet = (struct ethernet_hdr*)(packet);
	    ip = (struct ip_hdr*)(packet + SIZE_ETHERNET);
	    size_ip = ip->ip_hl << 2;
	    if (size_ip < 20)
        {
		    printf("   * Invalid IP header length: %u bytes\n", size_ip);
		    return 1;
	    }
	    
        tcp = (struct tcp_hdr*)(packet + SIZE_ETHERNET + size_ip);
	    size_tcp = tcp->th_off << 2;
	    if (size_tcp < 20)
        {
		    printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		    return 1;
    	}
	    
        payload = (uint8_t *)(packet + SIZE_ETHERNET + size_ip + size_tcp);    
        int data_len = ntohs(ip->ip_len) - size_tcp - size_ip;

        unsigned char *dmac = ethernet->ether_dhost;
        unsigned char *smac = ethernet->ether_shost;
    
        strcpy(s_ip, inet_ntoa(ip->src_ip));
        strcpy(d_ip, inet_ntoa(ip->dst_ip));

        printf("%02x:%02x:%02x:%02x:%02x:%02x -> %02x:%02x:%02x:%2x:%02x:%02x, %s:%d -> %s:%d\n",
            smac[0], smac[1], smac[2], smac[3], smac[4], smac[5],
            dmac[0], dmac[1], dmac[2], dmac[3], dmac[4], dmac[5],
            s_ip, ntohs(tcp->th_sport), d_ip, ntohs(tcp->th_dport));
        
        int cut = (data_len > 16) ? 16:data_len;
        for(i=0; i<cut; i+=1)
        {
           printf("%02x|", payload[i]);
        }
        printf("\n");
        print_line();
    }

    pcap_close(handle);
    return 0;
}
