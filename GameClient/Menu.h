#pragma once
#include "Button.h"
#include "GraphicsHandler.h"
#include "DataStructures.h"

#include <vector>

using namespace std;
static bool ChangeState;
extern GraphicsHandler* g_graphicsEngine;

class Menu
{
public:
	Menu();
	~Menu();

	static enum WorldState 
	{
		Main, Create, Join, Lore, Settings, Credits, Exit, Lobby, Loading, InGame, Score
	};
protected:
	vector<Button*>			m_Buttons;
	vector<Sprite*>			m_Images;
	vector<Text*>			m_text;
	vector<SpriteSheet*>	m_Sprite;
	void Init();
	void Update();
};
