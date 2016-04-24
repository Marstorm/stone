#pragma once
#include "basic_server.h"
#include <string>
#include <mutex>
#include <memory>
#include <future>
#include "basic.h"
class pin
{
private:
	virtual_type m_data;
	int m_writen = 0;
	std::condition_variable m_data_cond;
	std::mutex m_mutex;
public:
	//void operator&=(pin const&) = default;

	void write(const virtual_type& data);
	const virtual_type& read();//I want it return virtual_type.But virtual_type has some bug. 
	pin();
	virtual ~pin();
};

class pin_array
{
public:
	pin_array();

	void add_port(std::shared_ptr<pin> con);

	bool IsInDone();
	bool IsOutDone();
	int size();

	std::shared_ptr<pin> operator[](int num) { return m_register[num]; }
	~pin_array();

private:

	std::vector<std::shared_ptr<pin> > m_register;

};



