#include "component.h"



component::component(deal_com_data fun, int s_buff):m_size_buff(s_buff)
{
	
}

component::~component()
{
}

void component::Register(const pin_array& reg)
{
	m_register = reg;
}

inline const int & component::size() { return m_register.size(); }
