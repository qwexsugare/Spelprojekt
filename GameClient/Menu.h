#pragma once
#include "Button.h"
#include "Skill_Buttons.h"
#include "GraphicsHandler.h"
#include "DataStructures.h"

#include <vector>

using namespace std;

extern GraphicsHandler* g_graphicsEngine;

class Menu
{
public:
	Menu();
	~Menu();

protected:
	vector<Button*>			m_Buttons;
	vector<Skill_Buttons*>	m_SkillButtons;
	vector<Sprite*>			m_Images;
	vector<Text*>			m_text;
	vector<SpriteSheet*>	m_Sprite;
	void Init();
	void Update();
};
