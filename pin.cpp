#include "pin.h"
#include "proto/request.pb.h"
#include <fstream>

using namespace std;
std::map<int, std::string> pin::m_data;
pin::pin():transport()
{
	static int _port = 0;
	while (true)
	{
		m_str = m_data.find(++_port);
		if (m_str == m_data.end())
		{
			set_port(_port);
			break;
		}
	}
	
}


pin::~pin()
{
}

int pin::read(string & data)
{
	std::unique_lock<std::mutex> lk(m_mutex);
	m_data_cond.wait(lk, [&m = m_writen] {return m == 1; });
	m_writen = 0;
	data = m_str->second;
	m_data_cond.notify_one();
	return 0;
}

int pin::write(const string & data)
{
	std::unique_lock<std::mutex> lk(m_mutex);
	m_data_cond.wait(lk, [&m = m_writen] {return m == 0; });
	m_str->second = data;
	m_writen = 1;
	m_data_cond.notify_all();

	return 0;
}

int pin::try_read(string & data)
{
	
	if (m_writen == 1) {
		data = m_str->second;
		m_writen = 0;
		return 0;
	}
		
	
	return -1;
}

int pin::try_write(const string & data)
{
	if (m_mutex.try_lock())
	{
		m_str->second = data;
		m_writen = 1;
		m_data_cond.notify_one();
		return 0;
	}
	else
	{
		return -1;
	}
	
}

void pin::change_port()
{
	m_str = m_data.find(m_port);
	if (m_str==m_data.end())
	{
		m_data[m_port];
		m_str = m_data.find(m_port);
	}
}





pin_array::pin_array()
{

}

void pin_array::add_port(std::shared_ptr<pin> con)
{
	m_register.push_back(con);
}

bool pin_array::IsInDone()
{

	return false;
}
bool pin_array::IsOutDone()
{

	return false;
}
inline int pin_array::size() { return m_register.size(); }

pin_array::~pin_array()
{

}