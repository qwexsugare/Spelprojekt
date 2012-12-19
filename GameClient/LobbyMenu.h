#pragma once
#include "Menu.h"
class LobbyMenu : Menu
{
public:
	LobbyMenu();
	~LobbyMenu();

	void Init();
	void Update();

	bool ChatIsDown();
	bool StoreIsDown();
	bool MainMenuIsDown();
	bool CharacterInformationIsDown();
	bool LevelInformationIsDown();
	bool StartGameIsDown();
	bool RangeCombatIsDown();
	bool CloseCombatIsDown();

};

