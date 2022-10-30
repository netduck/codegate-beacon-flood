#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "beacon.h"

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

unsigned int calcBeaconSize(struct BeaconFrame *bc)
{
        return sizeof(struct BeaconFrame)-SSID_LEN+bc->ssid.ssid_len;
}
