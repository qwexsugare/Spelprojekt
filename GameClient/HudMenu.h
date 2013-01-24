#pragma once
#include "menu.h"
#include "TextLabel.h"
#include "TextInput.h"
#include "Input.h"

class HudMenu :
	public Menu
{
public:
	HudMenu(void);
	~HudMenu(void);

	void Update(float _dt);
	int ButtonClicked();
	int SkilledBougth();
	int ReturnID();
private:
	int		m_Time, 
			m_NumberOfSkills, 
			m_SkillValue, 
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
			m_Buy_Tower,
			m_Buy_Strength,
			m_Buy_Agility,
			m_Buy_Wits,
			m_Buy_Fortitude,
			m_Menu,
			m_First,
			m_First_Tower, 
			m_First_Strength,
			m_First_Agility, 
			m_First_Wits, 
			m_First_Fortitude, 
			m_Locked,
			m_Init_All,
			m_Init_Tower,
			m_Init_Strength,
			m_Init_Agility,
			m_Init_Wits,
			m_Init_Fortitude,
			m_OncePerBuy,
			m_Chat;
	TextInput* m_LabelInput;
	vector<TextLabel*> m_Chattext;	
	vector<Button*> BuyButtonTower;
	vector<Button*> BuyButtonStrength;
	vector<Button*> BuyButtonAgility;
	vector<Button*> BuyButtonWits;
	vector<Button*> BuyButtonFortitude;
	vector<Button*> BuyAttributes;

	bool LockIsDown();
	bool MenuIsDown();

	bool BuyTowerSkillIsDown();
	bool BuyStrengthSkillIsDown();
	bool BuyAgilitySkillIsDown();
	bool BuyWitsSkillIsDown();
	bool BuyFortitudeSkillIsDown();
	bool BuyAllSkillIsDown();

	void BuyHud();
	void UpdateShop();
	void UnInit(int _Type);

};

