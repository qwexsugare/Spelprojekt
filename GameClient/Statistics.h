#pragma once
#include "StatisticsPlayer.h"
#include <fstream>

class Statistics
{
private:
	static double timePlayed;
	static int isAtWave;
	static int startLife;
	static StatisticsPlayer sPlayers[4];
public:
	Statistics(void);
	~Statistics(void);
	static void addTime(float t);
	static void waveFinnished();
	static void setStartLife(int l);
	static void decreaseStartLife();
	static StatisticsPlayer& getStatisticsPlayer(int id);
	void saveToFile(string filename);
};

