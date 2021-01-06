#ifndef TCP_H
#define TCP_H

#include <stdint.h>

#ifndef __linux__
    #pragma(push, 1)
#endif
struct tcp_hdr
{
    uint16_t th_sport;
    uint16_t th_dport;
    uint32_t th_seq;
    uint32_t th_ack;
    uint8_t th_x2:4;
    uint8_t th_off:4;
    uint8_t th_flags;
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_ECE 0x40
#define TH_CWR 0x80
    uint16_t th_win;
    uint16_t th_sum;
    uint16_t th_urp;
}
#ifndef __linux__
    ;
    #pragma(pop)
#else
__attribute__((__packed__));
#endif
#endif
