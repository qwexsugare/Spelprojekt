#pragma once
#include "menu.h"
#include "TextInput.h"
class JoinGameMenu :
	public Menu
{
public:
	JoinGameMenu(void);
	~JoinGameMenu(void);

	void Update(float _dt);
	bool StartGameIsDown();
	bool MainMenuGameIsDown();
	bool MainWriteGameIsDown();
	bool MainWriteIPIsDown();
	bool MainWriteNameIsDown();

	string getIP();
	string getPort();
	string getPlayerName();

private:
	vector<TextInput*> m_Label;
	bool	m_WriteIP,
			m_WriteName,
			m_WriteGame;
};

