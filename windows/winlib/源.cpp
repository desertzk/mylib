#include<iostream>
#include"winsocket.h"
using namespace std;

void main()
{
	socket_init();
	TCPServer(29007);
	system("pause");
}