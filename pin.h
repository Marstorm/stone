#pragma once
#include "basic_server.h"
#include <string>
#include <memory>
#include "basic.h"
class pin
{
private:
	virtual_type m_data;
public:
	void operator&=(pin const&) = delete;

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

class port :public basic_server
{
public:
	void operator&=(port const&) = delete;
	void Register(const pin_array& reg);
	port();
	~port();
	void run() override;
private:
	pin_array m_pins;
};



