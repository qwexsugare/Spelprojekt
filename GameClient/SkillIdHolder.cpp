#include "SkillIdHolder.h"

SkillIdHolder::SkillIdHolder()
{
	this->m_SkillId[Skill::TOWER] = "menu_textures\\Button-Skill-0.png";
	this->m_SkillId[Skill::TURRET_LIFE] = "menu_textures\\Button-Skill-12.png";
	this->m_SkillId[Skill::STRENGTH] = "menu_textures\\Button-Skill-1.png";
	this->m_SkillId[Skill::PHYSICAL_RESISTANCE] = "menu_textures\\Button-Skill-7.png";
	this->m_SkillId[Skill::LIFESTEALING_STRIKE] = "menu_textures\\Button-Skill-9.png";
	this->m_SkillId[Skill::STUNNING_STRIKE] = "menu_textures\\Button-Skill-13.png";
	this->m_SkillId[Skill::DEMONIC_PRESENCE] = "menu_textures\\Button-Skill-16.png";
	this->m_SkillId[Skill::AGILITY] = "menu_textures\\Button-Skill-2.png";
	this->m_SkillId[Skill::TELEPORT] = "menu_textures\\Button-Skill-18.png";
	this->m_SkillId[Skill::AIM] = "menu_textures\\Button-Skill-5.png";
	this->m_SkillId[Skill::DEADLY_STRIKE] = "menu_textures\\Button-Skill-11.png";
	this->m_SkillId[Skill::WITS] = "menu_textures\\Button-Skill-3.png";
	this->m_SkillId[Skill::POISON_STRIKE] = "menu_textures\\Button-Skill-10.png";
	this->m_SkillId[Skill::HEALING_TOUCH] = "menu_textures\\Button-Skill-19.png";
	this->m_SkillId[Skill::CHAIN_STRIKE] = "menu_textures\\Button-Skill-14.png";
	this->m_SkillId[Skill::CLOUD_OF_DARKNESS] = "menu_textures\\Button-Skill-17.png";
	this->m_SkillId[Skill::FORTITUDE] = "menu_textures\\Button-Skill-4.png";
	this->m_SkillId[Skill::GREED] = "menu_textures\\Button-Skill-6.png";
	this->m_SkillId[Skill::MENTAL_RESISTANCE] = "menu_textures\\Button-Skill-8.png";
	this->m_SkillId[Skill::WALL] = "menu_textures\\Button-Skill-20.png";
	
	this->m_SkillId[Skill::SIMONS_EVIL] = "menu_textures\\Button-Skill-29.png";
	this->m_SkillId[Skill::ENIGMATIC_PRESENCE] = "menu_textures\\Button-Skill-20.png";
	this->m_SkillId[Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR] = "menu_textures\\Button-Skill-20.png";
	this->m_SkillId[Skill::COURAGE_HONOR_VALOR] = "menu_textures\\Button-Skill-20.png";
	this->m_SkillId[Skill::READY_AIM_FIRE] = "menu_textures\\Button-Skill-20.png";
	this->m_SkillId[Skill::TIME_IS_MONEY] = "menu_textures\\Button-Skill-20.png";
	this->m_SkillId[Skill::ENHANCED_DEVELOPMENT] = "menu_textures\\Button-Skill-20.png";
	this->m_SkillId[Skill::LIFE_REGAIN] = "menu_textures\\Button-Skill-20.png";
}

std::string SkillIdHolder::getSkill(unsigned int id)
{
	if(id < 100)
	{
		return this->m_SkillId[id];
	}
	else

	{
		return "";
	}
}

unsigned int SkillIdHolder::getNrOfIds()
{
	return 100;
}