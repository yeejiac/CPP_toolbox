#include "client.h"

Client::Client():connStatus_(true)
{
    allowConn();
    std::thread sendtd(&Client::sendMsg,this);
    std::thread recvtd(&Client::recvMsg,this);
    sendtd.detach();
    recvtd.detach();
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
		logwrite.writeLog("error", "(Client) WSAStartup failed with error: " + iniSignal_);
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
		logwrite.writeLog("error", "(Client) getaddrinfo failed with error: " + iniSignal_);
		WSACleanup();
		exit(1);
	}

    connectSocket_ = socket(result_->ai_family, result_->ai_socktype, result_->ai_protocol);
    if (connectSocket_ == SOCKET_ERROR) 
    {
        logwrite.writeLog("error", "(Client) connect failed with error: " + iniSignal_);
		WSACleanup();
		exit(1);
    }

}

void Client::allowConn()
{
    while(true)
    {
        socketini();
        iniSignal_ = connect(connectSocket_, result_->ai_addr, (int)result_->ai_addrlen);
        if (iniSignal_ == SOCKET_ERROR) 
        {
            logwrite.writeLog("error", "(Client) connect failed with error");
        }
        else
        {
            setConnStatus(true);
            logwrite.writeLog("debug", "(Client) connect success, start send&recv thread");
            break;
        }
    }
    

}

void Client::sendMsg()
{
    while(true)
    {
        std::string str = "testing Msg";
        sendSignal_ = send(connectSocket_, str.c_str(), recvbuflen_, 0);
        if(sendSignal_<0)
        {
            //set condition variable to reconnect
            logwrite.writeLog("error", "(Client) send failed");
            std::this_thread::sleep_for(std::chrono::seconds(5));
            setConnStatus(false);
            allowConn();
        }
        
    }
}

void Client::recvMsg()
{
    while(true)
    {
        recvSignal_ = recv(connectSocket_, buffer_, recvbuflen_, 0);
        if ( recvSignal_ > 0 )
        {
            buffer_[recvSignal_] = '\0';
            dq->pushDTA(buffer_);
        }
        else
        {
            logwrite.writeLog("error", "(Client) recv failed");
            std::this_thread::sleep_for(std::chrono::seconds(5));
            setConnStatus(false);
            allowConn();
        }
    }
}

void Client::reConnect()
{

}



