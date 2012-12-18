#pragma once
#include "Menu.h"
class LobbyMenu : Menu
{
public:
	LobbyMenu();
	~LobbyMenu();

	void Init();
	void Update();
	void ChangeStates();
	bool ChatIsDown();
	bool StoreIsDone();
	bool MainMenuIsDone();
	bool CharacterInformationIsDone();
	bool LevelInformationIsDone();
	bool StartGameIsDone();
	bool RangeCombatIsDone();
	bool CloseCombatIsDone();

};

