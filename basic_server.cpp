#include "basic_server.h"
#include <thread>
using namespace std;

basic_server::basic_server(std::vector<std::string> a )
{
	args = a;
	thread m_t(&basic_server::_run,this);
	//use thread m_t(&basic_server::run,this); failed
	m_thread = move(m_t);
	m_thread.detach();
}

void basic_server::_run()
{
	//run();
}


basic_server::~basic_server()
{
}
