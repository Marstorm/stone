#include "router.h"



router::router(deal_com_data fun, int s_buff)
{
	fun_callback = fun;
	m_thread_size = s_buff;
}
void router::run()
{
	while (true)
	{
		for (int i = 0; i < m_register.size(); i++)
		{
			if (m_register[i].get_type() & 1)
			{
				string s;
				(m_register)[i]->read(s);
				auto data_type = (m_register)[i].m_data_type;
				data_type->decoding(s);
				fun_callback(m_register, i, s);
			}
			else
				;
		}

		//m_buffs.push(buff);
		//read message
	}
}

void router::add_port(port & _p)
{
	m_register.push_back(_p);
}

router::~router()
{
}
