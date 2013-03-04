#ifndef MODEL_ID_HOLDER_H
#define MODEL_ID_HOLDER_H

#include <string>

class ModelIdHolder
{
public:
	static const int MAX_IDS = 100;
	enum WEAPON_TYPE{NO_WEAPON, RANGED, MELEE, AOE};
private:
	struct WeaponSet
	{
		std::string leftHand;
		std::string rightHand;

		WeaponSet(std::string rightHand = "", std::string leftHand = "")
		{
			this->leftHand = leftHand;
			this->rightHand = rightHand;
		}
	};

	struct ModelId
	{
		std::string model;
		std::string hat;
		std::string textures;
		std::string glowMap;
		WeaponSet weapons[4];

		ModelId()
		{
			this->model = "";
			this->hat = "";
			this->textures = "color";
			this->glowMap = "";
		}

		ModelId(std::string model, std::string textures = "color", std::string glowMap = "", std::string hat = "")
		{
			this->model = model;
			this->hat = hat;
			this->textures = textures;
			this->glowMap = glowMap;
		}
	};
	
	ModelId m_modelIds[MAX_IDS];
public:
	ModelIdHolder();
	std::string getHat(unsigned int id);
	std::string getRightHand(unsigned int id, unsigned short weaponType);
	std::string getLeftHand(unsigned int id, unsigned short weaponType);
	std::string getModel(unsigned int id);
	std::string getTexture(int _index)const;
	std::string getGlowmap(int _index)const;
};

#endif