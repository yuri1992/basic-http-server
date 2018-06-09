#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#ifndef _SOCKET_MANAGER_
#define _SOCKET_MANAGER_


#include <iostream>
using namespace std;
// Don't forget to include "Ws2_32.lib" in the library list.
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include "HttpServer.h"

bool addSocket(SOCKET id, int what);
void removeSocket(int index);
void acceptConnection(int index);
void receiveMessage(int index);
void sendMessage(int index);


struct SocketState
{
	SOCKET id;			// Socket handle
	int	status;			// Sending?
	HttpRequest* request;	// Sending sub-type
	time_t lastReqTime;	// Time of Last Pack
	char *buffer;
	int len;
};

#endif