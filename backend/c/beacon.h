#pragma once
#include <pcap.h>
#define MAC_ADDR_LEN    6
#define SSID_LEN        32
#define SSID_TAG_NUM    0

struct RadioTap
{
        uint8_t                 version;
        uint8_t                 pad;
        uint16_t                len;
        uint32_t                present;
} __attribute__((packed));

struct Dot11
{
        uint16_t                type;
        uint16_t                duration;
        u_char                  dest[MAC_ADDR_LEN];
        u_char                  src[MAC_ADDR_LEN];
        u_char                  bssid[MAC_ADDR_LEN];
        uint16_t                fsNum;
} __attribute__((packed));

struct Dot11Management
{
        uint64_t                timestamp;
        uint16_t                interval;
        uint16_t                cap;
} __attribute__((packed));

struct SSIDElement
{
        u_char                  tag_number;
        u_char                  ssid_len;
        u_char                  ssid_name[SSID_LEN];
} __attribute__((packed));


struct BeaconFrame
{
        struct RadioTap         rt;
        struct Dot11            dot11;
        struct Dot11Management  dot11man;
        struct SSIDElement      ssid;
} __attribute__((packed));

void mac(u_char *mac_addr, const char *arr);
void randMac(u_char *mac_addr);
void setSSID(struct BeaconFrame *bc, const char *ssid);
void initBeacon(struct BeaconFrame *bc, const char *ssid);
unsigned int calcBeaconSize(struct BeaconFrame *bc);


