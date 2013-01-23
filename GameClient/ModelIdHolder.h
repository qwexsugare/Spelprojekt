#ifndef MODEL_ID_HOLDER_H
#define MODEL_ID_HOLDER_H

#include <string>

class ModelIdHolder
{
private:
	std::string m_modelId[100];
public:
	ModelIdHolder();
	std::string getModel(unsigned int id);
	unsigned int getNrOfIds();
};

#endif