#include "ModelIdHolder.h"

ModelIdHolder::ModelIdHolder()
{
	this->m_modelId[0] = "Beast1_5";
	this->m_modelId[1] = "egg";
	this->m_modelId[2] = "PoisonTurret";
	this->m_modelId[3] = "LightningTurret";
	this->m_modelId[4] = "DeathTurret";
	this->m_modelId[5] = "FrostTurret";
	this->m_modelId[6] = "CloudOfDarkness";
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