#ifndef CONNECTION_H_
#define CONNECTION_H_

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

#include "../lib/logwriter.h"
#include "../lib/initParser.h"

#define buffer 1024

class Connection
{
public:
    Connection(int new_socket);
    Connection(const Connection& rhs);
    Connection& operator=(const Connection& rhs);
    void setRecvStatus(bool stat);
    bool getRecvStatus();
    bool recvfrom(std::string& str);
    int sendto(std::string str);
private:
    int connection_socket_;
    bool recvStatus_;
    char buffer_[buffer];
	int recvbuflen_ = buffer;
    mutable std::mutex mutex_;
    std::condition_variable conncv_;

};

#endif