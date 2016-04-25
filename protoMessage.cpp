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
int main(int argc, char* argv[]) {
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	transport_net::wVersionRequested = MAKEWORD(1, 1);
	WSAStartup(transport_net::wVersionRequested, &transport_net::wsaData);

	auto fun = [](vector<virtual_type>& m_port) {
		auto v = m_port[0].cast<stone>();
		cout << "0suc:" << v.message() << endl;
		v = m_port[1].cast<stone>();
		cout << "1suc:" << v.code() << endl;

		m_port[2] = v;
	};
	component com(fun,2);
	auto p = make_shared<transport_net>();
	auto p1 = make_shared<transport_net>(); p1->set_port(999);
	auto p2 = make_shared<transport_net>(); p2->set_port(9999);
	com.add_port(port(p, 1, make_shared<proto_type<stone>>() ));
	com.add_port(port(p1, 1, make_shared<proto_type<stone>>()));
	com.add_port(port(p2, 2, make_shared<proto_type<stone>>()));
	thread th(&component::run, &com);

	string str;
	while (cin>>str)
	{
		static stone t,t1;
		t.set_message(str);
		t1.set_code(t1.code() + 1);
		p->write( t.SerializeAsString());
		p1->write(t1.SerializeAsString());
		string s;
		p2->read(s); stone tem; tem.ParseFromString(s);
		cout <<"s:"<<tem.code()<< endl;
	}

	google::protobuf::ShutdownProtobufLibrary();
	WSACleanup();
	return 0;
}
