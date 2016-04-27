#include "component.h"

#include <thread>

component::component(deal_com_data fun, int s_buff)
{
	fun_callback = fun;
	m_thread_size = s_buff;
}

component::~component()
{
}

 

void component::run()
{
	while (true)
	{
		std::vector<virtual_type> buff;
		for (int i = 0; i < m_register.size(); i++)
		{
			if (m_register[i].get_type() & 1)
			{
				string s;
				(m_register)[i]->read(s);
				auto data_type = (m_register)[i].m_data_type;
				data_type->decoding(s);
				buff.push_back(data_type->m_data);
			}
			else
				buff.push_back(virtual_type());
		}

		m_buffs.push(buff);
		//read message
		deal_data();
	}
}

void component::deal_data( )
{
	std::lock_guard<std::mutex> t(m_mutex);
	//call
	std::vector<virtual_type> buff = m_buffs.front();
	m_buffs.pop();
	fun_callback(buff);

	//send to out ports
	for (int i = 0; i < m_register.size(); i++)
	{
		if (m_register[i].get_type() & 2)//check out
		{
			auto data_type = (m_register)[i].m_data_type;
			data_type->m_data = buff[i];
			m_register[i]->write(data_type->encoding());
			m_register[i].m_data_type->m_data.get_type_name();
		}
	}
	
}

inline const int & component::size() { return m_register.size(); }

void component::add_port(port & _p)
{
	m_register.push_back(_p);
}
