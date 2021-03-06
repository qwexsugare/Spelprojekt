#pragma once
#include "menu.h"
#include "TextInput.h"
#include "TextLabel.h"

class CreateGameMenu :
	public Menu
{
public:
	CreateGameMenu(void);
	~CreateGameMenu(void);

	void Update(float _dt);
	bool StartGameIsDown();
	bool MainMenuGameIsDown();
	bool MainWriteGameIsDown();
	bool MainWriteIPIsDown();
	bool MainWriteNameIsDown();
	bool LevelOneIsDown();
	bool LevelTwoIsDown();
	string getIP();
	string getPort();
	string getPlayerName();
	void savePlayerName();
	string getChoseLevel();
private:
	string choseLevel;
	vector<TextInput*> m_Label;
	TextLabel* m_IPLabel;
	bool	m_WriteIP,
			m_WriteName,
			m_WriteGame;
	float	m_changePosY;
	float	m_fontsize;
	string	m_graphicstext;
};

