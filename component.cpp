#include "component.h"



component::component(deal_com_data fun, int s_buff)
{
	fun_callback = fun;
}

component::~component()
{
}

void component::Register(const std::shared_ptr<pin_array>& reg)
{
	m_register = reg;
}

void component::run()
{
	while (true)
	{
		std::vector<virtual_type> buff;
		for (int i = 0; i < m_register->size(); i++)
		{
			buff.push_back((*m_register)[i]->read());
		}
		m_buffs.push(buff);
		//read message

		buff = m_buffs.front();
		m_buffs.pop();
		//call
		fun_callback(buff);

		
	}
}

inline const int & component::size() { return m_register->size(); }
