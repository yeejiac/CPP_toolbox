#include "client.h"

Client::Client(std::string configSelect):connStatus_(true),configSelect_(configSelect)
{
    allowConn();
    std::thread sendtd(&Client::sendMsg,this);
    std::thread recvtd(&Client::recvMsg,this);
    sendtd.detach();
    recvtd.join();
    std::this_thread::sleep_for(std::chrono::seconds(2));
};

void Client::setConnStatus(bool connStatus)
{
    std::lock_guard<std::mutex> lckConnect(mutex_);
	connStatus_ = connStatus;
}

bool Client::getConnStatus()
{
    std::lock_guard<std::mutex> lckConnect(mutex_);
	return connStatus_;
}

bool Client::socketini()
{
    InitParser *ip = new InitParser("D:\\program_file\\CPP_toolbox\\doc\\settings.ini", configSelect_);
    ip->readLine();
	const char* port = ip->iniContainer["port"].c_str();
	const char* addr = ip->iniContainer["addr"].c_str();
	
    WSAStartup(MAKEWORD(2,2), &wsaData_);
    if(iniSignal_ != 0)
	{
		logwrite.write("Error", "(Client) WSAStartup failed with error ");
		// exit(1);
	}

    int addlen = sizeof(addr);

    ZeroMemory( &hints_, sizeof(hints_) );
    hints_.ai_family = AF_INET;
    hints_.ai_socktype = SOCK_STREAM;
    hints_.ai_protocol = IPPROTO_TCP;

    iniSignal_ = getaddrinfo(addr, port, &hints_, &result_);
	if(iniSignal_ != 0)
	{
		logwrite.write("Error", "(Client) getaddrinfo failed with error ");
		WSACleanup();
		// exit(1);
	}

    connectSocket_ = socket(result_->ai_family, result_->ai_socktype, result_->ai_protocol);
    if (connectSocket_ == SOCKET_ERROR) 
    {
        logwrite.write("Error", "(Client) connect failed with error" );
		WSACleanup();
		// exit(1);
    }
    iniSignal_ = connect(connectSocket_, result_->ai_addr, (int)result_->ai_addrlen);
    setConnStatus(iniSignal_!=0?false:true);
    if(getConnStatus())
    {
        logwrite.write("Debug", "(Client) Socket Init success" );
        return true;
    }    
    else
    {
        logwrite.write("Debug", "(Client) Socket Init failed" );
        return false;
    }
        

}

void Client::allowConn()
{
    while(true)
    {
        if (socketini()) 
        {
            logwrite.write("Debug", "(Client) connect success ");
            cv_.notify_all();
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
        logwrite.write("Debug", "(Client) try connect" );
    }
}

void Client::sendMsg()
{
    while(true)
    {
        std::string str = "Testing Msg";
        sendSignal_ = send(connectSocket_, str.c_str(), recvbuflen_, 0);
        if(sendSignal_<0)
        {
            logwrite.write("Error", "(Client) send failed");
            std::unique_lock<std::mutex> lck2(mutex_);
            cv_.wait(lck2);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
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
            logwrite.write("Error", "(Client) recv failed");
            closesocket(connectSocket_);
            setConnStatus(false);
            std::thread reconn(&Client::allowConn,this);
            reconn.detach();
            std::unique_lock<std::mutex> lck2(mutex_);
            cv_.wait(lck2);
        }
    }
}



