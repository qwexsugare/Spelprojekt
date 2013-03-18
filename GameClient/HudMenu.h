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
#include "PlayerInfo.h"

class HudMenu : public Menu
{
private:
	bool m_done;
	Button* m_menuButton;
	Button* m_leaveButton;
	unsigned int m_currentTargetEnemyId;
	bool m_hasTargetEnemy;
	Enemy::EnemyType m_currentTargetType;
	map<Enemy::EnemyType, Sprite*> m_enemyIcons;
	Sprite* m_heroPortraits[5];
	SkillIdHolder m_skillHolder;
	Client *m_network;
	int	m_NumberOfSkills;
	int m_Resources;
	int m_health;
	int m_maxHealth;

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
	vector<TextLabel*>	m_AttributeText;
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

	bool m_placingTargetedSkill;
	Model* m_targetModel;
	Hero::HERO_TYPE m_heroType;
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
	HudMenu(Client *_network, Hero::HERO_TYPE _heroType, vector<PLAYER_INFO> m_playerInfos);
	~HudMenu(void);

	bool isDone()const;
	void Update(float _dt, const vector<Entity*>& _entities, unsigned int _heroId, vector<PLAYER_INFO> m_playerInfos);
	void addSkill(unsigned int _skillId);
	void removeTargetEnemy();
	void setResources(unsigned int resources);
	void skillUsed(unsigned int index, unsigned int actionId, float cooldown);
	void setHealth(int _health);
	void setMaxHealth(int _maxHealth);
	void setLivesRemaining(int livesRemaing);
	void setTargetEnemy(unsigned int _currentTargetEnemyId);
	void setStrength(int _strength);
	void setAgility(int _agility);
	void setWits(int _wits);
	void setFortitude(int _fortitude);
	void setMentalDamage(int _md);
	void setMentalResistance(float _mr);
	void setPhysicalDamage(int _pd);
	void setPhysicalResistance(float _pr);
	void setTowerConstruction(int _towerConstruction);
	void setWave(int _wave);
};

