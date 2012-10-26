#ifndef _NLL_H
#define _NLL_H

#ifndef INLINE
	# define INLINE extern inline
#endif

//! Little endian architecture.
#define __LITTLE_ENDIAN__       1234
//! Big endian architecture.
#define __BIG_ENDIAN__          4321
//! The current architecture.
//#define __BYTE_ORDER__          __LITTLE_ENDIAN__


INLINE unsigned int ntohs_tos(unsigned short n){
	#if __BYTE_ORDER__==__LITTLE_ENDIAN__
		return (((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8));
	#else
		return n;
	#endif
}

INLINE unsigned int ntohl_tos(unsigned int n){
	#if __BYTE_ORDER__==__LITTLE_ENDIAN__
		return ((n & 0xFF000000) >> 24) | ((n & 0x00FF0000) >> 8) | ((n & 0x0000FF00) << 8) |((n & 0x000000FF) << 24) ;
	#else
		return n;
	#endif

}

INLINE unsigned short htons_tos(unsigned short n){
#if __BYTE_ORDER__==__LITTLE_ENDIAN__
		return (((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8));
	#else
		return n;
	#endif
}

INLINE unsigned int htonl_tos(unsigned int n){
	#if __BYTE_ORDER__==__LITTLE_ENDIAN__
		return ((n & 0xFF000000) >> 24) | ((n & 0x00FF0000) >> 8) | ((n & 0x0000FF00) << 8) |((n & 0x000000FF) << 24) ;
	#else
		return n;
	#endif

}



#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define MAX(a, b)       ((a) > (b) ? (a) : (b))


#define TRUE	1
#define FALSE	0		


#ifndef NULL
#define NULL	((void *) 0)
#endif


typedef int BOOL;

typedef unsigned char           	byte;
typedef unsigned short          	word;
typedef signed char             	char_t;
typedef unsigned char           	u_char_t;
typedef unsigned char 		   	u_int8_t;
typedef signed short int        	int16_t;
typedef unsigned short int      	u_int16_t;
typedef signed int              	int_t;
typedef unsigned int            	u_int_t;
typedef unsigned int 		 		u_int32_t;


INLINE void memcpy_tos(void *dst,void *src,u_int_t len)
{
  if(dst == NULL || src==NULL)
    return;
   while(len--)
     *((u_char_t *)(dst++))= *((u_char_t *)(src++));
}


INLINE BOOL memcmp_tos(void *pt1, void *pt2,u_int_t size)
{
  u_char_t *p1 = (u_char_t *)pt1;
  u_char_t *p2 = (u_char_t *)pt2;

  u_int_t i;
  for(i=0;i<size;i++)
    if(*(p1 + i) != *(p2 +i))
      return FALSE;
  return TRUE;

}

INLINE BOOL is_digit(u_char_t c)
{
	return (c >= 0x30 && c <= 0x39);
}


INLINE BOOL is_ascii(u_char_t c)
{
	return (c <= 0x7f);
}

INLINE BOOL is_space(u_char_t c)
{
	return (c == 0x20);
}


/*===================== eth includes===========================*/

#define		ETHERTYPE_IP            0x0800		/* IP */
#define		ETHERTYPE_ARP           0x0806		/* Address resolution */

#define ETH_ADDR_LEN               6
 
#define ETH_HEAD_LEN           	   	14

#define ETH_MIN_LEN               	64

#define ETH_MAX_LEN             	1514

#define ETH_MAX_TRANSFER_UNIT   (ETH_MAX_LEN - ETH_HEAD_LEN)
 

 
struct _ethernet;
typedef struct _ethernet* ETH;
 
typedef struct _ethernet
 {

         u_char_t  dst[ETH_ADDR_LEN];
         u_char_t  src[ETH_ADDR_LEN];
         u_int16_t type;
 }ethernet_t ;

 
BOOL is_ethernet_header(void *buffer , ETH ether);
void print_ethernet_header(ETH ether,u_int_t len);



/*************************** ip includes ****************************************/

#define IP_V4                   	4
 
#define IP_LEN 		  		     	4
 
 #define IP_FRAME_LEN            	65535
 
 #define IP_HEAD_MIN_LEN         	20
 
 #define IP_DEFAULT_TTL          	64

 #define IP_PROTO_TCP            	6

 #define IP_PROTO_UDP            	0x11
 

 #define IP_TOS_MIN_DELAY        	0x10

 #define IP_TOS_MAX_THRU         	0x08

 #define IP_TOS_MAX_RELY         	0x04

 #define IP_TOS_MIN_COST         	0x02
 

 #define IP_FLAG_MF              	0x2000

 #define IP_FLAG_DF              	0x4000

 #define IP_FLAG_SERVED          	0x8000

 #define IP_FLAG_MASK            	0x1FFF


 #define INADDR_BROADCAST        IP_ADDRESS(255, 255, 255, 255)

 struct _ip;
 typedef struct _ip* IP;
 
 typedef struct _ip
 {
#if __BYTE_ORDER__==__LITTLE_ENDIAN__

         u_int8_t ip_hdr_len:4;   
         u_int8_t ip_version:4;  
 #else
         u_int8_t ip_version:4;   
         u_int8_t ip_hdr_len:4;   
 #endif
         
         u_int8_t  ip_tos;
         u_int16_t ip_len;
         u_int16_t ip_id;
       
         u_int16_t ip_offset;
        
         u_int8_t ip_ttl;
        
         u_int8_t ip_proto;
        
         u_int16_t ip_chksum;

         u_char_t ip_src[IP_LEN];
         u_char_t ip_dst[IP_LEN];
 
 }ip_t;
 


 u_int16_t ip_checksum(IP ip , u_int_t hdr_len);
 u_int16_t ip_checksum_v2(IP ip , u_int_t hdr_len);


 BOOL is_ip_packet(void *buffer,u_int_t len , IP ip_pkt);
 int inet_aton_tos(u_char_t *dot_ip, u_char_t *net_ip);
 void print_ip_header(IP ip_pkt, u_int_t packet_len);


 /*********************** arp includes ************************/

 #define ARPHRD_ETHER 1

 #define ARP_REQUEST 1
 #define ARP_REPLY 	  2

 struct _arp;
 typedef struct _arp* ARP;

 typedef struct _arp
 {

          u_int16_t arp_hard_type;
          u_int16_t arp_proto_type;
          u_char_t  arp_hard_size;
          u_char_t  arp_proto_size;
          u_int16_t arp_op;
          u_char_t  arp_eth_source[ETH_ADDR_LEN];
          u_char_t  arp_ip_source[IP_LEN];
          u_char_t  arp_eth_dest[ETH_ADDR_LEN];
          u_char_t  arp_ip_dest[IP_LEN];
  }arp_t;


 BOOL is_arp_request(void *buffer, u_int_t len,ARP arp_packet);
 BOOL is_arp_reply(void *buffer, u_int_t len,ARP arp_packet);
 void arp_add_cache(u_char_t *ip, u_char_t *mac);
 BOOL arp_ip_to_mac(u_char_t *eth_addr, u_char_t *ip_addr);
 u_int_t create_arp_packet(u_char_t *ip_to, u_char_t *eth_to,u_char_t *host_ip, \
		 u_char_t *host_mac,u_int16_t arp_op , ARP packet);
 void print_arp(ARP pkt, u_int_t len);

 /*************************** UDP includes *********************/
 
 struct _udp;
 typedef struct _udp* UDP;
  
 typedef struct _udp
  {
         
         u_int16_t udp_src_port;
         u_int16_t udp_dst_port;
         u_int16_t udp_len;
         u_int16_t udp_checksum;
         u_char_t *payload;
  }udp_t ;

  struct _pseudo_ip;
  typedef struct _pseudo_ip* PSEUDOIP;

  typedef struct _pseudo_ip
   {
         u_char_t ip_src[IP_LEN];
 	     u_char_t ip_dst[IP_LEN];
   }pseudo_ip_t ;

  
 u_int16_t udp_checksum(UDP ud, u_int_t len, PSEUDOIP sip);
 void set_pseudo_ip_header(IP ip,PSEUDOIP sip);
 BOOL is_udp_packet(void *buffer,u_int_t len, UDP packet);
 void print_udp_header(UDP ud,u_int_t len,PSEUDOIP sip);
 void print_udp_data(UDP ud,IP ip,u_int_t len);

#endif
