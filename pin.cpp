#include "pin.h"
#include "proto/request.pb.h"
#include <fstream>

using namespace std;
//阻塞模式：先写后读。如果写完再写需等待读
void pin::write(const virtual_type & data)
{
	std::unique_lock<std::mutex> lk(m_mutex);
	m_data_cond.wait(lk, [&m = m_writen] {return m == 0; });
	m_data = data;
	m_writen = 1;
	m_data_cond.notify_one();
	
}
//读前等待写
const virtual_type& pin::read()
{
	std::unique_lock<std::mutex> lk(m_mutex);
	m_data_cond.wait(lk, [&m = m_writen] {return m == 1; });
	m_writen = 0;
	m_data_cond.notify_one();
	return (m_data);
}
pin::pin()
{
}


pin::~pin()
{
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