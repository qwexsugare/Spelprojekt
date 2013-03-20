#pragma once
#include "menu.h"
#include "TextLabel.h"
#include "TextInput.h"
#include "Hero.h"
#include "Slider.h"
#include "SkillIdHolder.h"

class LobbyMenu :
	public Menu
{
public:
	LobbyMenu(bool _host);
	~LobbyMenu();

	void Update(float _dt, bool _mayPressReady);

	bool ChatIsDown();
	bool StoreIsDown();
	bool MainMenuIsDown();
	bool CharacterInformationIsDown();
	bool LevelInformationIsDown();
	bool StartGameIsDown();
	bool RangeCombatIsDown();
	bool CloseCombatIsDown();

	bool Character0IsDown();
	bool Character1IsDown();
	bool Character2IsDown();
	bool Character3IsDown();
	bool Character4IsDown();
	bool enterPressed;
	Slider* getSlider(){return &this->m_slider;}

	void selectHero(int _playerIndex, Hero::HERO_TYPE _type, bool changeText);
	int getCombat();
	void setPlayerName(int _playerIndex, string _name, bool changeText);
	void setReady(int _playerIndex);
	Hero::HERO_TYPE* getHeroesSelected(){return this->m_currentSelections;};
	void addStringToChat(string t);
	void removePlayer(int _playerIndex);
	void resetEnterPressed();
	bool wasEnterPressed();
	string getChatString();
	void updateMapInfo(string level, string mapsize, string nrwaves, string demoncoins);
private:
	bool m_host;
	Hero::HERO_TYPE m_currentSelections[4];
	Sprite* m_doctorPortrait;
	Sprite* m_officerPortrait;
	Sprite* m_engineerPortrait;
	Sprite* m_redKnightPortrait;
	Sprite* m_mentalistPortrait;
	Sprite* miniMap1;
	Sprite* miniMap2;

	Sprite* m_doctorPortrait2;
	Sprite* m_officerPortrait2;
	Sprite* m_engineerPortrait2;
	Sprite* m_redKnightPortrait2;
	Sprite* m_mentalistPortrait2;
	map<int, TextLabel*> m_playerNames;
	Slider m_slider;
	SkillIdHolder m_skillHolder;
	TextInput* m_LabelInput;
	vector<TextLabel*> m_Label;
	vector<TextLabel*> m_Chattext;
	bool m_Character0,
		 m_Character1,
		 m_Character2,
		 m_Character3,
		 m_Character4;
	int m_Counter,
		m_Combat;
	string m_String;
	
};

