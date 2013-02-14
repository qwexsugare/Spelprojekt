#include "ModelIdHolder.h"

ModelIdHolder::ModelIdHolder()
{
	for(int i = 0; i < MAX_IDS; i++)
	{
		m_textures[i] = "color";
	}

	this->m_modelId[0] = "Char1_5";
	this->m_modelId[1] = "Beast1_5";
	this->m_modelId[2] = "PoisonTurret";
	this->m_modelId[3] = "LightningTurret";
	this->m_modelId[4] = "DeathTurret";
	this->m_modelId[5] = "FrostTurret";
	this->m_modelId[6] = "CloudOfDarkness";
	this->m_modelId[7] = "Pentagram";
	this->m_modelId[8] = "redKnightPassiveAura";
	
	this->m_modelId[95] = "Char1_5";
	this->m_modelId[96] = "Char1_5";
	this->m_modelId[97] = "Char1_5";
	this->m_modelId[98] = "Char1_5";
	this->m_modelId[99] = "Char1_5";
	
	this->m_textures[95] = "color";
	this->m_textures[96] = "color1";
	this->m_textures[97] = "color2";
	this->m_textures[98] = "color3";
	this->m_textures[99] = "color4";
}

std::string ModelIdHolder::getModel(unsigned int id)
{
	if(id < 100)
	{
		return this->m_modelId[id];
	}
	else

	{
		return "";
	}
}

unsigned int ModelIdHolder::getNrOfIds()
{
	return 100;
}

std::string ModelIdHolder::getTexture(int _index)const
{
	return m_textures[_index];
}