#pragma once
#include "StatisticsPlayer.h"
#include "Skill.h"
#include <fstream>
#define MAXPLAYERS 4

class Statistics
{
private:
	static double timePlayed;
	static int isAtWave;
	static int startLife;
	//a player with id -1 means uninitilazed
	static StatisticsPlayer sPlayers[MAXPLAYERS];
public:
	Statistics(void);
	~Statistics(void);
	static void addTime(float t);
	static void waveFinnished();
	static void setStartLife(int l);
	static void decreaseStartLife();
	static StatisticsPlayer& getStatisticsPlayer(int id);
	static void saveToFile(string filename);
	static int convertSimonsIdToRealId(int id);
};

