#include "game.h"
#include "MapMethods.h"
#include "tcpSocket.h"

int main()
{
	InitSocket();

	SOCKET server = CreateServerSocket();
	printf("中国象棋服务端已启动,等待客户端连接......\n");

	struct hostent* phostinfo = gethostbyname("");
	char* p = inet_ntoa(*((struct in_addr*)(*phostinfo->h_addr_list)));
	printf("本机IP地址为:%s\n", p);

	SOCKET client = accept(server, NULL, NULL);
	if (client == INVALID_SOCKET)
	{
		MY_SOCKET_ERROR("accept");
	}
	printf("客户端已连接成功,开始游戏吧!\n");

	LoadGridImage();
	InitGame();
	while (true)
	{
		char recvBuffer[10];
		char sendBuffer[10];

		int recvLen = recv(client, recvBuffer, 10, 0);
		if (recvLen < 0)
		{
			client = accept(server, NULL, NULL);
			if (client == SOCKET_ERROR)
			{
				MY_SOCKET_ERROR("accept");
				return 0;
			}
			continue;
		}
		printf("[RECEIVE]:%s\n", recvBuffer);
		InputInformationAndMoveChess(recvBuffer);



		std::string sendTempBuffer = SelectChessPiece();

		for (int i = 0; i < 4; i++)
			sendBuffer[i] = sendTempBuffer[i];
		sendBuffer[4] = '\0';

		std::cout << "[SEND:]" << sendBuffer << "\n";

		send(client, sendBuffer, 10, 0);
	}
	
	closesocket(client);
	closesocket(server);

	CloseSocket();
	return 0;
}