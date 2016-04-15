#pragma once
#include <vector>
#include "basic.h"
#include "pin.h"

class component
{
public:
	typedef void deal_com_data(std::vector<virtual_type*> m_port);
	component(deal_com_data fun, int s_buff);
	~component();
	void Register(const pin_array& reg);
	
	inline const int&  size();
	pin_array m_register;
private:
	int m_size_buff;
	
	
};



