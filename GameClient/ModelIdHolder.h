#ifndef MODEL_ID_HOLDER_H
#define MODEL_ID_HOLDER_H

#include <string>

class ModelIdHolder
{
public:
	static const int MAX_IDS = 100;
private:
	std::string m_modelId[MAX_IDS];
	std::string m_textures[MAX_IDS];
public:
	ModelIdHolder();
	std::string getModel(unsigned int id);
	unsigned int getNrOfIds();
	std::string getTexture(int _index)const;
};

#endif