#ifndef IP_H
#define IP_H

#include <stdint.h>
#include <netinet/in.h>

#ifndef __linux__
    #pragma(push, 1)
#endif
struct ip_hdr
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	uint8_t ip_hl:4;
	uint8_t ip_v:4;
#endif

#if __BYTE_ORDER == __BIG_ENDIAN
    uint8_t ip_v:4;
    uint8_t ip_hl:4;
#endif
    uint8_t ip_tos;
	uint16_t ip_len;
	uint16_t ip_id;
	uint16_t ip_off;
#define IP_RF 0x8000
#define IP_DF 0x4000
#define IP_MF 0x2000
#define IP_OFFMASK 0x1fff
	uint8_t  ip_ttl;
	uint8_t ip_p;
	uint16_t ip_sum;
	struct in_addr src_ip, dst_ip;
}
#ifndef __linux__
    ;
    #pragma(pop)
#else
__attribute__((__packed__));
#endif
#endif
