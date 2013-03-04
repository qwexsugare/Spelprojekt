#ifndef SKILL_ID_HOLDER_H
#define SKILL_ID_HOLDER_H

#include <string>
#include "Skill.h"

class SkillIdHolder
{
private:
	std::string m_SkillId[100];
	std::string m_skillDescription[100];
	bool m_skillActive[100];
public:
	SkillIdHolder();
	std::string getSkill(unsigned int id);
	std::string getDescription(unsigned int id);
	bool getActive(unsigned int id);
	unsigned int getNrOfIds();
};

#endif