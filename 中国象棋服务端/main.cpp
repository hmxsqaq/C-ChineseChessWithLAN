#include "game.h"
#include "MapMethods.h"
#include "tcpSocket.h"

int main()
{
	InitSocket();

	SOCKET server = CreateServerSocket();
	printf("�й���������������,�ȴ��ͻ�������......\n");

	struct hostent* phostinfo = gethostbyname("");
	char* p = inet_ntoa(*((struct in_addr*)(*phostinfo->h_addr_list)));
	printf("����IP��ַΪ:%s\n", p);

	SOCKET client = accept(server, NULL, NULL);
	if (client == INVALID_SOCKET)
	{
		MY_SOCKET_ERROR("accept");
	}
	printf("�ͻ��������ӳɹ�,��ʼ��Ϸ��!\n");

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