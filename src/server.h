#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <string>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include <thread>

#include "../lib/logwriter.h"
#include "connection.h"
#include "../lib/initParser.h"

#define buffer 1024

class Server
{
public:
	Server();
	~Server();
	void socketini();
	void acceptConn();
	void msgRecv(Connection *cn);
	void send();
	void setconnStatus(bool connStatus);
	bool getconnStatus();
	Logwriter logwrite = Logwriter("testing");
	
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
	std::mutex mutex_;
    std::condition_variable conncv_;
	InitParser *ip = new InitParser("D:\\program_file\\CPP_toolbox\\doc\\settings.ini", "socket");
};



#endif