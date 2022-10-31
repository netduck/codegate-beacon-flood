#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

#include "beacon.h"
#include "request.h"
#include "sender.h"

void send_beacon(const char* iface)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	struct BeaconFrame bc;

	initBeacon(&bc, "");

	pcap_t *pcap = pcap_open_live(iface, BUFSIZ, 1, 1000, errbuf);

	if(pcap == NULL)
	{
		fprintf(stderr, "pcap_open_live Error : %s\n", errbuf);
		exit(-1);
	}

	while(1)
	{
		if(!request_queue.empty())
		{
			for(int i=0; i<request_queue.size(); i++)
			{
				//randMac(bc.dot11.src); 
				//setSSID(&bc, request_queue[i]); 
				initBeacon(&bc, request_queue[i]);
				for(int j=0; j<20; j++)
				{
					if(pcap_sendpacket(pcap, (const u_char*)&bc, calcBeaconSize(&bc))!=0)
					{
						fprintf(stderr, "send_beacon : Error\n");
						exit(-1);
					}
				}

			}
		}
	}
}

