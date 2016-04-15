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



void deal(vector<virtual_type*> m_port) {// 0 == > 1
	stone s;
	s.set_message(s.message() + "a");
	
	test t;

	t.code();
	s.set_code(s.code() + t.code());
}

void print(stone & s)
{
	cout << "m:" << s.message() << ";code:" << s.code() << endl;
}
int main(int argc, char* argv[]) {
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	
	pin_array pins;
	auto p1 = make_shared<pin>();
	auto p2 = make_shared<pin>();
	pins.add_port(p1);
	pins.add_port(p2);
	
	port t;
	thread port_run = thread(&port::run, &t);
	t.Register(pins);
	port_run.detach();
	auto vs=p1->read();
	cout << vs.cast<stone>().code() << endl;
	vs = p2->read();
	cout << vs.cast<stone>().code() << endl;
	
	google::protobuf::ShutdownProtobufLibrary();
	
	return 0;
}
