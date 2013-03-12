#pragma once
#include "networkmessage.h"
#include "Statistics.h"

class NetworkEndGameMessage : public NetworkMessage
{
private:
	bool m_victory;

	//Statistics
	double m_timePlayed;
	int m_isAtWave;
	int m_startLife;

	vector<StatisticsPlayer> m_players;
public:
	NetworkEndGameMessage();
	NetworkEndGameMessage(bool _victory, double _timePlayed, int _isAtWave, int _startLife, vector<StatisticsPlayer> _players);
	~NetworkEndGameMessage();

	bool getVictory();
	double getTimePlayed();
	int getIsAtWave();
	int getStartLife();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkEndGameMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkEndGameMessage& e);
};

