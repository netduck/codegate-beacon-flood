#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "utils/sender.h"
#include "utils/request.h"

void* connector(void *args)
{
	read_ssid_from_client();
	return NULL;
}

void* sender(void *iface)
{
	send_beacon((const char*)iface);
	return NULL;
}

void startServer(void)
{
	pthread_t connThread, sendThread;
	void** ret;
	
	if(pthread_create(&connThread, NULL, connector, NULL) <0)
	{
		perror("connThread Fail");
		exit(-1);
	}

	if(pthread_create(&sendThread, NULL, sender, (void*)"mon0") <0)
	{
		perror("sendThread Fail");
		exit(-1);
	}

	pthread_join(connThread, ret);
}


int main(int argc, char *argv[]){
    //unsigned char *Interface = argv[1];
    //sendBeacon(Interface);
    startServer();

    return 0;
}
