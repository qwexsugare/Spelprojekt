#include "NetworkEndGameMessage.h"

NetworkEndGameMessage::NetworkEndGameMessage() : NetworkMessage(NetworkMessage::EndGame)
{
}

NetworkEndGameMessage::NetworkEndGameMessage(bool _victory, double _timePlayed, int _isAtWave, int _startLife, vector<StatisticsPlayer> _players) : NetworkMessage(NetworkMessage::EndGame)
{
	this->m_victory = _victory;

	this->m_timePlayed = _timePlayed;
	this->m_isAtWave = _isAtWave;
	this->m_startLife = _startLife;

	this->m_players = _players;
}

NetworkEndGameMessage::~NetworkEndGameMessage()
{

}

bool NetworkEndGameMessage::getVictory()
{
	return this->m_victory;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkEndGameMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_victory<<e.m_timePlayed<<e.m_isAtWave<<e.m_startLife;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkEndGameMessage& e)
{
	return packet>>e.m_victory>>e.m_timePlayed>>e.m_isAtWave>>e.m_startLife;
}