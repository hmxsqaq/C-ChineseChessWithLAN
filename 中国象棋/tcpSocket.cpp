#include "tcpSocket.h"

bool InitSocket(void)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		MY_SOCKET_ERROR("WSAStartup");
		return false;
	}
	return true;
}

bool CloseSocket(void)
{
	if (WSACleanup() != 0)
	{
		MY_SOCKET_ERROR("WSACleanup");
		return false;
	}
	return true;
}

SOCKET CreateServerSocket(void)
{
	SOCKET newSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (newSocket == INVALID_SOCKET)
	{
		MY_SOCKET_ERROR("socket");
		return INVALID_SOCKET;
	}

	struct sockaddr_in socketAddress;
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_port = htons(8888);
	socketAddress.sin_addr.S_un.S_addr = ADDR_ANY;

	if (bind(newSocket, (struct sockaddr*)&socketAddress, sizeof socketAddress) == SOCKET_ERROR)
	{
		MY_SOCKET_ERROR("bind");
		return INVALID_SOCKET;
	}

	listen(newSocket, 10);
	return newSocket;
}

SOCKET CreateClientSocket(const char* ip)
{
	SOCKET newSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (newSocket == INVALID_SOCKET)
	{
		MY_SOCKET_ERROR("socket");
		return INVALID_SOCKET;
	}

	struct sockaddr_in socketAddress;
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_port = htons(8888);
	socketAddress.sin_addr.S_un.S_addr = inet_addr(ip);

	if (connect(newSocket, (sockaddr*)&socketAddress, sizeof socketAddress) == INVALID_SOCKET)
	{
		MY_SOCKET_ERROR("connect");
		return INVALID_SOCKET;
	}

	return newSocket;
}
