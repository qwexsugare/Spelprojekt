#pragma once
#include "menu.h"
#include "TextLabel.h"
#include "TextInput.h"
#include "Input.h"
#include "client.h"
#include "Skill.h"
#include <sstream>
#include "Entity.h"
#include "SkillIdHolder.h"
#include "Sprite.h"
#include "ModelIdHolder.h"
#include "Enemy.h"

class HudMenu : public Menu
{
private:
	unsigned int m_currentTargetEnemyId;
	bool m_hasTargetEnemy;
	map<Enemy::EnemyType, Sprite*> m_enemyIcons;
	SkillIdHolder m_skillHolder;
	Client *m_network;
	int	m_NumberOfSkills;
	int m_Resources;

	vector<float>	m_SkillHud;

	bool	m_Buy,
			m_Menu,
			m_Locked,
			m_Chat;

	vector<bool>	m_DontChange;

	TextInput* m_LabelInput;
	vector<TextLabel*> m_Chattext;	
	TextLabel* m_ResourceLabel;

	SpriteSheet *m_healthBar;
	vector<Sprite*> m_LabelSprite;
	FLOAT2 m_fullHealthPos;
	vector<string> m_Attributes;
	TextLabel*	m_AttributeText;
	TextLabel* m_waveText;
	TextLabel* m_livesRemaining;
	bool m_canAfford[20];
	bool m_shopVisible;
	int m_nrOfAttributesBought;
	vector<Button*> m_shopButtons;
	vector<Button*> m_disabledShopButtons;
	vector<Button*> m_resourceImages;
	vector<Sprite*> m_shopBackground;

	int m_skillWaitingForTarget;
	int m_buttonIndex;

	vector<Button*> m_towerButtons;
	bool m_placingTower;
	int m_towerId;
	Model* m_towerModel;
	Model* m_subTowerModel; // for frost turret base.

	int m_strength;
	int m_agility;
	int m_wits;
	int m_fortitude;
	int m_towerConstruction;

	bool LockIsDown();
	bool MenuIsDown();

	bool BuyAllSkillIsDown();

	void BuyHud();
	void UpdateShop();
	void UnInit(int _Type);

	void displayShop(bool _visible);
public:
	HudMenu(Client *_network, Hero::HERO_TYPE _heroType);
	~HudMenu(void);

	void Update(float _dt, const vector<Entity*>& _entities, unsigned int _heroId);

	void addSkill(unsigned int _skillId);
	void removeTargetEnemy();
	void setResources(unsigned int resources);
	void skillUsed(unsigned int index, unsigned int actionId, float cooldown);
	void setHealth(float health);
	void setLivesRemaining(int livesRemaing);
	void setTargetEnemy(unsigned int _currentTargetEnemyId);
	void setStrength(int _strength);
	void setAgility(int _agility);
	void setWits(int _wits);
	void setFortitude(int _fortitude);
	void setTowerConstruction(int _towerConstruction);
	void setWave(int _wave);
};

