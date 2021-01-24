#include "server.h"


Server::Server()
{
	socketini();
	std::thread connacpt(&Server::acceptConn,this);
	connacpt.detach();
}

Server::~Server()
{
	close(connfd_);
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
	int port = std::stoi(ip->iniContainer["port"]);
	std::cout<<port<<std::endl;
	const char* addr = ip->iniContainer["addr"].c_str();
	std::cout<<addr<<std::endl;
	if( (listenfd_ = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
        printf("create socket error: %s(errno: %d)\n");
        return;
    }
	memset(&servaddr_, 0,sizeof(servaddr_));
	servaddr_.sin_family = AF_INET;
	servaddr_.sin_port = htons(port);
	
    if (bind( listenfd_, (struct sockaddr*)&servaddr_, sizeof(servaddr_)) == -1) 
	{
		logwrite.write(LogLevel::WARN, "bind failed with Error: ");
        return;
    }

	
    if (listen( listenfd_, SOMAXCONN) == -1) 
	{
		logwrite.write(LogLevel::WARN, "listen failed with Error: ");
		return;
	}
	setconnStatus(true);
	logwrite.write(LogLevel::DEBUG, "server socket init success");
}

void Server::acceptConn()
{
	while(getconnStatus())
	{
		connfd_ = accept(listenfd_, (struct sockaddr *)NULL, NULL);
		if(connfd_ == -1)
		{
			logwrite.write(LogLevel::WARN, "accept failed with Error: ");
			continue;
		}
		else
		{
			setconnStatus(true);
			std::string connPortNum;

			std::unique_lock<std::mutex> lck3(mutex_);
			Connection *cn = new Connection(connfd_);
			int space = connStorage_.size();
			std::pair<int, Connection*> tmp(space, cn);
			connStorage_.insert(tmp);
			lck3.unlock();
			logwrite.write(LogLevel::DEBUG, "get socket connection: "+std::to_string(space));
			
			std::thread recvConn(&Server::msgRecv, this, cn);
			recvConn.detach();

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
			logwrite.write(LogLevel::DEBUG, "(Server): lose connection");
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
			logwrite.write(LogLevel::DEBUG, "(Server): free empty socket");
			std::unique_lock<std::mutex> lckerase(mutex_);
			it = connStorage_.erase(it);
			lckerase.unlock();
		}
	}
}

int main()
{
	Server *sr = new Server;
}

