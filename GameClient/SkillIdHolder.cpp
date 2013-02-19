#include "SkillIdHolder.h"

SkillIdHolder::SkillIdHolder()
{
	//Textures
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
	this->m_SkillId[Skill::SIMONS_EVIL] = "menu_textures\\Button-Skill-15.png";
	this->m_SkillId[Skill::ENIGMATIC_PRESENCE] = "menu_textures\\Button-Skill-22.png";
	this->m_SkillId[Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR] = "menu_textures\\Button-Skill-23.png";
	this->m_SkillId[Skill::COURAGE_HONOR_VALOR] = "menu_textures\\Button-Skill-24.png";
	this->m_SkillId[Skill::READY_AIM_FIRE] = "menu_textures\\Button-Skill-20.png";
	this->m_SkillId[Skill::TIME_IS_MONEY] = "menu_textures\\Button-Skill-20.png";
	this->m_SkillId[Skill::ENHANCED_DEVELOPMENT] = "menu_textures\\Button-Skill-20.png";
	this->m_SkillId[Skill::LIFE_REGEN] = "menu_textures\\Button-Skill-29.png";

	//Active
	this->m_skillActive[Skill::TOWER] = false;
	this->m_skillActive[Skill::TURRET_LIFE] = false;
	this->m_skillActive[Skill::STRENGTH] = false;
	this->m_skillActive[Skill::PHYSICAL_RESISTANCE] = false;
	this->m_skillActive[Skill::LIFESTEALING_STRIKE] = false;
	this->m_skillActive[Skill::STUNNING_STRIKE] = true;
	this->m_skillActive[Skill::DEMONIC_PRESENCE] = true;
	this->m_skillActive[Skill::AGILITY] = false;
	this->m_skillActive[Skill::TELEPORT] = true;
	this->m_skillActive[Skill::AIM] = false;
	this->m_skillActive[Skill::DEADLY_STRIKE] = false;
	this->m_skillActive[Skill::WITS] = false;
	this->m_skillActive[Skill::POISON_STRIKE] = false;
	this->m_skillActive[Skill::HEALING_TOUCH] = true;
	this->m_skillActive[Skill::CHAIN_STRIKE] = true;
	this->m_skillActive[Skill::CLOUD_OF_DARKNESS] = true;
	this->m_skillActive[Skill::FORTITUDE] = false;
	this->m_skillActive[Skill::GREED] = false;
	this->m_skillActive[Skill::MENTAL_RESISTANCE] = false;
	this->m_skillActive[Skill::WALL] = true;	
	this->m_skillActive[Skill::SIMONS_EVIL] = true;
	this->m_skillActive[Skill::ENIGMATIC_PRESENCE] = false;
	this->m_skillActive[Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR] = true;
	this->m_skillActive[Skill::COURAGE_HONOR_VALOR] = false;
	this->m_skillActive[Skill::READY_AIM_FIRE] = false;
	this->m_skillActive[Skill::TIME_IS_MONEY] = false;
	this->m_skillActive[Skill::ENHANCED_DEVELOPMENT] = true;
	this->m_skillActive[Skill::LIFE_REGEN] = false;

	//Description
	this->m_skillDescription[Skill::TOWER] = "";
	this->m_skillDescription[Skill::TURRET_LIFE] = "";
	this->m_skillDescription[Skill::STRENGTH] = "";
	this->m_skillDescription[Skill::PHYSICAL_RESISTANCE] = "";
	this->m_skillDescription[Skill::LIFESTEALING_STRIKE] = "";
	this->m_skillDescription[Skill::STUNNING_STRIKE] = "";
	this->m_skillDescription[Skill::DEMONIC_PRESENCE] = "";
	this->m_skillDescription[Skill::AGILITY] = "";
	this->m_skillDescription[Skill::TELEPORT] ="";
	this->m_skillDescription[Skill::AIM] ="";
	this->m_skillDescription[Skill::DEADLY_STRIKE] ="";
	this->m_skillDescription[Skill::WITS] = "";
	this->m_skillDescription[Skill::POISON_STRIKE] = "";
	this->m_skillDescription[Skill::HEALING_TOUCH] = "";
	this->m_skillDescription[Skill::CHAIN_STRIKE] = "";
	this->m_skillDescription[Skill::CLOUD_OF_DARKNESS] = "";
	this->m_skillDescription[Skill::FORTITUDE] = "";
	this->m_skillDescription[Skill::GREED] = "";
	this->m_skillDescription[Skill::MENTAL_RESISTANCE] = "";
	this->m_skillDescription[Skill::WALL] = "";
	this->m_skillDescription[Skill::SIMONS_EVIL] = "";
	this->m_skillDescription[Skill::ENIGMATIC_PRESENCE] = "";
	this->m_skillDescription[Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR] = "";
	this->m_skillDescription[Skill::COURAGE_HONOR_VALOR] = "";
	this->m_skillDescription[Skill::READY_AIM_FIRE] = "";
	this->m_skillDescription[Skill::TIME_IS_MONEY] = "";
	this->m_skillDescription[Skill::ENHANCED_DEVELOPMENT] = "";
	this->m_skillDescription[Skill::LIFE_REGEN] = "";
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

std::string SkillIdHolder::getDescription(unsigned int id)
{
	if(id < 100)
	{
		return this->m_skillDescription[id];
	}
	else

	{
		return "";
	}
}

bool SkillIdHolder::getActive(unsigned int id)
{
	if(id < 100)
	{
		return this->m_skillActive[id];
	}
	else

	{
		return false;
	}
}

unsigned int SkillIdHolder::getNrOfIds()
{
	return 100;
}