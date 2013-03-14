#include "LobbyMenu.h"
#include "Input.h"

LobbyMenu::LobbyMenu(void)
{
	enterPressed=false;
	m_Counter = 0;
	m_Character0 = false;
	m_Character1 = false;
	m_Character2 = false;
	m_Character3 = false;
	m_Character4 = false;
	m_String = "";
	m_Combat = 2;
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-CharacterMenu-Background2.png", FLOAT2(0,0),  FLOAT2(2,2),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-CharacterMenu-Middleground.png", FLOAT2(0,0), FLOAT2(2,2),1));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LobbyMenu-Foreground.dds", FLOAT2(0,0), FLOAT2(2,2),4));
	FLOAT2 m_size, m_side; 
	m_size.x = 0;
	m_size.y = 0;
	m_side.x = 0;
	m_side.y = 0;
	m_size.x = 1920;
	m_size.y = 1080;
	m_side.x = (122.0f/m_size.x)*2.0f;
	m_side.y = (1920.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.png", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),3));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.png", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),3));
	m_side.x = (1920.0f/m_size.x)*2.0f;
	m_side.y = (122.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.png", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),4));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.png", FLOAT2(0,-0.89f),  FLOAT2(-m_side.x,m_side.y),4));
	
	this->m_Buttons.resize(12);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.140625f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-Chat.png","",0,0,2,5);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.28125f*1.5f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-Store.png","",0,0,2,5);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(0.28125f*2.5f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,2,5);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(0.140625f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-CharacterInformation.png","",0,0,2,5);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(0.28125f*1.5f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-LevelInformation.png","",0,0,2,5);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(-0.28125f*2.5f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-Ready.png","",0,0,2,5);
	
	this->m_Buttons[0]->setVisible(false);
	this->m_Buttons[1]->setVisible(false);
	this->m_Buttons[3]->setVisible(false);
	this->m_Buttons[4]->setVisible(false);

	this->m_Buttons[6] = new Button();
	this->m_Buttons[6]->Init(FLOAT2(-0.8f, -0.1f),FLOAT2(0.15625f*0.8f,0.277777778f*0.8f),"","",0,0,2,25);
	this->m_Buttons[7] = new Button();
	this->m_Buttons[7]->Init(FLOAT2(-0.65f, -0.1f),FLOAT2(0.15625f*0.8f,0.277777778f*0.8f),"","",0,0,2,25);

	// Player stuff
	/*this->m_Buttons[8] = new Button();
	this->m_Buttons[8]->Init(FLOAT2(-0.30f,-0.27f),FLOAT2(0.272916667f*0.5f,0.142592593f*0.5f),"menu_textures\\Button-LobbyMenu-Player1.dds","",0,0,1);
	this->m_Buttons[9] = new Button();
	this->m_Buttons[9]->Init(FLOAT2(-0.10f,-0.27f),FLOAT2(0.272916667f*0.5f,0.142592593f*0.5f),"menu_textures\\Button-LobbyMenu-Player2.dds","",0,0,1);
	this->m_Buttons[10] = new Button();
	this->m_Buttons[10]->Init(FLOAT2(0.10f,-0.27f),FLOAT2(0.272916667f*0.5f,0.142592593f*0.5f),"menu_textures\\Button-LobbyMenu-Player3.dds","",0,0,1);
	this->m_Buttons[11] = new Button();
	this->m_Buttons[11]->Init(FLOAT2(0.30f,-0.27f),FLOAT2(0.272916667f*0.5f,0.142592593f*0.5f),"menu_textures\\Button-LobbyMenu-Player4.dds","",0,0,1);*/
	this->m_Buttons[8] = new Button();
	this->m_Buttons[8]->Init(FLOAT2(0.675f, 0.2f),FLOAT2(0.272916667f*0.5f,0.142592593f*0.5f),"menu_textures\\Button-LobbyMenu-Player1.dds","",0,0,1);
	this->m_Buttons[9] = new Button();
	this->m_Buttons[9]->Init(FLOAT2(0.8f, 0.2f),FLOAT2(0.272916667f*0.5f,0.142592593f*0.5f),"menu_textures\\Button-LobbyMenu-Player2.dds","",0,0,1);
	this->m_Buttons[10] = new Button();
	this->m_Buttons[10]->Init(FLOAT2(0.675f, -0.2f),FLOAT2(0.272916667f*0.5f,0.142592593f*0.5f),"menu_textures\\Button-LobbyMenu-Player3.dds","",0,0,1);
	this->m_Buttons[11] = new Button();
	this->m_Buttons[11]->Init(FLOAT2(0.8f, -0.2f),FLOAT2(0.272916667f*0.5f,0.142592593f*0.5f),"menu_textures\\Button-LobbyMenu-Player4.dds","",0,0,1);
	m_doctorPortrait = g_graphicsEngine->createSprite("menu_textures/Character-4.png", FLOAT2(0.0f, 0.0f), FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f), 18);
	m_officerPortrait = g_graphicsEngine->createSprite("menu_textures/Character-1.png", FLOAT2(0.0f, 0.0f), FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f), 18);
	m_engineerPortrait = g_graphicsEngine->createSprite("menu_textures/Character-3.png", FLOAT2(0.0f, 0.0f), FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f), 18);
	m_redKnightPortrait = g_graphicsEngine->createSprite("menu_textures/Character-2.png", FLOAT2(0.0f, 0.0f), FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f), 18);
	m_mentalistPortrait = g_graphicsEngine->createSprite("menu_textures/Character-0.png", FLOAT2(0.0f, 0.0f), FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f), 18);
	m_doctorPortrait->setVisible(false);
	m_officerPortrait->setVisible(false);
	m_engineerPortrait->setVisible(false);
	m_redKnightPortrait->setVisible(false);
	m_mentalistPortrait->setVisible(false);
	m_currentSelections[0] = Hero::HERO_TYPE::NONE;
	m_currentSelections[1] = Hero::HERO_TYPE::NONE;
	m_currentSelections[2] = Hero::HERO_TYPE::NONE;
	m_currentSelections[3] = Hero::HERO_TYPE::NONE;
	
	/*this->m_Buttons[12] = new Button();
	this->m_Buttons[12]->Init(FLOAT2(-0.445f,  0.73f),FLOAT2(0.178125f*0.5f,0.194444444f*0.5f),"menu_textures\\CharacterMenu-Button-Officer.png","",0,0,1);
	this->m_Buttons[13] = new Button();
	this->m_Buttons[13]->Init(FLOAT2(-0.22f, 0.73f),FLOAT2(0.178125f*0.5f,0.194444444f*0.5f),"menu_textures\\CharacterMenu-Button-RedKnight.png","",0,0,1);
	this->m_Buttons[14] = new Button();
	this->m_Buttons[14]->Init(FLOAT2(0.0f,  0.73f),FLOAT2(0.178125f*0.5f,0.194444444f*0.5f),"menu_textures\\CharacterMenu-Button-Engineer.png","",0,0,1);
	this->m_Buttons[15] = new Button();
	this->m_Buttons[15]->Init(FLOAT2(0.22f,  0.73f),FLOAT2(0.178125f*0.5f,0.194444444f*0.5f),"menu_textures\\CharacterMenu-Button-Doctor.png","",0,0,1);
	this->m_Buttons[16] = new Button();
	this->m_Buttons[16]->Init(FLOAT2(0.445f,  0.73f),FLOAT2(0.178125f*0.5f,0.194444444f*0.5f),"menu_textures\\CharacterMenu-Button-Mentalist.png","",0,0,1);*/


	
	this->m_slider.Init(FLOAT2(-0.5f, -0.30f), 0.0f, FLOAT2(0.2f,0.2f),"menu_textures\\LobbyMenuSlider.png","", 0.0f, 1.0f, 1, 15);

	this->m_Label.resize(5);
	this->m_Label[0] = new TextLabel("","text2.png",INT2(130,205),75);
	this->m_Label[1] = new TextLabel("","text2.png",INT2(130,830),60);
	this->m_Label[2] = new TextLabel("","text3.png",INT2(130,150),100);
	this->m_Label[3] = new TextLabel("","text4.png",INT2(130,500),75);
	this->m_LabelInput = new TextInput("text3.png",INT2(1100,1010),80);
	this->m_Chattext.resize(6);
	this->m_Chattext[0] = new TextLabel("","text2.png",INT2(1100,950),60);
	this->m_Chattext[1] = new TextLabel("","text2.png",INT2(1100,920),60);
	this->m_Chattext[2] = new TextLabel("","text2.png",INT2(1100,890),60);
	this->m_Chattext[3] = new TextLabel("","text2.png",INT2(1100,860),60);
	this->m_Chattext[4] = new TextLabel("","text2.png",INT2(1100,830),60);
	this->m_Chattext[5] = new TextLabel("","text2.png",INT2(1100,800),60);
	this->m_Label[3]->setText("Close combat_Selected");
	this->m_Buttons[6]->SetTextBoxValue(true);
	this->m_Buttons[7]->SetTextBoxValue(false);
}


