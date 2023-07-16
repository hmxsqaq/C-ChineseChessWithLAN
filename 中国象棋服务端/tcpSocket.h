#pragma once

#include <stdbool.h>
#include <WinSock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

#define MY_SOCKET_ERROR(errorMsg) printf("%s Error, Code %d\n",errorMsg , WSAGetLastError());

bool InitSocket(void);
bool CloseSocket(void);
SOCKET CreateServerSocket(void);
SOCKET CreateClientSocket(const char* ip);