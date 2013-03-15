#include "SkillIdHolder.h"

SkillIdHolder::SkillIdHolder()
{
	//Textures
	this->m_SkillId[Skill::TURRET_CONSTRUCTION] = "menu_textures\\Button-Skill-0.png";
	this->m_SkillId[Skill::TURRET_DAMAGE] = "menu_textures\\Button-Skill-12.png";
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
	this->m_SkillId[Skill::READY_AIM_FIRE] = "menu_textures\\Button-Skill-26.png";
	this->m_SkillId[Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE] = "menu_textures\\Button-Skill-25.png";
	this->m_SkillId[Skill::TIME_IS_MONEY] = "menu_textures\\Button-Skill-27.png";
	this->m_SkillId[Skill::ENHANCED_DEVELOPMENT] = "menu_textures\\Button-Skill-28.png";
	this->m_SkillId[Skill::LIFE_REGEN] = "menu_textures\\Button-Skill-29.png";
	this->m_SkillId[Skill::HYPNOTIC_STARE] = "menu_textures\\Button-Skill-21.png";

	this->m_SkillId[Skill::TESLA_CHAIN_TURRET] = "menu_textures\\Upgradebar_Buy_Tower_Tesla.png";
	this->m_SkillId[Skill::DEATH_PULSE_TURRET] = "menu_textures\\Upgradebar_Buy_Tower_Death.png";
	this->m_SkillId[Skill::POISON_TURRET] = "menu_textures\\Upgradebar_Buy_Tower_Poison.png";
	this->m_SkillId[Skill::FROST_TURRET] = "menu_textures\\Upgradebar_Buy_Tower_Frost.png";

	//Active
	this->m_skillActive[Skill::TURRET_CONSTRUCTION] = false;
	this->m_skillActive[Skill::TURRET_DAMAGE] = false;
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
	this->m_skillActive[Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE] = true;
	this->m_skillActive[Skill::TIME_IS_MONEY] = true;
	this->m_skillActive[Skill::ENHANCED_DEVELOPMENT] = false;
	this->m_skillActive[Skill::LIFE_REGEN] = false;
	this->m_skillActive[Skill::HYPNOTIC_STARE] = true;

	this->m_skillActive[Skill::TESLA_CHAIN_TURRET] = true;
	this->m_skillActive[Skill::DEATH_PULSE_TURRET] = true;
	this->m_skillActive[Skill::POISON_TURRET] = true;
	this->m_skillActive[Skill::FROST_TURRET] = true;

	//Description
	this->m_skillDescription[Skill::TURRET_CONSTRUCTION] = "menu_textures\\Skill_0.png";
	this->m_skillDescription[Skill::TURRET_DAMAGE] = "menu_textures\\Skill_1.png";
	this->m_skillDescription[Skill::STRENGTH] = "menu_textures\\Skill_2.png";
	this->m_skillDescription[Skill::PHYSICAL_RESISTANCE] = "menu_textures\\Skill_3.png";
	this->m_skillDescription[Skill::LIFESTEALING_STRIKE] = "menu_textures\\Skill_4.png";
	this->m_skillDescription[Skill::STUNNING_STRIKE] = "menu_textures\\Skill_5.png";
	this->m_skillDescription[Skill::DEMONIC_PRESENCE] = "menu_textures\\Skill_6.png";
	this->m_skillDescription[Skill::AGILITY] = "menu_textures\\Skill_7.png";
	this->m_skillDescription[Skill::TELEPORT] ="menu_textures\\Skill_8.png";
	this->m_skillDescription[Skill::AIM] ="menu_textures\\Skill_9.png";
	this->m_skillDescription[Skill::DEADLY_STRIKE] ="menu_textures\\Skill_10.png";
	this->m_skillDescription[Skill::WITS] = "menu_textures\\Skill_11.png";
	this->m_skillDescription[Skill::POISON_STRIKE] = "menu_textures\\Skill_12.png";
	this->m_skillDescription[Skill::HEALING_TOUCH] = "menu_textures\\Skill_19.png";
	this->m_skillDescription[Skill::CHAIN_STRIKE] = "menu_textures\\Skill_13.png";
	this->m_skillDescription[Skill::CLOUD_OF_DARKNESS] = "menu_textures\\Skill_14.png";
	this->m_skillDescription[Skill::FORTITUDE] = "menu_textures\\Skill_16.png";
	this->m_skillDescription[Skill::GREED] = "menu_textures\\Skill_17.png";
	this->m_skillDescription[Skill::MENTAL_RESISTANCE] = "menu_textures\\Skill_18.png";
	this->m_skillDescription[Skill::WALL] ="menu_textures\\Skill_20.png"; 
	this->m_skillDescription[Skill::SIMONS_EVIL] = "menu_textures\\Skill_15.png";
	this->m_skillDescription[Skill::ENIGMATIC_PRESENCE] = "menu_textures\\Skill_22.png";
	this->m_skillDescription[Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR] = "menu_textures\\Skill_23.png";
	this->m_skillDescription[Skill::COURAGE_HONOR_VALOR] = "menu_textures\\Skill_24.png";
	this->m_skillDescription[Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE] = "menu_textures\\Skill_25.png";
	this->m_skillDescription[Skill::READY_AIM_FIRE] = "menu_textures\\Skill_26.png";
	this->m_skillDescription[Skill::TIME_IS_MONEY] = "menu_textures\\Skill_27.png";
	this->m_skillDescription[Skill::ENHANCED_DEVELOPMENT] = "menu_textures\\Skill_28.png";
	this->m_skillDescription[Skill::LIFE_REGEN] = "menu_textures\\Skill_29.png";
	this->m_skillDescription[Skill::HYPNOTIC_STARE] = "menu_textures\\Skill_21.png";
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