LobbyMenu::~LobbyMenu(void)
{
	for(int i=0 ; i < this->m_Label.size();i++)
	{
		delete this->m_Label[i];
		this->m_Label[i] = NULL;
	}
	delete this->m_LabelInput;
	for(int i=0 ; i < this->m_Chattext.size();i++)
	{
		delete this->m_Chattext[i];
		this->m_Chattext[i] = NULL;
	}
	g_graphicsEngine->removeSprite(m_doctorPortrait);
	g_graphicsEngine->removeSprite(m_mentalistPortrait);
	g_graphicsEngine->removeSprite(m_officerPortrait);
	g_graphicsEngine->removeSprite(m_redKnightPortrait);
	g_graphicsEngine->removeSprite(m_engineerPortrait);
	for(int i = 0; i < m_playerNames.size(); i++)
	{
		delete m_playerNames[i];
	}
}

void LobbyMenu::addStringToChat(string t)
{
	for(int i = m_Chattext.size()-1; i > 0;i--)
		{
			m_Chattext[i]->setText(m_Chattext[i-1]->getText());
		}
		this->m_Chattext[0]->setText(t);
			
}
void LobbyMenu::resetEnterPressed()
{
	this->enterPressed=false;
}
bool LobbyMenu::wasEnterPressed()
{
	return this->enterPressed;
}
string LobbyMenu::getChatString()
{
	return this->m_String;
}
void LobbyMenu::Update(float _dt)
{
	int Change = 0;
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
	if(Character0IsDown())
	{
		Change = 1;
		m_Character0 = true;
		m_Character1 = false;
		m_Character2 = false;
		m_Character3 = false;
		m_Character4 = false;
		this->m_Buttons[6]->setTexture("menu_textures\\O0.png");
		this->m_Buttons[7]->setTexture("menu_textures\\O1.png");
		if (m_Combat == 1)
		{
			this->m_Label[3]->setText("Range combat_Selected");
		}

	}
	if(Character1IsDown())
	{
		Change = 1;
		m_Character0 = false;
		m_Character1 = true;
		m_Character2 = false;
		m_Character3 = false;
		m_Character4 = false;
		this->m_Buttons[6]->setTexture("menu_textures\\R0.png");
		this->m_Buttons[7]->setTexture("menu_textures\\R1.png");
		this->m_Label[3]->setText("Close combat_Selected");
		if (m_Combat == 1)
		{
			this->m_Label[3]->setText("Close combat_Selected");
		}
	}
	if(Character2IsDown())
	{
		Change = 1;
		m_Character0 = false;
		m_Character1 = false;
		m_Character2 = true;
		m_Character3 = false;
		m_Character4 = false;
		this->m_Buttons[6]->setTexture("menu_textures\\E0.png");
		this->m_Buttons[7]->setTexture("menu_textures\\E1.png");
		if (m_Combat == 1)
		{
			this->m_Label[3]->setText("Range combat_Selected");
		}
	}
	if(Character3IsDown())
	{
		Change = 1;
		m_Character0 = false;
		m_Character1 = false;
		m_Character2 = false;
		m_Character3 = true;
		m_Character4 = false;
		this->m_Buttons[6]->setTexture("menu_textures\\D0.png");
		this->m_Buttons[7]->setTexture("menu_textures\\D1.png");
		if (m_Combat == 1)
		{
			this->m_Label[3]->setText("Range combat_Selected");
		}
	}
	if(Character4IsDown())
	{
		Change = 1;
		m_Character0 = false;
		m_Character1 = false;
		m_Character2 = false;
		m_Character3 = false;
		m_Character4 = true;
		this->m_Buttons[6]->setTexture("menu_textures\\M0.png");
		this->m_Buttons[7]->setTexture("menu_textures\\M1.png");
		if (m_Combat == 1)
		{
			this->m_Label[3]->setText("Range combat_Selected");
		}
	}
	this->m_LabelInput->update(_dt);
	//if the enter key is pressed, the string is saved
	if(g_keyboard->getKeyState(VK_RETURN) == Keyboard::KEY_PRESSED)
	{
			m_String = this->m_LabelInput->getText();
			m_String.erase(m_String.end());
			this->m_LabelInput->setText(""); 
			this->m_Chattext[5]->setText("");
			enterPressed=true;
	}
	
	//this->m_Label[3]->setText(m_String);
	if(m_Combat == 0)
	{
		if(m_Character0 == false && m_Character1 == false && m_Character2 == false && m_Character3 == false && m_Character4 == false)
		{
			this->m_Label[3]->setText("");
			this->m_Label[2]->setText("Select Character");
			this->m_Label[0]->setText("");
			this->m_Label[1]->setText("Welcome to the Asylum! The smell of burning flesh, Haunts my dreams It is time to face my demons_and leave this horrible place once and for all. This is my time to shine Lets kill som demons!");
		}
		else
		{
			this->m_Label[3]->setText("Select Weapontype");
		}
	}
	if(CloseCombatIsDown() && m_Combat == 2)
	{
		this->m_Label[3]->setText("Close combat_Selected");
		this->m_Buttons[6]->SetTextBoxValue(true);
		this->m_Buttons[7]->SetTextBoxValue(false);
	}
	if(RangeCombatIsDown() && m_Combat == 1 && m_Character1 != true)
	{
		this->m_Label[3]->setText("Range combat_Selected");
		this->m_Buttons[6]->SetTextBoxValue(false);
		this->m_Buttons[7]->SetTextBoxValue(true);
	}
	if(RangeCombatIsDown() && m_Combat == 1 && m_Character1 == true)
	{
		this->m_Label[3]->setText("Close combat_Selected");
		this->m_Buttons[6]->SetTextBoxValue(false);
		this->m_Buttons[7]->SetTextBoxValue(true);
	}


	if(Change == 1)
	{
		if (m_Character0 == true)
		{
			this->m_Label[2]->setText("Officer");
			this->m_Label[0]->setText("Strength: 3_Agility: 5_Wits: 1_Fortitude: 3__Weapon:_Rapier_Hexagun_________Story:_____Skills:");
			this->m_Label[1]->setText("A captain of the Royal Airship Brigade, the officer is now commissioned to take charge against the siege_that has befallen Chevington. His leadership skills are a true assets to the brave men and women_stationed in the towers and siege weapons and his skill with blade and rifle makes him a true plague_upon anyone standing in his way.___Active: Target acquired, permission to fire!_Passive: Ready, aim, fire!");
			this->m_Buttons[6]->setTexture("menu_textures\\O0.png");
			this->m_Buttons[7]->setTexture("menu_textures\\O1.png");
			if (m_Combat == 1)
			{
				this->m_Label[3]->setText("Range combat_Selected");
			}
		}
		if (m_Character1 == true)
		{
			this->m_Label[2]->setText("Red Knight");
			this->m_Label[0]->setText("Strength: 5_Agility: 2_Wits: 1_Fortitude: 4__Weapon:_Bastardsword_Twohanded Warhammer_________Story:_____Skills:");
			this->m_Label[1]->setText("In a city where steam and cogs are the pinnacle of modern civilization, the ancient order of Sword and_Shield wielding knights seem a bit superfluous, but they are fierce warriors and good men. Whenever Dark_Powers show their ugly face, the Red Knights descend upon them without mercy. This particular_Knight is a paragon of his order and instills courage in his comrades as he strikes down enemy after enemy.___Active: Swift as a cat, powerful as a bear_Passive: Courage,Honor,Valor");
			this->m_Buttons[6]->setTexture("menu_textures\\R0.png");
			this->m_Buttons[7]->setTexture("menu_textures\\R1.png");
			this->m_Label[3]->setText("Close combat_Selected");
			if (m_Combat == 1)
			{
				this->m_Label[3]->setText("Close combat_Selected");
			}
		}
		if (m_Character2 == true)
		{
			this->m_Label[2]->setText("Engineer");
			this->m_Label[0]->setText("Strength: 3_Agility: 3_Wits: 5_Fortitude: 1__Weapon:_Gigantic Wrench_Steampowered Crossbow_________Story:_____Skills:");
			this->m_Label[1]->setText("HEJ JAG R MAD!");
			this->m_Buttons[6]->setTexture("menu_textures\\E0.png");
			this->m_Buttons[7]->setTexture("menu_textures\\E1.png");
			if (m_Combat == 1)
			{
				this->m_Label[3]->setText("Range combat_Selected");
			}
		}
		if (m_Character3 == true)
		{
			this->m_Label[2]->setText("Doctor");
			this->m_Label[0]->setText("Strength: 1_Agility: 3_Wits: 5_Fortitude: 3__Weapon:_Cleaver_Pistol_________Story:_____Skills:");
			this->m_Label[1]->setText("A master of surgery, medicine and the art of healing, the Doctor is not only wanted, but needed on the field_of battle. Not only skilled in healing his allies and bringing their spirits back, but also gifted with the_ability to poison his enemies, making them weaker and easier to kill, he is a force to be reckoned with_and not a man you would want to cross.___Active: Healing aura_Passive: Life regain");
			this->m_Buttons[6]->setTexture("menu_textures\\D0.png");
			this->m_Buttons[7]->setTexture("menu_textures\\D1.png");
			if (m_Combat == 1)
			{
				this->m_Label[3]->setText("Range combat_Selected");
			}
		}
		if (m_Character4 == true)
		{
			this->m_Label[2]->setText("Mentalist");
			this->m_Label[0]->setText("Strength: 1_Agility: 4_Wits: 5_Fortitude: 2__Weapon:_Rapier_Pistol_________Story:_____Skills:");
			this->m_Label[1]->setText("The Mentalist is an enigmatic, charming character with the stunning ability to know more about you than_you do yourself. Some say he is a charlatan, other think it is real magic. Whichever is true,_it is clear that The Mentalist can do incredible things to your mind, often without you even noticing._Be glad he is on your side.___Active: Hypnotic stare_Passive: Enigmatic Presence");
			this->m_Buttons[6]->setTexture("menu_textures\\M0.png");
			this->m_Buttons[7]->setTexture("menu_textures\\M1.png");
			if (m_Combat == 1)
			{
				this->m_Label[3]->setText("Range combat_Selected");
			}
		}
	}
	m_slider.Update();
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
		this->m_Buttons[5]->SetTextBoxValue(true);
		return true;
	}
	return false;
}
bool LobbyMenu::CloseCombatIsDown()
{
	if(this->m_Buttons[6]->Clicked()== 1)
	{
		m_Combat = 2;
		return true;
	}
	return false;
}
bool LobbyMenu::RangeCombatIsDown()
{
	if(this->m_Buttons[7]->Clicked() == 1)
	{
		m_Combat = 1;
		return true;
	}
	return false;
}

