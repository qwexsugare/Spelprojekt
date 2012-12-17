#include "Msg.h"

Msg::Msg()
{
	this->text="message not set";
}

Msg::Msg(string txt)
{
	this->text=txt;
}

void Msg::setText(string txt)
{
	this->text=txt;
}

string Msg::getText()
{
	return this->text;
}

sf::Packet& operator<<(sf::Packet& packet,const Msg& e)
{
	return packet<<"MSG"<<e.text;
}
sf::Packet& operator>>(sf::Packet& packet, Msg& e)
{
	return packet >> e.text;
}