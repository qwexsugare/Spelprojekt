#include "Statistics.h"

double Statistics::timePlayed;
int Statistics::isAtWave;
int Statistics::startLife;
StatisticsPlayer Statistics::sPlayers[MAXPLAYERS];

Statistics::Statistics(void)
{
	this->startLife=10;
	this->timePlayed=0.0;
	this->isAtWave=1;
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
	Statistics::isAtWave++;
}
int Statistics::convertSimonsIdToRealId(int id)
{
	int trueId=-1;
	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(Statistics::sPlayers[i].getPlayerId()==id)
			trueId=i;
		i=MAXPLAYERS;
	}
	return trueId;
}
StatisticsPlayer& Statistics::getStatisticsPlayer(int id)
{
	return Statistics::sPlayers[id];
}
void Statistics::saveToFile(string filename)
{
	//converts the hero types to strings
	string heroTypes[5]={"Officer","Red knight","Engineer","Doctor","Mentalist"};
	ofstream file;
	file.open(filename.c_str());
	if(file.is_open())
	{
		file << "Game statistics: " << endl;
		file << "----------------"<<endl;
		file << "Time played: " << Statistics::timePlayed<<endl;
		file << "Life remaining: " <<  Statistics::startLife<<endl;
		file << "Reached wave: " << Statistics::isAtWave<<endl<<endl;
		file << "Player Statistics:" << endl;
		file << "------------------"<<endl;

		for(int i=0;i<MAXPLAYERS;i++)
		{
			if(Statistics::sPlayers[i].getPlayerId()!=-1)
			{
				file << "Player name: " << Statistics::sPlayers[i].getPlayerName()<<endl;
				file << "Hero played: " << heroTypes[Statistics::sPlayers[i].getPlayerHero()]<<endl;
				file << "Deamons killed: " << Statistics::sPlayers[i].getDeamonsKilled()<<endl;
				file << "Player deaths: " << Statistics::sPlayers[i].getDeathCount()<<endl;
				file << "Resources collected: " << Statistics::sPlayers[i].getGoldCollected()<<endl;
				file << "Healed for: " << Statistics::sPlayers[i].getHealedAmount()<<endl<<endl;

				file << "Damage statistics: " << endl;
				file << "Total damage dealt: " << Statistics::sPlayers[i].getPhysicalDamageDealth() + Statistics::sPlayers[i].getMentalDamageDealth() + Statistics::sPlayers[i].getSkillPhysicalDamageDealth() + Statistics::sPlayers[i].getSkillMentalDamageDealth()<<endl;
				file << "Physical damage taken: " << Statistics::sPlayers[i].getPhysicalDamageRecived() << endl;
				file << "Mental damage taken: " << Statistics::sPlayers[i].getMentalDamageRecived() << endl;
				file << "Physical damage dealt: " << Statistics::sPlayers[i].getPhysicalDamageDealth()<<endl;
				file << "Mental damage dealt: " << Statistics::sPlayers[i].getMentalDamageDealth() << endl;
				file << "Physical skill damage dealt: " << Statistics::sPlayers[i].getSkillPhysicalDamageDealth()<<endl;
				file << "Mental skill damage dealt: " << Statistics::sPlayers[i].getSkillMentalDamageDealth() << endl<<endl;

				file << "Skills used: " << endl;
				for(int i=0;i<Skill::SKILLS::NR_OF_SKILLS;i++)
				{
					file << Statistics::sPlayers[i].getNrOfTimesSkillUsed(i)<<endl;
				}
				file << "---------------" << endl;
			}
		}

		file.close();
	}

		static double timePlayed;
	static int isAtWave;
	static int startLife;
	static StatisticsPlayer sPlayers[MAXPLAYERS];
}

double Statistics::getTimePlayed()
{
	return Statistics::timePlayed;
}

int Statistics::getIsAtWave()
{
	return Statistics::isAtWave;
}

int Statistics::getStartLife()
{
	return Statistics::startLife;
}
void Statistics::resetStatistics()
{
	for(int i=0;i<MAXPLAYERS;i++)
	{
		Statistics::sPlayers[i].resetPlayer();
	}
}