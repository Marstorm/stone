#include "transport.h"
#ifdef WIN32

#pragma comment(lib,"ws2_32.lib")
#endif // WIN32

using namespace std;
transport::transport()
{
}

transport::~transport()
{
}

int transport::try_read(string & data)
{
	return 0;
}

int transport::try_write(string & const data)
{
	return 0;
}

inline int transport::get_mode()
{ 
	return m_mode; 
}

inline int transport::set_mode(int _m_mode) 
{ m_mode = _m_mode; }

int transport::get_status()
{
	return m_status;
}

inline void transport::set_port(decltype(m_port) _port)
{
	m_port = _port;
	change_port();
}

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

int transport_net::write(string & const data)
{
	
	SOCKADDR_IN addrSrv=m_addr;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	int err;
	auto t_sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	
	err = connect(t_sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	
	
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
	
	m_sockSrv = socket(AF_INET, SOCK_STREAM, 0);
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


port::port(shared_ptr<transport> _transit, int _type, shared_ptr<transit_type> _dtype):m_transitport(_transit),m_type(_type),m_data_type(_dtype)
{

}

port::~port()
{
}

shared_ptr<transport> port::operator->()
{
	return m_transitport;
}

int port::get_type()
{
	return m_type;
}
