#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

#include "beacon.h"

#define MAX_SIZE 10

void sendBeacon(u_char* Interface)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	struct BeaconFrame bc;

	initBeacon(&bc, "배고픈 민준이");

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
		    if(pcap_sendpacket(pcap, (char*)&bc, calcBeaconSize(&bc))!=0)
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
