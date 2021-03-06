#ifndef MYPCAP_H
#define MYPCAP_H
#include <stdint.h>
#include <netinet/in.h>
#include <pcap.h>

struct myether{
    unsigned char dst_addr[6];
    unsigned char src_addr[6];
    unsigned short type_id;
};

struct myip{
    /*by byte order*/
#if __BYTE_ORDER__ == __LITTLE_ENDIAN__
    unsigned int hdr_len:4;
    unsigned int hdr_v:4;
#endif
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    unsigned int hdr_v:4;
    unsigned int hdr_len:4;
#endif
    uint8_t tos; /*type of services*/
    unsigned short len; /*ip header length*/
    unsigned short id; /*identification*/
    unsigned short offset;

    uint8_t ttl; /*time to live*/
    uint8_t protocol;
    unsigned short chksum;
    struct in_addr src_ip, dst_ip;
};

struct mytcp{
    uint16_t dst_port;
    uint16_t src_port;
    unsigned long seq_num; /*sequence number*/
    unsigned long ack_num; /*acknowledgment number*/
#if __BYTE_ORDER__ == __LITTLE_ENDIAN__
    uint8_t reverse:4;
    uint8_t offset:4;
#endif
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint8_t offset:4; /*data offset*/
    uint8_t reverse:4;
#endif
    uint8_t flags; /* C E U A P R S F */
#  define TH_FIN    0x01
#  define TH_SYN    0x02
#  define TH_RST    0x04
#  define TH_PUSH   0x08
#  define TH_ACK    0x10
#  define TH_URG    0x20
    unsigned short window; /*window*/
    unsigned short chksum; /*checksum*/
    unsigned short ptr; /*urgent pointer*/
};

void print_ether(struct myether*);
void print_ip(struct myip*);
void print_tcp(struct mytcp*);
void display_packet(const u_char *packet);

#endif // MYPCAP_H
