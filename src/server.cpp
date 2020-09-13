#include "server.h"

Server::Server()
{
	socketini();
	// acceptConn();
}

Server::~Server()
{
	iniSignal_ = shutdown(clientSocket_, SD_SEND);
	closesocket(clientSocket_);
	WSACleanup();
}

void Server::setconnStatus(bool connStatus)
{
	connStatus_ = connStatus;
}

bool Server::getconnStatus()
{
	return connStatus_;
}

void Server::socketini()
{
	ip->readLine();
	const char* port = ip->iniContainer["port"].c_str();
	const char* addr = ip->iniContainer["addr"].c_str();
	iniSignal_ = WSAStartup(MAKEWORD(2,2), &wsaData_);
	if(iniSignal_ != 0)
	{
		std::cout<<"WSAStartup failed with error: "<< iniSignal_<<std::endl;
		exit(1);
	}
	ZeroMemory(&hints_, sizeof(hints_));
	hints_.ai_family = AF_INET;
	hints_.ai_socktype = SOCK_STREAM;
	hints_.ai_protocol = IPPROTO_TCP;
	hints_.ai_flags = AI_PASSIVE;
	
	iniSignal_ = getaddrinfo(addr, port, &hints_, &result_);
	if(iniSignal_ != 0)
	{
		std::cout<<"getaddrinfo failed with error: "<< iniSignal_<<std::endl;
		WSACleanup();
		exit(1);
	}
	
	listenSocket_ = socket(result_->ai_family, result_->ai_socktype, result_->ai_protocol);
	if(listenSocket_ == INVALID_SOCKET)
	{
		std::cout<<"socket failed with error: "<< WSAGetLastError()<<std::endl;
		freeaddrinfo(result_);
		WSACleanup();
		exit(1);
	}
	
	iniSignal_ = bind( listenSocket_, result_->ai_addr, (int)result_->ai_addrlen);
    if (iniSignal_ == SOCKET_ERROR) 
	{
        std::cout<<"bind failed with error: "<< WSAGetLastError()<<std::endl;
        freeaddrinfo(result_);
        closesocket(listenSocket_);
        WSACleanup();
        exit(1);
    }
	freeaddrinfo(result_);
	
	iniSignal_ = listen( listenSocket_, SOMAXCONN);
    if (iniSignal_ == SOCKET_ERROR) 
	{
		std::cout<<"listen failed with error: "<< WSAGetLastError()<<std::endl;
        closesocket(listenSocket_);
        WSACleanup();
        exit(1);
	}
	setconnStatus(true);
	std::cout<<"server socket init success"<<std::endl;
	
}

void Server::acceptConn()
{
	clientSocket_ = accept(listenSocket_, NULL, NULL);
	if(clientSocket_ == INVALID_SOCKET)
	{
		std::cout<<"accept failed with error: "<< WSAGetLastError()<<std::endl;
		closesocket(listenSocket_);
		WSACleanup();
        exit(1);
	}
	else
	{
		std::cout<<"get socket connection"<<std::endl;
	}
}

// int main()
// {
//     // Logwriter logwrite("testing");
//     // logwrite.writeLog("debug", "just testing");
//     Server *sr = new Server;
//     return 0;
// }

// void Server::recv()
// {
// 	while(connStatus_)
// 	{
// 		iniSignal_ = recv(clientSocket_, buffer_, recvbuflen_, 0);
// 		if(iniSignal_>0)
// 		{
// 			std::cout<<"recv from client: "<<buffer_<<std::endl;
// 		}
// 	}
// }

// void Server::send()
// {
// 	while(connStatus_)
// 	{
// 		iSendResult_ = send(clientSocket_, "Hello", iniSignal_, 0);
// 		if (iSendResult == SOCKET_ERROR) 
// 		{
//             printf("send failed with error: %d\n", WSAGetLastError());
//             closesocket(ClientSocket);
//             WSACleanup();
//             return 1;
//         }
// 	}
// }
