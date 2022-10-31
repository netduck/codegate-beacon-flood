#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <malloc.h>

#include <pthread.h>

#include <iostream>
#include <deque>

#include "request.h"
deque<char*> request_queue;

int sock_init(void)
{
        int                     server_sock;
        int                     client_sock;
        int                     option = 1;

        struct  sockaddr_in     server_addr;
        struct  sockaddr_in     client_addr;

        socklen_t               client_addr_size;

        server_sock = socket(PF_INET, SOCK_STREAM, 0);
        setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

        if(server_sock == -1)
        {
                fprintf(stdout, "Server : socket Error\n");
                exit(-1);
        }

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(LOCAL_HOST);
        server_addr.sin_port=htons(PORT);

        if(bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1)
        {
                fprintf(stdout, "Server : bind Error\n");
                exit(-1);
        }

        if(listen(server_sock, 1)==-1)
        {
                fprintf(stdout, "Server : listen Error\n");
                exit(-1);
        }

        client_addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
        if(client_sock == -1)
        {
                fprintf(stdout, "Server : accept Error\n");
                exit(-1);
        }

        close(server_sock);
        return client_sock;
}

void read_ssid_from_client(void)
{
        int                     client_sock;
        char*                   request;
        client_sock = sock_init();

        while(1)
        {
                request = (char*)calloc(SSID_LEN, sizeof(char));
                read(client_sock, request, SSID_LEN);

		if(strlen(request) == 0)
		{
			fprintf(stderr, "read_ssid_from_client() : Connection closed\n");
			close(client_sock);
			exit(-1);
		}

                if(request_queue.size()==QUEUE_SIZE)
                {
                        char* expired = request_queue.front();
                        request_queue.pop_front();
                        cout<<"Delete : "<<expired<<endl;
                        free(expired);
                }

                request_queue.push_back(request);
        }
}
