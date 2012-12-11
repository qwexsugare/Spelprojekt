#include "NetworkClient.h"

NetworkClient::NetworkClient()
{
}

NetworkClient::~NetworkClient()
{
}

bool NetworkClient::connect(sf::IPAddress ip, int port)
{
	//connects to the server
	if(this->hostSocket.Connect(port,ip)!=sf::Socket::Done)
	{
		cout << "error connecting"<<endl;
	}
	
	this->hostSocket.SetBlocking(false);
	//launches the thread that listen to messages from the server
	this->Launch();
	
	this->hostPort=port;
	this->hostIp=ip;
	
	return this->hostSocket.IsValid();
}

void NetworkClient::disconnect()
{
	if(this->hostSocket.IsValid())
		this->hostSocket.Close();
}

void NetworkClient::tellServer(string msg)
{
	sf::Packet packet;
	packet << msg;
	if(this->hostSocket.IsValid())
		this->hostSocket.Send(packet);
}

void NetworkClient::Run()
{
	while(this->hostSocket.IsValid())
	{
		sf::Packet packet;
		if (this->hostSocket.Receive(packet) == sf::Socket::Done)
		{
			string message;
			packet >>message;
			if(this->messageQueue.size() < 10000)
			{
				this->messageQueue.push(message);
			}
			if(message=="disconnect")
			{
				this->disconnect();
			}
		}
	}
}

bool NetworkClient::isConnected()
{
	return this->hostSocket.IsValid();
}

string NetworkClient::getMessage()
{
	string s = "";

	if(this->messageQueue.empty() == false)
	{
		s = this->messageQueue.front();
		this->messageQueue.pop();
	}

	return s;
}