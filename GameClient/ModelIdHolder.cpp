#include "ModelIdHolder.h"

ModelIdHolder::ModelIdHolder()
{
	this->m_modelIds[0] = ModelId("Char");
	this->m_modelIds[2] = ModelId("PoisonTurret", "color", "glowIntensity");
	this->m_modelIds[3] = ModelId("LightningTurret", "color", "glowIntensity");
	this->m_modelIds[4] = ModelId("DeathTurret", "color", "glowIntensity");
	this->m_modelIds[5] = ModelId("FrostGun", "color", "glowIntensity");
	this->m_modelIds[6] = ModelId("FrostBase");
	this->m_modelIds[7] = ModelId("CloudOfDarkness");
	this->m_modelIds[8] = ModelId("Pentagram");
	this->m_modelIds[9] = ModelId("redKnightPassiveAura");
	this->m_modelIds[10] = ModelId("wall");

	this->m_modelIds[80] = ModelId("Imp", "color", "glowIntensity"); //Frost demon
	this->m_modelIds[81] = ModelId("Imp", "color1", "glowIntensity1"); //Imp
	this->m_modelIds[82] = ModelId("Imp", "color2", "glowIntensity2"); //Shade
	this->m_modelIds[83] = ModelId("Imp", "color3", "glowIntensity3"); //Spitting
	
	this->m_modelIds[84] = ModelId("Beast", "color", "glowIntensity"); //Soul Eater
	this->m_modelIds[85] = ModelId("Beast", "color1", "glowIntensity1"); //Brute 
	this->m_modelIds[86] = ModelId("Beast", "color2", "glowIntensity2"); //Hellfire
	this->m_modelIds[87] = ModelId("Beast", "color3", "glowIntensity3"); //Thunder

	this->m_modelIds[95] = ModelId("Char", "color", "", "DECLHatt"); //Officer
	this->m_modelIds[96] = ModelId("Char", "color1", "", "IronMan"); //Red Knight
	this->m_modelIds[97] = ModelId("Char", "color2", "", "GasMask"); //Engineer
	this->m_modelIds[98] = ModelId("Char", "color3", "", "Kubb");  //Doctor
	this->m_modelIds[99] = ModelId("Char", "color4", "", "TopHat"); //Mentalist

	//Officer
	this->m_modelIds[95].weapons[WEAPON_TYPE::MELEE] = WeaponSet("OfficerRapier", "lantern");
	this->m_modelIds[95].weapons[WEAPON_TYPE::RANGED] = WeaponSet("HexaGun", "lantern");

	//Red Knight
	this->m_modelIds[96].weapons[WEAPON_TYPE::MELEE] = WeaponSet("Sword", "lantern");
	this->m_modelIds[96].weapons[WEAPON_TYPE::AOE] = WeaponSet("Mace", "");

	//Engineer
	this->m_modelIds[97].weapons[WEAPON_TYPE::MELEE] = WeaponSet("Wrench", "lantern");
	this->m_modelIds[97].weapons[WEAPON_TYPE::RANGED] = WeaponSet("Crossbow", "lantern");

	//Doctor
	this->m_modelIds[98].weapons[WEAPON_TYPE::MELEE] = WeaponSet("MeatClever", "lantern");
	this->m_modelIds[98].weapons[WEAPON_TYPE::RANGED] = WeaponSet("DoctorRevolver", "lantern");

	//Mentalist
	this->m_modelIds[99].weapons[WEAPON_TYPE::MELEE] = WeaponSet("MentalistRapier", "lantern");
	this->m_modelIds[99].weapons[WEAPON_TYPE::RANGED] = WeaponSet("MentalistRevolver", "lantern");
}

std::string ModelIdHolder::getHat(unsigned int id)
{
	if(id < ModelIdHolder::MAX_IDS)
	{
		return this->m_modelIds[id].hat;
	}
	else

	{
		return "";
	}
}

std::string ModelIdHolder::getRightHand(unsigned int id, unsigned short weaponType)
{
	if(id < ModelIdHolder::MAX_IDS && weaponType < 4)
	{
		return this->m_modelIds[id].weapons[weaponType].rightHand;
	}
	else
	{
		return "";
	}
}

std::string ModelIdHolder::getLeftHand(unsigned int id, unsigned short weaponType)
{
	if(id < ModelIdHolder::MAX_IDS && weaponType < 4)
	{
		return this->m_modelIds[id].weapons[weaponType].leftHand;
	}
	else
	{
		return "";
	}
}

std::string ModelIdHolder::getModel(unsigned int id)
{
	if(id < ModelIdHolder::MAX_IDS)
	{
		return this->m_modelIds[id].model;
	}
	else

	{
		return "";
	}
}

std::string ModelIdHolder::getTexture(int _index)const
{
	if(_index < ModelIdHolder::MAX_IDS)
	{
		return this->m_modelIds[_index].textures;
	}
	else

	{
		return "";
	}
}

std::string ModelIdHolder::getGlowmap(int _index)const
{
	if(_index < ModelIdHolder::MAX_IDS)
	{
		return this->m_modelIds[_index].glowMap;
	}
	else

	{
		return "";
	}
}