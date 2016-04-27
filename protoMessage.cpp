// protoMessage.cpp : 定义控制台应用程序的入口点。
//


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <google\protobuf\service.h>
#include "packages.h"
using namespace std;
using namespace google::protobuf;



void print(stone & s)
{
	cout << "m:" << s.message() << ";code:" << s.code() << endl;
}
#include <Winsock2.h>
#include "transport.h"
#include "realised/winNet.h"
#include "router.h"

/*
		
			
		--router-					--del----	
cin ->  ->  1	|					|   	|
		|	 2	->		--add---	->	2	|
		|    3	->		->  3	|	|    	|
cin->	---------		->  4 	|	->	4	|
						|    5	->	|  5	->     cout  
						---------	---------




*/
int main(int argc, char* argv[]) {
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	transport_net::wVersionRequested = MAKEWORD(1, 1);

	auto iResult=WSAStartup(transport_net::wVersionRequested, &transport_net::wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	component add( [](vector<virtual_type>& m_port) {
		stone v = (m_port[0].cast<stone>());
		int a = v.code();
		v = (m_port[1].cast<stone>());
		v.set_code(v.code() + a);
		m_port[2] = v;

		cout << "add:" << endl;
	}, 2);
	auto p1 = make_shared<pin>(); 
	auto p2 = make_shared<pin>(); 
	auto p3 = make_shared<pin>();
	auto p4 = make_shared<pin>();
	auto p5 = make_shared<pin>();
	{
		add.add_port(port(p3, 1, make_shared<proto_type<stone>>() ));
		add.add_port(port(p4, 1, make_shared<proto_type<stone>>()));
		add.add_port(port(p5, 2, make_shared<proto_type<stone>>()));
	}
	thread th(&component::run, &add);
	component del([](vector<virtual_type>& m_port) {
		stone v = (m_port[0].cast<stone>());
		int a = v.code();
		v = (m_port[1].cast<stone>());
		v.set_code(a-v.code());
		m_port[2] = v;
		cout << "del:" << endl;
	}, 2);
	{
		del.add_port(port(p2, 1, make_shared<proto_type<stone>>()));
		del.add_port(port(p4, 1, make_shared<proto_type<stone>>()));
		del.add_port(port(p5, 2, make_shared<proto_type<stone>>()));
	}
	thread th1(&component::run, &del);
	auto fun = [](std::vector<port>& _register, int i, string& _str) {
		cout << "p:" << _register[i]->get_port() << ",s:" << _str << endl;
		static int _c = 0;
		_c = !_c;
		_register[_c + 1]->write(_str);
		
	};
	router r(fun,2);
	{
		r.add_port(port(p1, 1, make_shared<proto_type<stone>>()));
		r.add_port(port(p2, 2, make_shared<proto_type<stone>>()));
		r.add_port(port(p3, 2, make_shared<proto_type<stone>>()));
	}
	thread th2(&router::run, &r);

	int a,b;
	while (cin>>a>>b)
	{
		static stone t,t1;
		t.set_code(a);
		p1->write( t.SerializeAsString());
		t.set_code(b);
		p4->write(t.SerializeAsString());


		string s;
		if (p5->read(s)==0)
		{
			stone tem; tem.ParseFromString(s);
			cout << "ans:" << tem.code() << endl;
		}
	}

	google::protobuf::ShutdownProtobufLibrary();
	WSACleanup();
	return 0;
}
