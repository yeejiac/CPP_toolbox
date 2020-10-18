#include "server.h"


Server::Server()
{
	socketini();
	std::thread connacpt(&Server::acceptConn,this);
	// std::thread recvConn(&Server::recv_conn,this);
	connacpt.join();
	// recvConn.detach();
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
	std::cout<<port<<std::endl;
	const char* addr = ip->iniContainer["addr"].c_str();
	std::cout<<addr<<std::endl;
	iniSignal_ = WSAStartup(MAKEWORD(2,2), &wsaData_);
	if(iniSignal_ != 0)
	{
		logwrite.write("Error", "WSAStartup failed with Error: " + iniSignal_);
		exit(1);
	}
	memset(&hints_, 0,sizeof(hints_));
	hints_.ai_family = AF_INET;
	hints_.ai_socktype = SOCK_STREAM;
	hints_.ai_protocol = IPPROTO_TCP;
	hints_.ai_flags = AI_PASSIVE;
	
	iniSignal_ = getaddrinfo(addr, port, &hints_, &result_);
	if(iniSignal_ != 0)
	{
		logwrite.write("Error", "getaddrinfo failed with Error: " + iniSignal_);
		WSACleanup();
		exit(1);
	}
	
	listenSocket_ = socket(result_->ai_family, result_->ai_socktype, result_->ai_protocol);
	if(listenSocket_ == INVALID_SOCKET)
	{
		logwrite.write("Error", "socket failed with Error: "+ WSAGetLastError());
		freeaddrinfo(result_);
		WSACleanup();
		exit(1);
	}
	
	iniSignal_ = bind( listenSocket_, result_->ai_addr, (int)result_->ai_addrlen);
    if (iniSignal_ == SOCKET_ERROR) 
	{
		logwrite.write("Error", "bind failed with Error: " + WSAGetLastError());
        freeaddrinfo(result_);
        closesocket(listenSocket_);
        WSACleanup();
        exit(1);
    }
	freeaddrinfo(result_);
	
	iniSignal_ = listen( listenSocket_, SOMAXCONN);
    if (iniSignal_ == SOCKET_ERROR) 
	{
		logwrite.write("Error", "listen failed with Error: " + WSAGetLastError());
		std::cout<<"listen failed with Error: "<< WSAGetLastError()<<std::endl;
        closesocket(listenSocket_);
        WSACleanup();
        exit(1);
	}
	setconnStatus(true);
	logwrite.write("Debug", "server socket init success");
}

void Server::acceptConn()
{
	while(getconnStatus())
	{
		clientSocket_ = accept(listenSocket_, (struct sockaddr *)&result_, NULL);
		if(clientSocket_ == INVALID_SOCKET)
		{
			std::cout<<"accept failed with Error: "<< WSAGetLastError()<<std::endl;
			logwrite.write("Error", "accept failed with Error: " + WSAGetLastError());
			closesocket(listenSocket_);
			WSACleanup();
			exit(1);
		}
		else
		{
			setconnStatus(true);
			std::string connPortNum;

			std::unique_lock<std::mutex> lck3(mutex_);
			Connection *cn = new Connection(clientSocket_);
			int space = connStorage_.size();
			std::pair<int, Connection*> tmp(space, cn);
			connStorage_.insert(tmp);
			lck3.unlock();

			logwrite.write("Debug", "get socket connection: "+std::to_string(space));
			

			std::thread recvConn(&Server::msgRecv, this, cn);
			recvConn.detach();
			// st_.wait(lck3);

		}
	}
}

void Server::msgRecv(Connection *cn)
{
	while(connStatus_)
	{
		std::string recvStr;
		bool connStatus = true;
		connStatus = cn->recvfrom(recvStr);
		if(connStatus&&recvStr!="")
		{
			//push to queue
			dq->pushDTA(recvStr);
			// logwrite.write("Debug", "recv from client: " + recvStr);
		}
		else
		{
			st_.notify_one();
			freeEmptysocket();
			// logwrite.write("Debug", "(Server): lose connection");
		}
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

void Server::freeEmptysocket()
{
	std::map<int, Connection*>::iterator it;
	for(it = connStorage_.begin(); it!=connStorage_.end(); ++it)
	{
		if(!it->second->getRecvStatus())
		{
			logwrite.write("Debug", "(Server): free empty socket");
			std::unique_lock<std::mutex> lckerase(mutex_);
			it = connStorage_.erase(it);
			lckerase.unlock();
		}
	}
}

