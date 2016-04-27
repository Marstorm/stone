/*!
* \file basic.h
* \breif 基本数据类型的抽象。virtual_type 万用类型，transit_type 数据传输类型
* \author erow
* \date 四月 2016
*
*	定义基本数据类型
*/

#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using std::shared_ptr;
using std::string;
using std::cout;
class __base_type {
public:
	virtual const char* get_id_name() = 0;//验证类型名称
};
/*!
* \class real_type
*
* \brief 数据实体：需要使用类模板来创建。
*
* \author erow
* \date 四月 2016
*/
template<class T>
class real_type :public __base_type
{
public:
	const T&  get_value() {
		return m_data;
	}
	const char* get_id_name() { return typeid(T).name(); }

	void assign(const T& data) { m_data = data; }
	real_type() {}
	~real_type() {}

private:
	T m_data;
};
/*!
 * \class virtual_type
 *
 * \ingroup microcloud
 *
 * \brief boost:any.can accept any type 
 *
 * USEAGE: 
 string str="asd";
 virtual_type vs = str, vs1;
 vs1 = vs;
 cout << vs.cast<string>() << endl;
 cout << vs1.cast<string>();
 *
 * \note There are maybe some mistakes
 *
 * \author erow
 *
 * \version 1.0
 *
 * \date 四月 2016
 *
 * Contact: clouderow@gmail.com
 *
 */
class virtual_type {
public:
	virtual_type() :policyPtr(nullptr) {}
	virtual_type(const virtual_type& x)
	{
		policyPtr = x.policyPtr;
	}

	const virtual_type& operator=(const virtual_type& x)
	{
		policyPtr = x.policyPtr;
		return *this;
	}
	template<typename T>
	virtual_type(const T& x) {
		policyPtr = std::make_shared<real_type<T> >();
		(static_cast<real_type<T>*>(policyPtr.get()))->assign(x);
	}
	template<typename T>
	const virtual_type& operator=(const T& x) {
		
		policyPtr = std::make_shared<real_type<T> >() ;
		(static_cast<real_type<T>*>(policyPtr.get()))->assign(x);
		return *this;
	}
	/*!
	* \brief cast 返回的是一个拷贝
	*/
	template<typename T>
	T cast() 
	{
		//cout << typeid(T).name() << "\n" << policyPtr->get_id_name();
		if (policyPtr!=nullptr) 
		{ 
			assert(strcmp(typeid(T).name(), policyPtr->get_id_name()) == 0);//确保类型相同
			return (static_cast<real_type<T>*>(policyPtr.get()))->get_value();
		}
		throw std::exception("nullptr");
		return T();
	}
	template<typename T>
	T try_cast()
	{
		if (is_typeof<T>()) {
			if (policyPtr != nullptr)
			{
				assert(strcmp(typeid(T).name(), policyPtr->get_id_name()) == 0);//确保类型相同
				return (static_cast<real_type<T>*>(policyPtr.get()))->get_value();
			}
		}
		else
		throw std::exception("nullptr");
		else
		{
			throw std::exception("wrong type");
		}
		return T();
	}
	template<typename T>
	bool  try_cast(T& ans)
	{
		if (is_typeof<T>()) {
			if (policyPtr != nullptr)
			{
				assert(strcmp(typeid(T).name(), policyPtr->get_id_name()) == 0);//确保类型相同
				ans = (static_cast<real_type<T>*>(policyPtr.get()))->get_value();
				return true;
			}
		}
		
			return false;
	}
	/*!
	* \brief modify 修改内容
	*/
	template<typename T>
	void modify(const T& data)
	{
		if (policyPtr != nullptr)
		{
		assert(strcmp(typeid(T).name(), policyPtr->get_id_name()) == 0);
		(static_cast<real_type<T>*>(policyPtr.get()))->assign(data);
		}
		else		throw std::exception("nullptr");

	}
	bool is_empty() {
		return policyPtr == nullptr;
	}
	const char * get_type_name()
	{
		return policyPtr->get_id_name();
	}
	template<typename T>
	bool is_typeof()
	{
		return strcmp(policyPtr->get_id_name(), typeid(T).name()) == 0;
	}
	template<typename T>
	bool is_typeof(T& a)
	{
		return strcmp(policyPtr->get_id_name(), typeid(T).name()) == 0;
	}
	~virtual_type() {
		
	}
	void print_type()
	{
		cout << policyPtr->get_id_name() << std::endl;
	}
private:

	shared_ptr<__base_type> policyPtr;

};

/*!
 * \class transit_type
 *
 * \brief 数据编码，类型验证。用以传输。
 *
 * \author erow
 * \date 四月 2016
 */
class transit_type
{
public:
	transit_type(virtual_type& _data);
	~transit_type();
	virtual string encoding() { return string(); }
	virtual void decoding(const string& ){}
	string get_name() { return m_data.get_type_name(); }
	virtual_type m_data;
private:
};

template <class T>
class proto_type :public transit_type
{
public:
	proto_type(virtual_type& _data);
	proto_type():transit_type(virtual_type(T())){}
	string encoding() override
	{
		return m_data.cast<T>().SerializeAsString();
	}
	void decoding(const string& _str) override
	{
		T t;
		t.ParseFromString(_str);
		m_data.modify(t);
	}
};