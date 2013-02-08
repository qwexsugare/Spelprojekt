#ifndef SKILL_ID_HOLDER_H
#define SKILL_ID_HOLDER_H

#include <string>
#include "Skill.h"

class SkillIdHolder
{
private:
	std::string m_SkillId[100];
public:
	SkillIdHolder();
	std::string getSkill(unsigned int id);
	unsigned int getNrOfIds();
};

#endif