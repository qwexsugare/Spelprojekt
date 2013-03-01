#include "Statistics.h"

double Statistics::timePlayed;
int Statistics::isAtWave;
int Statistics::startLife;
StatisticsPlayer Statistics::sPlayers[4];

Statistics::Statistics(void)
{
	this->startLife=10;
	this->timePlayed=0.0;
	this->isAtWave=0;
}


Statistics::~Statistics(void)
{
}

void Statistics::setStartLife(int l)
{
	Statistics::startLife=l;
}
void Statistics::decreaseStartLife()
{
	Statistics::startLife--;
}
void Statistics::addTime(float f)
{
	Statistics::timePlayed+=f;
}
void Statistics::waveFinnished()
{
	Statistics::startLife++;
}
StatisticsPlayer& Statistics::getStatisticsPlayer(int id)
{
	return Statistics::sPlayers[id];
}
void Statistics::saveToFile(string filename)
{
	ofstream file;
	file.open(filename.c_str());
	if(file.is_open())
	{
		file <<"Life remaining: " <<  this->startLife;
		file.close();
	}
}