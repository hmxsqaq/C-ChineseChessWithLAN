#include "game.h"
#include "MapMethods.h"
#include "tcpSocket.h"

int main()
{
	InitSocket();
	std::cout << "�й�����ͻ���������" << std::endl;

	SOCKET server;

	while (true)
	{
		char input[50];
		printf("����������IP��ַ:");
		scanf("%s", input);
		server = CreateClientSocket(input);
		if (server != INVALID_SOCKET)
			break;
	}

	std::cout << "���ӳɹ�,��ʼ��Ϸ��!" << "\n";

	LoadGridImage();
	InitGame();
	while (true)
	{
		char sendBuffer[10];
		char recvBuffer[10];

		std::string sendTempBuffer = SelectChessPiece();

		for (int i = 0; i < 4; i++)
			sendBuffer[i] = sendTempBuffer[i];
		sendBuffer[4] = '\0';

		std::cout << "[SEND:]" << sendBuffer << "\n";

		int sendLen = send(server, sendBuffer, 10, 0);

		if (sendLen < 0)
		{
			MY_SOCKET_ERROR("send")
		}

		recv(server, recvBuffer, 10, 0);
		printf("[RECEIVE]:%s\n", recvBuffer);
		InputInformationAndMoveChess(recvBuffer);
	}
	return 0;
}