#include "ModelIdHolder.h"

ModelIdHolder::ModelIdHolder()
{
	this->m_modelId[0] = "Imp";
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