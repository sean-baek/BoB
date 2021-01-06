#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdint.h>

#ifndef __linux__
    #pragma(push,1)
#endif
struct ethernet_hdr
{
    uint8_t ether_dhost[6];
	uint8_t ether_shost[6];
	uint16_t ether_type;
}
#ifndef __linux__
    ;
    #pragma pack(pop)
#else
__attribute__((__packed__));
#endif
#endif
