#include "LoreMenu.h"
#include "TextLabel.h"
#include "SoundWrapper.h"
LoreMenu::LoreMenu(void)
{
	ThisPage = 0;
	Change = false;
	m_Play = false;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-0.png", FLOAT2(0,0),  FLOAT2(2,2),0));
	this->m_Reading.push_back(createSoundHandle("lorebook/Introduction.wav", false, false));
	this->m_Reading.push_back(createSoundHandle("lorebook/Gathering.wav", false, false));
	this->m_Reading.push_back(createSoundHandle("lorebook/TheWorld.wav", false, false));
	this->m_Buttons.resize(4);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(0.33f,-0.933333333f),FLOAT2(0.053125f,0.103703704f),"menu_textures\\Arrow-Right.png","",0,0,2);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.33f,-0.933333333f),FLOAT2(0.053125f,0.103703704f),"menu_textures\\Arrow-Left.png","",0,0,2);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(0.15f,-0.933333333f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,2);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(-0.15f,-0.933333333f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-ReadLore.png","",0,0,2);


}
void LoreMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
	if ( ThisPage == 0)
	{
		if(ReadLoreIsDown())
		{
			m_Play = true;
			playSound(m_Reading[0]);
		}
		if (!isSoundPlaying(m_Reading[0]) && m_Play == true)
		{
			playSound(m_Reading[1]);
			m_Play = false;
		}
	}
	if ( ThisPage == 1)
	{
		if(ReadLoreIsDown())
		{
			playSound(m_Reading[2]);
		}
	}

	ChangeStates();
}
bool LoreMenu::Plus()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LoreMenu::Minus()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LoreMenu::MainMenuIsDown()
{
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LoreMenu::ReadLoreIsDown()
{
	if(this->m_Buttons[3]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
void LoreMenu::ChangeStates()
{
	if(Plus())
	{
		ThisPage += 1;
		Change = true;
		m_Play = false;
		if (ThisPage > 16)
		{
			ThisPage = 0;
		}
		for(int i = 0; i < m_Reading.size();i++)
		{
			stopSound(m_Reading[i]);
		}

	}
	else if(Minus())
	{
		ThisPage -= 1;
		Change = true;
		m_Play = false;
		if(ThisPage < 0)
		{
			ThisPage = 16;
		}
		for(int i = 0; i < m_Reading.size();i++)
		{
			stopSound(m_Reading[i]);
		}
	}

	if (Change == true)
	{
		if(ThisPage != 0 && ThisPage != 1)
		{
			m_Buttons[3]->setVisible(false);
			m_Buttons[3]->setKeep(1);
		}
		else
		{
			m_Buttons[3]->setVisible(true);
			m_Buttons[3]->setKeep(0);
		}

		stringstream ss;
		ss << ThisPage;

		g_graphicsEngine->removeSprite( m_Images[0]);
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-" +ss.str()+ ".png", FLOAT2(0,0),  FLOAT2(2,2),0));
	}
	Change = false;
}

LoreMenu::~LoreMenu(void)
{
	for(int i = 0; i < m_Reading.size();i++)
	{
		stopSound(m_Reading[i]);
	}
	for (int i = 0; i < m_Reading.size();i++)
	{
		deactivateSound(m_Reading[i]);
	}
}
