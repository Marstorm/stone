#pragma once
#include <vector>
#include <queue>
#include "basic.h"
#include "pin.h"

class component
{
public:
	typedef void deal_com_data(std::vector<virtual_type> m_port);
	component(deal_com_data fun, int s_buff);
	~component();
	void Register(const std::shared_ptr<pin_array>& reg);
	void run();
	inline const int&  size();
	deal_com_data* fun_callback = 0;
private:
	std::shared_ptr<pin_array> m_register;
	std::queue<std::vector<virtual_type>> m_buffs;
	
};



