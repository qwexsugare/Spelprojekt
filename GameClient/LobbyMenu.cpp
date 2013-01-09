#include "LobbyMenu.h"


LobbyMenu::LobbyMenu(void)
{
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LobbyMenu-Background.dds", FLOAT2(0,0),  FLOAT2(2,2),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LobbyMenu-Middleground.dds", FLOAT2(0,0), FLOAT2(2,2),1));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LobbyMenu-Foreground.dds", FLOAT2(0,0), FLOAT2(2,2),4));

	this->m_Buttons.resize(12);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.729166667f,  0.051851852f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-Chat.dds","",0,0,2);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.729166667f,  -0.111111111f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-Store.dds","",0,0,2);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(-0.729166667f,  -0.274074074f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.dds","",0,0,2);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(0.729166667f,  0.051851852f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-CharacterInformation.dds","",0,0,2);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(0.729166667f,  -0.111111111f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-LevelInformation.dds","",0,0,2);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(0.729166667f,  -0.274074074f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-Ready.dds","",0,0,2);
	this->m_Buttons[6] = new Button();
	this->m_Buttons[6]->Init(FLOAT2(0.375f,  -0.518518519f),FLOAT2(0.076041667f,0.135185185f),"menu_textures\\Button-LobbyMenu-CloseCombat.dds","",0,0,2);
	this->m_Buttons[7] = new Button();
	this->m_Buttons[7]->Init(FLOAT2(0.708333333f,  -0.518518519f),FLOAT2(0.076041667f,0.135185185f),"menu_textures\\Button-LobbyMenu-RangeCombat.dds","",0,0,2);
	
	// Player buttons
	this->m_Buttons[8] = new Button();
	this->m_Buttons[8]->Init(FLOAT2(0.729166667f,  0.611111111f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-Player1.dds","",0,0,1);
	this->m_Buttons[9] = new Button();
	this->m_Buttons[9]->Init(FLOAT2(0.729166667f, 0.481481481f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-Player2.dds","",0,0,1);
	this->m_Buttons[10] = new Button();
	this->m_Buttons[10]->Init(FLOAT2(0.729166667f,  0.351851852f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-Player3.dds","",0,0,1);
	this->m_Buttons[11] = new Button();
	this->m_Buttons[11]->Init(FLOAT2(0.729166667f,  0.222222222f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-Player4.dds","",0,0,1);

}


LobbyMenu::~LobbyMenu(void)
{

}
void LobbyMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
}

bool LobbyMenu::ChatIsDown()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::StoreIsDown()
{
	if(this->m_Buttons[1]->Clicked()== 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::MainMenuIsDown()
{
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::CharacterInformationIsDown()
{
	if(this->m_Buttons[3]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::LevelInformationIsDown()
{
	if(this->m_Buttons[4]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::StartGameIsDown()
{
	if(this->m_Buttons[5]->Clicked()== 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::RangeCombatIsDown()
{
	if(this->m_Buttons[6]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::CloseCombatIsDown()
{
	if(this->m_Buttons[7]->Clicked()== 1)
	{
		return true;
	}
	return false;
}
