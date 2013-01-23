#pragma once
#include "menu.h"
#include "TextLabel.h"
#include "TextInput.h"

class LobbyMenu :
	public Menu
{
public:
	LobbyMenu(void);
	~LobbyMenu(void);

	void Update(float _dt);

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
private:
	TextInput* m_LabelInput;
	vector<TextLabel*> m_Label;
	vector<TextLabel*> m_Chattext;
	bool m_Character0,
		 m_Character1,
		 m_Character2,
		 m_Character3,
		 m_Character4;
	int m_Counter;
	string m_String;

};