int LobbyMenu::getCombat()
{
	return this->m_Combat;
}

bool LobbyMenu::Character0IsDown()
{
	/*if(this->m_Buttons[12]->Clicked() == 1)
	{
		m_Character0 = true;
		m_Character1 = false;
		m_Character2 = false;
		m_Character3 = false;
		m_Character4 = false;
		return true;
	}
	return false;*/

	//return m_Buttons[12]->isClicked();

	return false;
}

bool LobbyMenu::Character1IsDown()
{
	/*if(this->m_Buttons[13]->Clicked() == 1)
	{
		m_Character0 = false;
		m_Character1 = true;
		m_Character2 = false;
		m_Character3 = false;
		m_Character4 = false;
		return true;
	}
	return false;*/

	//return m_Buttons[13]->isClicked();

	return false;
}
bool LobbyMenu::Character2IsDown()
{
	/*if(this->m_Buttons[14]->Clicked()== 1)
	{
		m_Character0 = false;
		m_Character1 = false;
		m_Character2 = true;
		m_Character3 = false;
		m_Character4 = false;
		return true;
	}
	return false;*/

	//return m_Buttons[14]->isClicked();

	return false;
}
bool LobbyMenu::Character3IsDown()
{
	/*if(this->m_Buttons[15]->Clicked() == 1)
	{
		m_Character0 = false;
		m_Character1 = false;
		m_Character2 = false;
		m_Character3 = true;
		m_Character4 = false;
		return true;
	}
	return false;*/

	//return m_Buttons[15]->isClicked();

	return false;
}
bool LobbyMenu::Character4IsDown()
{
	/*if(this->m_Buttons[16]->Clicked()== 1)
	{
		m_Character0 = false;
		m_Character1 = false;
		m_Character2 = false;
		m_Character3 = false;
		m_Character4 = true;
		return true;
	}
	return false;*/

	//return m_Buttons[16]->isClicked();

	return false;
}

