#pragma once
#include <vector>
#include <queue>
#include <memory>
#include "basic.h"
#include "transport.h"
#include "pin.h"

using std::shared_ptr;


class component: public basic_server
{
public:
	typedef void deal_com_data(std::vector<virtual_type>& m_port);
	component(deal_com_data fun, int s_buff);
	~component();

	void run();
	void deal_data();

	inline const int&  size();
	void add_port(port& _p);
private:
	int m_thread_size;
	std::vector<port> m_register;
	std::queue<std::vector<virtual_type>> m_buffs;
	deal_com_data* fun_callback = 0;
};



