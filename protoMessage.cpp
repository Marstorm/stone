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



void deal(vector<virtual_type> m_port) {// 0 == > 1
	cout << "component:" << endl;
	cout << m_port[0].cast<stone>().code() << endl;
	cout << m_port[1].cast<stone>().code() << endl;
}
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

	auto fun = [](vector<virtual_type> m_port) { cout<<"suc:"<<m_port[0].cast<string>(); };
	component com(fun,2);
	com.add_port(port(make_shared<transport_net>(), 1));
	thread th(&component::run, &com);
	transport_net p;
	string str;
	while (cin>>str)
	{
		p.write(str);
	}

	google::protobuf::ShutdownProtobufLibrary();
	WSACleanup();
	return 0;
}
