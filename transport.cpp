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
	return -1;
}

int transport::try_write(const string &  data)
{
	return -1;
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

void transport::set_port(decltype(m_port) _port)
{
	m_port = _port;
	change_port();
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
