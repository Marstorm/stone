
#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#ifndef S_ISDIR
#define S_ISDIR(x) (((x) & S_IFMT) == S_IFDIR)
#endif
#else
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#endif
#include "transport.h"
/*!
* \class transport_net
*
* \brief transport的基于网络的实现。
*
* \author erow
* \date 四月 2016
*/


class transport_net :public transport
{
private:

	SOCKET m_sockSrv = 0;
	SOCKADDR_IN m_addr;
public:

	static	WORD wVersionRequested;
	static	WSADATA wsaData;

	// return error code ,block mode
	int read(string& data) override;
	// return error code ,block mode
	int write(const string&  data) override;
	int try_write(const string&  data) override;
	void change_port() override;
	transport_net();
	~transport_net();
};