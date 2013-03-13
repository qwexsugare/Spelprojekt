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

double NetworkEndGameMessage::getTimePlayed()
{
	return this->m_timePlayed;
}

int NetworkEndGameMessage::getIsAtWave()
{
	return this->m_isAtWave;
}

int NetworkEndGameMessage::getStartLife()
{
	return this->m_startLife;
}

vector<StatisticsPlayer> NetworkEndGameMessage::getPlayers()
{
	return this->m_players;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkEndGameMessage& e)
{
	packet<<*((int*)&e.m_type)<<e.m_victory<<e.m_timePlayed<<e.m_isAtWave<<e.m_startLife<<e.m_players.size();

	for(int i = 0; i < e.m_players.size(); i++)
	{
		packet<<e.m_players[i].getPlayerId()<<e.m_players[i].getPlayerName()<<e.m_players[i].getPlayerHero();
	}

	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkEndGameMessage& e)
{
	packet>>e.m_victory>>e.m_timePlayed>>e.m_isAtWave>>e.m_startLife;

	int nrOfPlayers;
	packet>>nrOfPlayers;

	for(int i = 0; i < nrOfPlayers; i++)
	{
		int id;
		string name;
		int heroType;

		packet>>id>>name>>heroType;

		e.m_players.push_back(StatisticsPlayer());
		e.m_players[i].setId(id);
		e.m_players[i].setPlayerName(name);
		e.m_players[i].setHeroType((StatisticsPlayer::HERO_TYPE)heroType);
	}

	return packet;
}