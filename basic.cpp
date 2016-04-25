#include "basic.h"



transit_type::transit_type(virtual_type & _data)
{
	m_data = _data;
}

transit_type::~transit_type()
{
}

template <class T>
proto_type<T>::proto_type(virtual_type & _data):transit_type(_data)
{
}

