#pragma once
#include "basic_server.h"
#include "basic.h"
#include "transport.h"
#include <queue>
using std::deque;
class router : public basic_server
{
public:
	typedef void deal_com_data(std::vector<port>& _register,int _port,string& _str);
	router(deal_com_data fun, int s_buff);
	~router();

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

