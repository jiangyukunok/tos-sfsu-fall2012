#ifndef _ETH_C
#define _ETH_C

#define INLINE

#include "nll.h"

#ifdef LINUX
	#include <stdio.h>
#endif

u_char_t host_mac[ETH_ADDR_LEN]={0xBC,0xAE,0x82,0x69,0xEB,0x28};

u_char_t eth_bcast[ETH_ADDR_LEN] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

void set_host_mac(u_char_t *mac)
	{
	  memcpy_tos(host_mac, mac,ETH_ADDR_LEN);
	}

u_char_t *get_host_mac()
	{
		return host_mac;
	}

BOOL is_ethernet_header(void *buffer,ETH ether)
{
	u_char_t *buff = (u_char_t *)(buffer);
	memcpy_tos(ether->dst ,buff,ETH_ADDR_LEN);
	memcpy_tos(ether->src , (buff + ETH_ADDR_LEN),ETH_ADDR_LEN);
	ether->type = *((u_int16_t *)(buff + 2*ETH_ADDR_LEN));
	return TRUE;
 }

u_int_t send_eth_packet(u_char_t *to, u_char_t *host, const void *data, u_int_t len, u_int16_t type,u_char_t *packet)
{
        int i;
		u_int_t length;
		//u_char_t *dta = (u_char_t *)data;

		length = MIN(len, ETH_MAX_TRANSFER_UNIT);
         //mac_addr = get_host_mac();

         memcpy_tos(packet, to, ETH_ADDR_LEN);
         memcpy_tos((packet + ETH_ADDR_LEN), host, ETH_ADDR_LEN);
         //memcpy_tos((packet + (2 * ETH_ADDR_LEN)), type, sizeof(u_int16_t));

         *((u_int16_t *)(packet + (2 * ETH_ADDR_LEN))) = htons_tos(type);

         // Copy the data into the packet
         memcpy_tos((packet + ETH_HEAD_LEN), data, len);

         //for (i=0; i<len; i++)
           //        printf("%02x:", dta[i]);
         //printf("\n");
         // Adjust the packet length including the size of the header
         length += ETH_HEAD_LEN;


         while (length < ETH_MIN_LEN)
                 packet[length++] = '\0';

         return length;
}

#endif
