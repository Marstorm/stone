
#include "realised/winNet.h"


WORD transport_net::wVersionRequested;
WSADATA transport_net::wsaData;

#include <iostream>

int transport_net::read(string & data)
{

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	SOCKET sockConn = accept(m_sockSrv, (SOCKADDR*)&addrClient, &len);
	//std::cout << "recv from:" << inet_ntoa( addrClient.sin_addr) << std::endl;
	char recvBuf[50];
	recv(sockConn, recvBuf, 50, 0);
	data = recvBuf;
	closesocket(sockConn);
	return 0;


}

int transport_net::write(const string &  data)//this will not block,
{

	SOCKADDR_IN addrSrv = m_addr;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(m_port);

	int err;

	SOCKET  t_sockSrv;
	while (true)
	{
		t_sockSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (t_sockSrv == INVALID_SOCKET)
			wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
		err = connect(t_sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
		if (err == SOCKET_ERROR) {
			closesocket(t_sockSrv);
		}
		else
		{
			break;
		}
	}


	if (send(t_sockSrv, data.c_str(), 50, MSG_DONTROUTE) != WSANOTINITIALISED)
	{
		err = WSAGetLastError();
	}
	else
		return 0;

	return 0;
}

int transport_net::try_write(const string &  data)
{
	SOCKADDR_IN addrSrv = m_addr;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(m_port);

	int err;

	SOCKET  t_sockSrv;

	t_sockSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (t_sockSrv == INVALID_SOCKET)
		wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
	err = connect(t_sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (err == SOCKET_ERROR) {
		closesocket(t_sockSrv);
		return -1;
	}


	if (send(t_sockSrv, data.c_str(), 50, MSG_DONTROUTE) != WSANOTINITIALISED)
	{
		err = WSAGetLastError();
	}
	else
		return 0;

	return 0;
}

void transport_net::change_port()
{
	if (m_sockSrv)
	{

	}
	m_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//¼àÌý0.0.0.0
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(m_port);

	m_sockSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(m_sockSrv, (SOCKADDR*)&m_addr, sizeof(SOCKADDR));
	listen(m_sockSrv, 5);

}



transport_net::transport_net()
{

	set_port(8888);
}


transport_net::~transport_net()
{

}
