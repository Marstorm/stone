#pragma once
#include <thread>
#include <vector>
#include <string.h>
#include <mutex>
class basic_server
{
protected:
	std::thread m_thread;
	std::mutex m_mutex;
	std::vector<std::string> args;
public:
	basic_server(std::vector<std::string> a= std::vector<std::string>() );
	void operator&=(basic_server const&) = delete;
	void _run();
	virtual void run() =0;
	virtual ~basic_server();
};

