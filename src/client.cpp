#include "client.h"

Client::Client():connStatus_(true)
{
    socketini();
    allowConn();
    while(true)
    {
        std::cout<<dq->popDTA()<<std::endl;
    }
};

void Client::setConnStatus(bool connStatus)
{
	connStatus_ = connStatus;
}

bool Client::getConnStatus()
{
	return connStatus_;
}

void Client::socketini()
{
    ip->readLine();
	const char* port = ip->iniContainer["port"].c_str();
	std::cout<<port<<std::endl;
	const char* addr = ip->iniContainer["addr"].c_str();
    std::cout<<addr<<std::endl;
	
    WSAStartup(MAKEWORD(2,2), &wsaData_);
    if(iniSignal_ != 0)
	{
		logwrite.writeLog("error", "WSAStartup failed with error: " + iniSignal_);
		exit(1);
	}

    int addlen = sizeof(addr);

    ZeroMemory( &hints_, sizeof(hints_) );
    hints_.ai_family = AF_INET;
    hints_.ai_socktype = SOCK_STREAM;
    hints_.ai_protocol = IPPROTO_TCP;

    iniSignal_ = getaddrinfo(addr, port, &hints_, &result_);
	if(iniSignal_ != 0)
	{
		logwrite.writeLog("error", "getaddrinfo failed with error: " + iniSignal_);
		WSACleanup();
		exit(1);
	}

    connectSocket_ = socket(result_->ai_family, result_->ai_socktype, result_->ai_protocol);
    if (connectSocket_ == SOCKET_ERROR) 
    {
        logwrite.writeLog("error", "connect failed with error: " + iniSignal_);
		WSACleanup();
		exit(1);
    }

}

void Client::allowConn()
{
    iniSignal_ = connect(connectSocket_, result_->ai_addr, (int)result_->ai_addrlen);
    if (iniSignal_ == SOCKET_ERROR) 
    {
        logwrite.writeLog("error", "connect failed with error: " + iniSignal_);
        WSACleanup();
        exit(1);
    }
    else
    {
        logwrite.writeLog("debug", "(Client) connect success, start send&recv thread");
        std::thread sendtd(&Client::sendMsg,this);
        std::thread recvtd(&Client::recvMsg,this);
        sendtd.detach();
        recvtd.detach();
    }
}

void Client::sendMsg()
{
    while(getConnStatus())
    {
        std::string str;
        std::cout<<"input string: ";
        std::cin>>str;
        sendSignal_ = send(connectSocket_, str.c_str(), recvbuflen_, 0);
        if(sendSignal_<0)
        {
            std::cout<<"send failed"<<std::endl;
            setConnStatus(false);
        }
    }
}

void Client::recvMsg()
{
    while(getConnStatus())
    {
        recvSignal_ = recv(connectSocket_, buffer_, recvbuflen_, 0);
        if ( recvSignal_ > 0 )
        {
            buffer_[recvSignal_] = '\0';
            dq->pushDTA(buffer_);
        }
        else
        {
            std::cout<<"recv failed"<<std::endl;
            setConnStatus(false);
        }
    }
}



