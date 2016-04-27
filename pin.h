#pragma once
#include "basic_server.h"
#include <string>
#include <mutex>
#include <memory>
#include <future>
#include "basic.h"
#include "transport.h"
#include <map>
class pin:public transport
{
private:
	static std::map<int, std::string> m_data;
	std::map<int, std::string>::iterator m_str;
	int m_writen = 0;
	std::condition_variable m_data_cond;
	std::mutex m_mutex;
public:
	//void operator&=(pin const&) = default;
	pin();
	pin(int _p) { set_port(_p); }
	virtual ~pin();

	// return error code ,block mode
	int read(string& data) override;
	// return error code ,block mode
	int write(const string&  data) override;
	virtual int try_read(string& data);
	int try_write(const string&  data) override;


	// Í¨¹ý transport ¼Ì³Ð
	virtual void change_port() override;
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



