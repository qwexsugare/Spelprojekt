#ifndef MODEL_ID_HOLDER_H
#define MODEL_ID_HOLDER_H

#include <string>

class ModelIdHolder
{
public:
	static const int MAX_IDS = 100;
private:
	std::string m_modelId[MAX_IDS];
	std::string m_hatIds[MAX_IDS];
	std::string m_rightHandIds[MAX_IDS];
	std::string m_leftHandIds[MAX_IDS];
	std::string m_textures[MAX_IDS];
	std::string m_glowmaps[MAX_IDS];
public:
	ModelIdHolder();
	std::string getHat(unsigned int id);
	std::string getRightHand(unsigned int id);
	std::string getLeftHand(unsigned int id);
	std::string getModel(unsigned int id);
	std::string getTexture(int _index)const;
	std::string getGlowmap(int _index)const;
};

#endif