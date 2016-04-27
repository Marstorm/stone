#pragma once
#include<string>
#include <memory>
#include "basic.h"
using std::shared_ptr;

/*!
 * \class transport
 *
 * \brief 数据传输抽象类。通过write/read实现通信。
 * 不同实现的transport不能相互通信，相同的transport只要port相同就可以通信。mode 保留		  
 * \author erow
 * \date 四月 2016
 */
using std::string;
class transport
{
public:
	transport();
	~transport();
	// return error code ,block mode
	virtual int read(string& data) { return -1; };
	// return error code ,block mode
	virtual int write(const string&  data) { return -1; };

	// return error code ,unblock mode
	virtual int try_read(string& data) ;
	// return error code ,unblock mode
	virtual int try_write(const string&  data) ;

	int get_mode();
	int set_mode(int _m_mode);
	int get_status();
	
protected:
	int m_mode;
	int m_status;
	int m_port;

	virtual void change_port() = 0;
public:
	auto get_port()->decltype(m_port) { return m_port; }
	void set_port(decltype(m_port) _port) ;

};
/*!
 * \class port  
 *
 * \brief ---------------			---------------
 * 传输介质|transport	|--------->	|transport	  |
 * 端口类型|type			|out		|type		  | in 
 * 必须相等|transit_type |			|transit_type |
 *		  ---------------			---------------
 * \author erow
 * \date 四月 2016
 */

class port
{
public:
	port(shared_ptr<transport> _transit, int _type, shared_ptr<transit_type> _dtype);
	~port();

	shared_ptr<transport> operator->();
	int get_type();
	shared_ptr<transit_type> m_data_type;
protected:
	int m_type;
	shared_ptr<transport> m_transitport;
};

