#pragma once
#include "menu.h"
class LobbyMenu :
	public Menu
{
public:
	LobbyMenu(void);
	~LobbyMenu(void);

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

