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

void startServer(const char* iface)
{
	pthread_t connThread, sendThread;
	void** ret;
	
	if(pthread_create(&connThread, NULL, connector, NULL) <0)
	{
		perror("connThread Fail");
		exit(-1);
	}

	if(pthread_create(&sendThread, NULL, sender, (void*)iface) <0)
	{
		perror("sendThread Fail");
		exit(-1);
	}

	pthread_join(connThread, ret);
}


int main(int argc, char *argv[])
{
	setvbuf(stdout, 0, 2, 0);

	if(argc!=2)
	{
		fprintf(stderr, "usage : ./backend <iface>\n");
		exit(-1);
	}

	startServer(argv[1]);
	return 0;
}
