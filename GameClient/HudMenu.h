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

class HudMenu :
	public Menu
{
public:
	HudMenu(Client *_network);
	~HudMenu(void);

	void Update(float _dt, const vector<Entity*>& _entities);
	int ButtonClicked();
	int SkilledBougth();
	int ReturnID();

	void addSkill(unsigned int _skillId);
	void setResources(unsigned int resources);
private:
	SkillIdHolder m_skillHolder;
	Client *m_network;
	int		m_Time, 
			m_NumberOfSkills, 
			m_DelayTime, 
			m_Delay,
			m_Change,
			m_Resources,
			m_LoseMoney;

	int		button_0,
			button_1,
			button_2,
			button_3,
			button_4,
			button_5,
			SkillID;
	float	m_SkillHud;

	bool	m_DontChange,
			m_Buy,
			m_Menu,
			m_First,
			m_Locked,
			m_OncePerBuy,
			m_Chat;
	TextInput* m_LabelInput;
	vector<TextLabel*> m_Chattext;	
	TextLabel* m_ResourceLabel;	

	bool m_canAfford[20];
	bool m_shopVisible;
	vector<Button*> m_shopButtons;
	vector<Button*> m_disabledShopButtons;
	vector<Button*> m_resourceImages;
	vector<Sprite*> m_shopBackground;

	bool LockIsDown();
	bool MenuIsDown();

	bool BuyAllSkillIsDown();

	void BuyHud();
	void UpdateShop();
	void UnInit(int _Type);

	void displayShop(bool _visible);
};

