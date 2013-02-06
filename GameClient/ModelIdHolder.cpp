#include "ModelIdHolder.h"

ModelIdHolder::ModelIdHolder()
{
	this->m_modelId[0] = "Test";
	this->m_modelId[1] = "Beast1_5";
	this->m_modelId[2] = "egg";
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