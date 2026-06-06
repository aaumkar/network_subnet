#pragma once
#include <stdint.h>

/**
 * @brief get uint32 version of the IP address 
 * 
 * @param ip array size 4 of uint8
 * @return uint32_t 
 */
static inline uint32_t ip_to_u32(const uint8_t ip[4]) {
    return ((uint32_t)ip[0] << 24) | ((uint32_t)ip[1] << 16) | ((uint32_t)ip[2] << 8) |
           ((uint32_t)ip[3]);
}

/**
 * @brief get array size 4 ip from uint32 ip number
 * 
 * @param val uint32 value of IP
 * @param ip 
 */
static inline void u32_to_ip(uint32_t val, uint32_t ip[4]) {
    ip[0] = val >> 24 & 0xFF;
    ip[1] = val >> 16 & 0xFF;
    ip[2] = val >> 8 & 0xFF;
    ip[3] = val & 0xFF;
}

/**
 * @brief convert CIDR value to 32 bit IP subnet mask
 * 
 * @param cidr 
 * @return uint32_t 
 */
static inline uint32_t cidr_to_mask(short cidr) {
    if(cidr == 0) return 0;
    return ~((uint32_t)0) << (32 - cidr);
}

/**
 * @brief get subnet detials from IP and CIDR.
 * This function will also calculate edge case of the /31, /32 subnets
 * 
 * @param ip 
 * @param cidr 
 * @param out_network 
 * @param out_broadcast 
 * @param out_host_count 
 */
void subnet_calculate(
    const uint8_t ip[4],
    uint8_t cidr,
    uint32_t* out_network, // network address
    uint32_t* out_broadcast, // broadcast address
    uint32_t* out_host_count // usable hosts (broadcast - network - 1)
) {
    uint32_t mask = cidr_to_mask(cidr);
    uint32_t ip_number = ip_to_u32(ip);
    *out_network = mask & ip_number;

    *out_host_count = *out_broadcast - ip_number;
    switch(cidr) {
    case 31:
        *out_broadcast = *out_network + 1;
        *out_host_count = 2;
        break;
    case 32:
        *out_broadcast = *out_network;
        *out_host_count = 0;
        break;
    default:
        *out_broadcast = ip_number | (~mask);
        *out_host_count = *out_host_count - 1;
    }
}
