#pragma once
#include<string>
#include <memory>
#include "basic.h"
using std::shared_ptr;

/*!
 * \class transport
 *
 * \brief ���ݴ�������ࡣͨ��write/readʵ��ͨ�š�
 * ��ͬʵ�ֵ�transport�����໥ͨ�ţ���ͬ��transportֻҪport��ͬ�Ϳ���ͨ�š�mode ����		  
 * \author erow
 * \date ���� 2016
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
 * �������|transport	|--------->	|transport	  |
 * �˿�����|type			|out		|type		  | in 
 * �������|transit_type |			|transit_type |
 *		  ---------------			---------------
 * \author erow
 * \date ���� 2016
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

