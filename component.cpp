#include "component.h"

#include <thread>

component::component(deal_com_data fun, int s_buff)
{
	fun_callback = fun;
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
				buff.push_back(s);
			}
		}
		m_buffs.push(buff);
		//read message

		buff = m_buffs.front();
		m_buffs.pop();
		//call
		std::thread t(fun_callback, buff);
		t.detach();
	}
}

inline const int & component::size() { return m_register.size(); }

void component::add_port(port & _p)
{
	m_register.push_back(_p);
}
