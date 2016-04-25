#pragma once
#include<string>
#include <memory>
using std::shared_ptr;
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
/*!
#include "basic.h"
#include "basic.h"
 * \class transport
 *
 * \brief 数据传输抽象类。定义数据流动的基本操作。
 *
 * \author erow
 * \date 四月 2016
 */
using std::string;
class transport
{
public:
	transport();
	~transport();
	// return error code ,block mode
	virtual int read(string& data) =0;
	// return error code ,block mode
	virtual int write(string& const data)=0;

	// return error code ,unblock mode
	virtual int try_read(string& data);
	// return error code ,unblock mode
	virtual int try_write(string& const data);
	
	
	

	int get_mode();
	int set_mode(int _m_mode);
	int get_status();
	
protected:
	int m_mode;
	int m_status;
	int m_port;

	virtual void change_port() = 0;
public:
	auto get_port() ->decltype(m_port) { return m_port; }
	void set_port(decltype(m_port) _port);

};
/*!
 * \class port
 *
 * \brief 用在component里，增加了数据传输类型
 *
 * \author erow
 * \date 四月 2016
 */
#include "basic.h"
class port
{
public:
	port(shared_ptr<transport> _transit, int _type, shared_ptr<transit_type> _dtype);
	~port();

	shared_ptr<transport> operator->();
	int get_type();
	shared_ptr<transit_type> m_data_type;
private:
	int m_type;
	shared_ptr<transport> m_transitport;
};

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

SOCKET m_sockSrv=0;
SOCKADDR_IN m_addr;
public:

	static	WORD wVersionRequested;
	static	WSADATA wsaData;

	// return error code ,block mode
	int read(string& data) override;
	// return error code ,block mode
	int write(string& const data) override;
	void change_port() override;
	transport_net();
	~transport_net();
};


