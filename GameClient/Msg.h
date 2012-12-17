#ifndef MSG_H
#define MSG_H
#include <string>
#include <SFML\Network.hpp>

using namespace std;

class Msg
{
private:
	string text;
public:
	Msg();
	Msg(string txt);
	void setText(string txt);
	string getText();
	friend sf::Packet& operator<<(sf::Packet& packet,const Msg& e);
	friend sf::Packet& operator>>(sf::Packet& packet, Msg& e);

};

#endif