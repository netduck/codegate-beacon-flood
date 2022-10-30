#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10

#define MAC_ADDR_LEN	6
#define SSID_LEN	32
#define SSID_TAG_NUM	0

struct RadioTap
{
	uint8_t			version;
	uint8_t			pad;
	uint16_t		len;
	uint32_t		present;
} __attribute__((packed));

struct Dot11
{
	uint16_t		type;
	uint16_t		duration;
	u_char 			dest[MAC_ADDR_LEN];
	u_char 			src[MAC_ADDR_LEN];
	u_char			bssid[MAC_ADDR_LEN];
	uint16_t		fsNum;
} __attribute__((packed));

struct Dot11Management
{
	uint64_t 		timestamp;
	uint16_t 		interval;
	uint16_t		cap;
} __attribute__((packed));

struct SSIDElement
{
	u_char			tag_number;
	u_char			ssid_len;
	u_char			ssid_name[SSID_LEN];
} __attribute__((packed));


struct BeaconFrame
{
	struct RadioTap 	rt;
	struct Dot11		dot11;
	struct Dot11Management	dot11man;
	struct SSIDElement	ssid;
} __attribute__((packed));

void mac(u_char *mac_addr, const char *arr)
{
	int a;
	char cpyarr[18];

	if (strlen(arr) != 17)
	{
		printf("Maclen error!!\n");
	}

	memcpy(cpyarr, arr, 17);
	
	for (int i = 0; i < 6; i++) //입력Mac값의 콜론 제거
	{
		cpyarr[i * 3 + 2] = '\0';
		sscanf((const char *)&cpyarr[3 * i], "%x", &a);
		mac_addr[i] = (u_char)a;
	}
}

void randMac(u_char *mac_addr)
{
	for(int i=0;i<6;i++)
	{
		srand((unsigned)time(NULL));
		mac_addr[i] = rand()%256;
	}
}

void setSSID(struct BeaconFrame *bc, const char *ssid)
{
	bc->ssid.tag_number = SSID_TAG_NUM;
	bc->ssid.ssid_len = strlen(ssid);
	memcpy(bc->ssid.ssid_name, ssid, bc->ssid.ssid_len);
}

void initBeacon(struct BeaconFrame *bc, const char *ssid)
{
	memset(bc, 0, sizeof(struct BeaconFrame));
	
	/* RadioTap */
	bc->rt.len = 0x8;

	/* Dot11 */
	bc->dot11.type = 0x80;
	mac(bc->dot11.dest, "ff:ff:ff:ff:ff:ff");
	randMac(bc->dot11.src);
	memcpy(bc->dot11.bssid, bc->dot11.src, 6);

	/* Dot11Management */
	bc->dot11man.interval = 0x64;
	bc->dot11man.cap = 0x11;

	/* SSID Element */
	setSSID(bc, ssid);
}


void sendBeacon(u_char* Interface)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	struct BeaconFrame bc;

	initBeacon(&bc, "saddsafsadfdsafdsaf");

	pcap_t *pcap = pcap_open_live(Interface, BUFSIZ, 1, 1000, errbuf);
	if(pcap == NULL)
	{
	    fprintf(stderr, "pcap_open_live Error : %s\n",errbuf);
	    exit(-1);
	}

	while(1)
	{		
	    for(int i=0; i<20; i++)
	    {
		    if(pcap_sendpacket(pcap, (char*)&bc, sizeof(struct BeaconFrame)-SSID_LEN+bc.ssid.ssid_len)!=0)
		    {
			    fprintf(stderr, "Error\n");
			    exit(-1);
		    }
	    }
	}
}
int main(int argc, char *argv[]){
    unsigned char *Interface = argv[1];
    sendBeacon(Interface);
}
