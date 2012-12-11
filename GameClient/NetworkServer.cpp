#include "NetworkServer.h"

NetworkServer::NetworkServer()
{
	this->clientArrPos=0;
}

NetworkServer::~NetworkServer()
{
}

bool NetworkServer::start(int port)
{
	//if the server cant listen to the port, return
	if(!this->listener.Listen(port))
		return false;
	
	//otherwise, continue by adding the listening socket to the selector and start selector thread
	this->Launch();
	this->selector.Add(this->listener);
		return true;
}

//the selector is blocking, so runs in a thread
void NetworkServer::goThroughSelector()
{
	unsigned int itemsInSelector= this->selector.Wait();
	
	for(unsigned int i =0;i<itemsInSelector;i++)
	{
		//fetches a ready socket from the selector
		sf::SocketTCP sock = this->selector.GetSocketReady(i);
		
		if(sock==this->listener)
		{
			sf::IPAddress ip;
			sf::SocketTCP incSocket;
			//accept the new socket
			this->listener.Accept(incSocket, &ip);
			cout << "client connected: " << ip.ToString()<<endl;
			//and add it to the selector
			this->selector.Add(incSocket);
			this->clients[this->clientArrPos++]=incSocket;
		}
		//else its a client socket who wants to sent a message
		else
		{
			sf::Packet packet;
			if (sock.Receive(packet) == sf::Socket::Done)
			{
				// Extract the message and display it
				string message;
				packet >> message;
				cout << "A client says : \"" << message << "\"" << endl;
			}
			else
			{
				// if done wasnt completed, the socket will be removed from the selector
				if(this->listener.IsValid())
				{
					this->selector.Remove(sock);
					cout<<"A client disconnected!"<<endl;
					for(int i=0;i<this->clientArrPos;i++)
					{
						if(this->clients[i]==sock)
						{
							this->clients[i]=this->clients[--this->clientArrPos];
						}
					}
				}
			}
		}
	}
}

void NetworkServer::shutDown()
{
	for(int i=0;i<this->clientArrPos;i++)
	{
		sf::Packet msg;
		msg << "disconnect";
		if(this->clients[i].IsValid())
		{
			this->clients[i].Send(msg);
			this->clients[i].Close();
		}
	}
	if(this->listener.IsValid())
	{
		this->listener.Close();
	}
}

void NetworkServer::broadcast(string msg)
{
	sf::Packet packet;
	packet<<msg;
	for(int i=0;i<this->clientArrPos;i++)
	{
		this->clients[i].Send(packet);
	}
}

void NetworkServer::Run()
{
	while(this->listener.IsValid())
	{
		this->goThroughSelector();
	}
}

bool NetworkServer::isRunning()
{
	return this->listener.IsValid();
}