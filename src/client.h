#ifndef CLIENT_H_
#define CLIENT_H_

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
#include <chrono>

#include "../lib/dataQueue.h"
#include "../lib/initParser.h"
#include "../lib/logwriter.h"

#define buffer 1024

class Client
{
public:
    Client(std::string configSelect);
    bool socketini();
    void allowConn();
    void setConnStatus(bool stat);
    bool getConnStatus();
    void sendMsg();
    void recvMsg();
    void reConnect();
    Logwriter logwrite = Logwriter("testing");
	DataQueue *dq = new DataQueue(10);
	
private:
    std::string configSelect_;
    bool connStatus_;
    WSADATA wsaData_;
    struct addrinfo *result_ = NULL;
    struct addrinfo *ptr_ = NULL;
    struct addrinfo hints_;
    int iniSignal_;
    int sendSignal_;
    int recvSignal_;
    SOCKET connectSocket_ = INVALID_SOCKET;
    char buffer_[buffer];
	int recvbuflen_ = buffer;
    std::mutex mutex_;
    std::condition_variable cv_;
};
#endif