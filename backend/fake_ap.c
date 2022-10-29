#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10

struct Radio
{
    uint8_t version; /* set to 0 */
    uint8_t pad;
    uint16_t len;     /* entire length */
    uint32_t present; /* fields present */
};

void radio_init(struct Radio *rad)
{
    rad->version = 0x00;
    rad->pad = 0x00;
    rad->len = 0x0008;
    rad->present = 0x00;
}

struct BeaconFrame
{
    uint16_t FcF;
    uint16_t Dur;                  // Duration
    u_char mac_des[6];   // Destination address
    u_char mac_src[6];   // Source address
    u_char mac_bssid[6]; // BSS Id
    uint16_t FSnumber;
};
struct ssid_tag
{
    u_char tag_number;
    u_char ssid_len;
    u_char *ssid_name;
};

struct beaconPacket{
    struct Radio radio;
    struct BeaconFrame beacon;
    struct ssid_tag tag;
};

void Mac_(const char *arr, u_char mac_addr[6])
{
    int a;
    if (strlen(arr) != 17)
    {
        printf("Maclen error!!\n");
    }
    char cpyarr[18];
    memcpy(cpyarr, arr, 17);
    for (int i = 0; i < 6; i++) //입력Mac값의 콜론 제거
    {
        cpyarr[i * 3 + 2] = '\0';
        sscanf((const char *)&cpyarr[3 * i], "%x", &a);
        mac_addr[i] = (u_char)a;
    }
}

// void returnRMAC(){
//     char mac[15];
//     int a,b;
//     for(int i=0; i < 6; i++){
//         srand((unsigned)time(NULL));
//         a = rand()%16;
//         srand((unsigned)time(NULL));
//         b = rand()%16;
//         printf("%c\n\n",a);
//         mac[3*i] = (char)a;
//         mac[3*i+1] = (char)b;
//         mac[3*i+2] = ':';
//         // *(mac+3*i+1) = (char)b;
//         // *(mac+3*i+2) = *":";
//     }
//     mac[15] = '\0';
//     printf("%s",mac);
// }[
void randMac(u_char mac_addr[6]){
    for(int i=0;i<6;i++){
        srand((unsigned)time(NULL));
        mac_addr[i] = rand()%256;
    }
}

void tagInit(struct ssid_tag tag[9]){
    u_char buf[256];
    int len;
    printf("%p\n",&tag[1]);
    for(int i=0;i<MAX_SIZE;i++){
        tag[i].tag_number = 0x00;
        tag[i].ssid_len = 0x00;
        len = sprintf(buf,"test");
        len += sprintf(buf+len,"%d",i);
        tag[i].ssid_name = buf;
        // strcat(tag[i].ssid_name,"test");
        // strcat(tag[i].ssid_name,itoa(i,buf,10));
    }
}
// void socket();

void sendBeacon(u_char* Interface){
    int cnt=0;
    struct Radio radioTap;
    struct ssid_tag tag[9];
    radio_init(&radioTap);
    struct beaconPacket BP;
    BP.radio = radioTap;
    BP.beacon.FcF = 0x0080;
    BP.beacon.Dur = 0x0000;
    randMac(BP.beacon.mac_des);
    Mac_("ff:ff:ff:ff:ff:ff", BP.beacon.mac_src);
    randMac(BP.beacon.mac_bssid);
    BP.beacon.FSnumber = 0x0000;
    printf("%p\n",&tag[1]);
    tagInit(tag);
    // printf("%s",tag[0].ssid_name);
    // printf("%p\n",tag);
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_live(Interface, BUFSIZ, 1, 1000, errbuf);
    while(1){
        if(cnt > MAX_SIZE){
            cnt = 0;
        }
        BP.tag = tag[cnt++];
        
        // printf("%d\n",sizeof(BP));
        // printf("%s\n",BP.tag.ssid_name);
        // printf("%s\n",tag[0].ssid_name);
        // pcap_sendpacket(pcap, (char *)&BP, sizeof(BP) - 2);
    }
}
int main(int argc, char argv[]){
    unsigned char Interface = argv[1];
    sendBeacon(&Interface);
}