void LobbyMenu::selectHero(int _playerIndex, Hero::HERO_TYPE _type, bool changeText)
{
	FLOAT2 pos;
	int buttonIndex;

	switch(_playerIndex)
	{
	case 0:
		buttonIndex = 8;
		this->m_Buttons[8]->SetTextBoxValue(true);
		pos = m_Buttons[8]->getPos()+FLOAT2(0.0f, -0.15f);
		break;
	case 1:
		buttonIndex = 9;
		this->m_Buttons[9]->SetTextBoxValue(true);
		pos = m_Buttons[9]->getPos()+FLOAT2(0.0f, -0.15f);
		break;
	case 2:
		buttonIndex = 10;
		this->m_Buttons[10]->SetTextBoxValue(true);
		pos = m_Buttons[10]->getPos()+FLOAT2(0.0f, -0.15f);
		break;
	case 3:
		buttonIndex = 11;
		this->m_Buttons[11]->SetTextBoxValue(true);
		pos = m_Buttons[11]->getPos()+FLOAT2(0.0f, -0.15f);
		break;
	}

	switch(m_currentSelections[_playerIndex])
	{
	case Hero::OFFICER:
		m_officerPortrait->setVisible(false);
		break;
	case Hero::RED_KNIGHT:
		m_redKnightPortrait->setVisible(false);
		break;
	case Hero::ENGINEER:
		m_engineerPortrait->setVisible(false);
		break;
	case Hero::DOCTOR:
		m_doctorPortrait->setVisible(false);
		break;
	case Hero::THE_MENTALIST:
		m_mentalistPortrait->setVisible(false);
		break;
	}
	
	switch(_type)
	{
	case Hero::OFFICER:
		this->m_officerPortrait->setPosition(pos);
		this->m_officerPortrait->setVisible(true);
		if(changeText == true)
		{
			this->m_Label[2]->setText("Officer");
			this->m_Label[0]->setText("Strength: 3_Agility: 5_Wits: 1_Fortitude: 3__Weapon:_Rapier_Hexagun_________Story:_____Skills:");
			this->m_Label[1]->setText("A captain of the Royal Airship Brigade, the officer is now commissioned to take charge against the siege_that has befallen Chevington. His leadership skills are a true assets to the brave men and women_stationed in the towers and siege weapons and his skill with blade and rifle makes him a true plague_upon anyone standing in his way.___Active: Target acquired, permission to fire!_Passive: Ready, aim, fire!");
			this->m_Buttons[6]->setTexture("menu_textures\\O0.png");
			this->m_Buttons[7]->setTexture("menu_textures\\O1.png");
			if (m_Combat == 1)
			{
				this->m_Label[3]->setText("Range combat_Selected");
			}
		}
		break;
	case Hero::RED_KNIGHT:
		this->m_redKnightPortrait->setPosition(pos);
		this->m_redKnightPortrait->setVisible(true);
		if(changeText == true)
		{
			this->m_Label[2]->setText("Red Knight");
			this->m_Label[0]->setText("Strength: 5_Agility: 2_Wits: 1_Fortitude: 4__Weapon:_Bastardsword_Twohanded Warhammer_________Story:_____Skills:");
			this->m_Label[1]->setText("In a city where steam and cogs are the pinnacle of modern civilization, the ancient order of Sword and_Shield wielding knights seem a bit superfluous, but they are fierce warriors and good men. Whenever Dark_Powers show their ugly face, the Red Knights descend upon them without mercy. This particular_Knight is a paragon of his order and instills courage in his comrades as he strikes down enemy after enemy.___Active: Swift as a cat, powerful as a bear_Passive: Courage,Honor,Valor");
			this->m_Buttons[6]->setTexture("menu_textures\\R0.png");
			this->m_Buttons[7]->setTexture("menu_textures\\R1.png");
			this->m_Label[3]->setText("Close combat_Selected");
			if (m_Combat == 1)
			{
				this->m_Label[3]->setText("Close combat_Selected");
			}
		}
		break;
	case Hero::ENGINEER:
		this->m_engineerPortrait->setPosition(pos);
		this->m_engineerPortrait->setVisible(true);
		if(changeText == true)
		{
			this->m_Label[2]->setText("Engineer");
			this->m_Label[0]->setText("Strength: 3_Agility: 3_Wits: 5_Fortitude: 1__Weapon:_Gigantic Wrench_Steampowered Crossbow_________Story:_____Skills:");
			this->m_Label[1]->setText("Roland is Gay!");
			this->m_Buttons[6]->setTexture("menu_textures\\E0.png");
			this->m_Buttons[7]->setTexture("menu_textures\\E1.png");
			if (m_Combat == 1)
			{
				this->m_Label[3]->setText("Range combat_Selected");
			}
		}
		break;
	case Hero::DOCTOR:
		this->m_doctorPortrait->setPosition(pos);
		this->m_doctorPortrait->setVisible(true);
		if(changeText == true)
		{
			this->m_Label[2]->setText("Doctor");
			this->m_Label[0]->setText("Strength: 1_Agility: 3_Wits: 5_Fortitude: 3__Weapon:_Cleaver_Pistol_________Story:_____Skills:");
			this->m_Label[1]->setText("A master of surgery, medicine and the art of healing, the Doctor is not only wanted, but needed on the field_of battle. Not only skilled in healing his allies and bringing their spirits back, but also gifted with the_ability to poison his enemies, making them weaker and easier to kill, he is a force to be reckoned with_and not a man you would want to cross.___Active: Healing aura_Passive: Life regain");
			this->m_Buttons[6]->setTexture("menu_textures\\D0.png");
			this->m_Buttons[7]->setTexture("menu_textures\\D1.png");
			if (m_Combat == 1)
			{
				this->m_Label[3]->setText("Range combat_Selected");
			}
		}
		break;
	case Hero::THE_MENTALIST:
		this->m_mentalistPortrait->setPosition(pos);
		this->m_mentalistPortrait->setVisible(true);
		if(changeText == true)
		{
			this->m_Label[2]->setText("Mentalist");
			this->m_Label[0]->setText("Strength: 1_Agility: 4_Wits: 5_Fortitude: 2__Weapon:_Rapier_Pistol_________Story:_____Skills:");
			this->m_Label[1]->setText("The Mentalist is an enigmatic, charming character with the stunning ability to know more about you than_you do yourself. Some say he is a charlatan, other think it is real magic. Whichever is true,_it is clear that The Mentalist can do incredible things to your mind, often without you even noticing._Be glad he is on your side.___Active: Hypnotic stare_Passive: Enigmatic Presence");
			this->m_Buttons[6]->setTexture("menu_textures\\M0.png");
			this->m_Buttons[7]->setTexture("menu_textures\\M1.png");
			if (m_Combat == 1)
			{
				this->m_Label[3]->setText("Range combat_Selected");
			}
		}
		break;
	}
	
	m_currentSelections[_playerIndex] = _type;
}

void LobbyMenu::setPlayerName(int _playerIndex, string _name)
{
	INT2 pos;
	switch(_playerIndex)
	{
	case 0:
		//pos = INT2(0.675f, 0.2f);
		pos = INT2(1920/2.0f*0.675f + 1920/2.0f, 1080/2.0f - 1080/2.0f*0.2f);
		break;
	case 1:
		//pos = INT2(0.8f, 0.2f);
		pos = INT2(1920/2.0f*0.8f + 1920/2.0f, 1080/2.0f - 1080/2.0f*0.2f);
		break;
	case 2:
		//pos = INT2(0.675f, -0.2f);
		pos = INT2(1920/2.0f*0.675f + 1920/2.0f, 1080/2.0f - 1080/2.0f*(-0.2f));
		break;
	case 3:
		//pos = INT2(0.8f, -0.2f);
		pos = INT2(1920/2.0f*0.8f + 1920/2.0f, 1080/2.0f - 1080/2.0f*(-0.2f));
		break;
	}
	m_playerNames.push_back(new TextLabel(_name, "text2.png", pos, 50, true));
}