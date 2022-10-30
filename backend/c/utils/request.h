#pragma once
#include <deque>
#define PORT            1235
#define LOCAL_HOST      "127.0.0.1"
#define SSID_LEN        32
#define QUEUE_SIZE      10

using namespace std;
extern deque<char*> request_queue;

int sock_init(void);
void read_ssid_from_client(void);
