#include "ModelIdHolder.h"

ModelIdHolder::ModelIdHolder()
{
	for(int i = 0; i < MAX_IDS; i++)
	{
		m_textures[i] = "color";
		m_hatIds[i] = "";
		m_rightHandIds[i] = "";
		m_leftHandIds[i] = "";
		m_glowmaps[i] = "";
	}

	this->m_modelId[0] = "Char1_5";
	
	this->m_modelId[2] = "PoisonTurret";
	this->m_modelId[3] = "LightningTurret";
	this->m_modelId[4] = "DeathTurret";
	this->m_modelId[5] = "FrostTurret";
	this->m_modelId[6] = "CloudOfDarkness";
	this->m_modelId[7] = "Pentagram";
	this->m_modelId[8] = "redKnightPassiveAura";
	

	this->m_modelId[80] = "Imp"; //imp1
	this->m_modelId[81] = "Imp"; //imp2
	this->m_modelId[82] = "Imp"; //imp3
	this->m_modelId[83] = "Imp"; //imp4

	this->m_textures[80] = "color";
	this->m_textures[81] = "color1";
	this->m_textures[82] = "color2";
	this->m_textures[83] = "color3";

	this->m_glowmaps[80] = "glowIntensity";
	this->m_glowmaps[81] = "glowIntensity1";
	this->m_glowmaps[82] = "glowIntensity2";
	this->m_glowmaps[83] = "glowIntensity3";

	this->m_modelId[84] = "Beast";  
	this->m_modelId[85] = "Beast"; 
	this->m_modelId[86] = "Beast"; 
	this->m_modelId[87] = "Beast"; 

	this->m_textures[84] = "color";
	this->m_textures[85] = "color1";
	this->m_textures[86] = "color2";
	this->m_textures[87] = "color3";

	this->m_glowmaps[84] = "glowIntensity";
	this->m_glowmaps[85] = "glowIntensity1";
	this->m_glowmaps[86] = "glowIntensity2";
	this->m_glowmaps[87] = "glowIntensity3";

	this->m_modelId[95] = "Char1_5";
	this->m_modelId[96] = "Char1_5";
	this->m_modelId[97] = "Char1_5";
	this->m_modelId[98] = "Char1_5";
	this->m_modelId[99] = "Char1_5";
	this->m_hatIds[95] = "DECLHatt";
	this->m_hatIds[96] = "IronMan";
	this->m_hatIds[97] = "GasMask";
	this->m_hatIds[98] = "Kubb";
	this->m_hatIds[99] = "TopHat";
	this->m_rightHandIds[99] = "MentalistRapier";
	this->m_rightHandIds[97] = "Crossbow";
	this->m_textures[95] = "color";
	this->m_textures[96] = "color1";
	this->m_textures[97] = "color2";
	this->m_textures[98] = "color3";
	this->m_textures[99] = "color4";
}

std::string ModelIdHolder::getHat(unsigned int id)
{
	if(id < ModelIdHolder::MAX_IDS)
	{
		return this->m_hatIds[id];
	}
	else

	{
		return "";
	}
}

std::string ModelIdHolder::getRightHand(unsigned int id)
{
	if(id < ModelIdHolder::MAX_IDS)
	{
		return this->m_rightHandIds[id];
	}
	else

	{
		return "";
	}
}

std::string ModelIdHolder::getLeftHand(unsigned int id)
{
	if(id < ModelIdHolder::MAX_IDS)
	{
		return this->m_leftHandIds[id];
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
		return this->m_modelId[id];
	}
	else

	{
		return "";
	}
}

std::string ModelIdHolder::getTexture(int _index)const
{
	return m_textures[_index];
}

std::string ModelIdHolder::getGlowmap(int _index)const
{
	return m_glowmaps[_index];
}