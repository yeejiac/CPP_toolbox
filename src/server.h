#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <string>
// #include "lib/logwriter.h"
#include "../lib/initParser.h"

#define buffer 1024

class Server
{
public:
	Server();
	~Server();
	void socketini();
	void acceptConn();
	void recv_conn();
	void send();
	void setconnStatus(bool connStatus);
	bool getconnStatus();
	
private:
	WSADATA wsaData_;
	int iniSignal_;
	SOCKET listenSocket_;
	SOCKET clientSocket_;
	struct addrinfo *result_ = NULL;
	struct addrinfo hints_;
	int iSendResult_;
	char buffer_[buffer];
	int recvbuflen_ = buffer;
	bool connStatus_;
	InitParser *ip = new InitParser("D:\\program_file\\CPP_toolbox\\doc\\settings.ini", "socket");
};



#endif