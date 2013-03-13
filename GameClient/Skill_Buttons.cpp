#include "Skill_Buttons.h"

Skill_Buttons::Skill_Buttons()
{

}
Skill_Buttons::~Skill_Buttons()
{
	this->m_ButtonReaction = 0;
	g_graphicsEngine->removeSpriteSheet(m_SkillButton);
	g_graphicsEngine->removeSpriteSheet(this->m_cooldown);
	m_SkillButton = NULL;
}
void Skill_Buttons::Init(FLOAT2 _ScreenPos,
			 FLOAT2 _Size, 
			 string _TextureName, 
			 string _Number, 
			 string _TextType,
			 unsigned int _skillId, 
			 float _min, 
			 float _max, 
			 float _textSize,
			 int _layer,
			 int _DelayTime,
			 bool _Active)
{
	this->m_skillId = _skillId;
	this->m_ButtonReaction	=	0;
	this->m_Value			=	0;
	this->m_id				=	StringtoINT(_Number);	
	//-----------------------------------------------------------------------------------------------
	//	Name of the textures and text
	//-----------------------------------------------------------------------------------------------
	this->m_TextureName		=	_TextureName;
	this->m_Number			=	_Number;
	this->m_TextType		=	_TextType;
	this->m_FullName		=	m_TextureName + m_Number + m_TextType;
	if(_max !=0)
	{
	this->m_Min				=	_min + _ScreenPos.x;
	this->m_Max				=	_max + _ScreenPos.x;
	}
	else 
	{
		this->m_Min			=	_min;
		this->m_Max			=	_max;
	}
	this->m_Pos.x			=	_ScreenPos.x;
	this->m_Pos.y			=	_ScreenPos.y;
	this->m_Size.x			=	_Size.x;
	this->m_Size.y			=	_Size.y;
	this->m_Delay			=	0;
	this->m_DelayTime		=	_DelayTime;
	this->m_Keep			=	0;
	this->m_Layer			=	_layer;
	this->m_Active			=	_Active;
	this->m_ChangeAble		=	true;
	this->m_Lock			=	false;
	this->m_SkillButton = g_graphicsEngine->createSpriteSheet(this->m_FullName,m_Pos,m_Size,INT2(3,1),m_Layer);
	this->m_cooldown = g_graphicsEngine->createSpriteSheet("menu_textures\\Clock.png", this->m_Pos, this->m_Size, INT2(4, 3), this->m_Layer + 1);
	this->m_cooldown->setVisible(false);
}
void Skill_Buttons::Update(float dt)
{
	//Get the mouse position
	INT2 tmpPos2 = g_mouse->getPos();

	INT2 m_SS = g_graphicsEngine->getRealScreenSize();
	FLOAT2 tmpPos;
	tmpPos2.y = m_SS.y - tmpPos2.y;
	tmpPos.x =(tmpPos2.x/ (float)m_SS.x) * 2 -1;
	tmpPos.y =(tmpPos2.y/ (float)m_SS.y) * 2 -1;
	FLOAT2 halfSize = FLOAT2(this->m_Size.x / 2, this->m_Size.y/2);
	if(m_Lock == false && m_Active == true)
	{
		if(tmpPos.x >= this->m_Pos.x - halfSize.x && tmpPos.y >= this->m_Pos.y - halfSize.y &&
		   tmpPos.x <= this->m_Pos.x + halfSize.x && tmpPos.y <= this->m_Pos.y + halfSize.y) 
		{
			if (GetKeyState(VK_LBUTTON)< 0)
			{
				m_ButtonReaction = 1;
				m_SkillButton->setCurrentFrame(INT2(1,0));
				//m_Lock = true;
			}
			else if(GetKeyState(VK_RBUTTON)< 0)
			{
				m_ButtonReaction = 1;
				m_SkillButton->setCurrentFrame(INT2(1,0));
			}
			else
			{
				m_ButtonReaction = 2;
				m_SkillButton->setCurrentFrame(INT2(2,0));
			}
		} 
		else 
		{
			m_ButtonReaction = 0;
			m_SkillButton->setCurrentFrame(INT2(0,0));
		}
		this->m_Delay += 1;
	}

	if(this->m_cooldown->getVisible() == true)
	{
		this->m_cooldownTime = this->m_cooldownTime - dt;

		if(this->m_cooldownTime <= 0.0f)
		{
			this->m_cooldown->setVisible(false);
		}
	}
}

unsigned int Skill_Buttons::getSkillId()
{
	return this->m_skillId;
}

int Skill_Buttons::GetButtonReaction()
{
	return this->m_ButtonReaction;
}
void Skill_Buttons::ChangeButton(string _Number, bool _Active, int id)
{
	this->m_skillId				=	id;	
	this->m_Number			=	_Number;
	//this->m_FullName		=	m_TextureName + m_Number + m_TextType;
	this->m_FullName = _Number;
	this->m_Active			=	_Active;

	g_graphicsEngine->removeSpriteSheet(m_SkillButton);
	m_SkillButton = g_graphicsEngine->createSpriteSheet(this->m_FullName,m_Pos,m_Size,INT2(3,1),m_Layer);
}
int Skill_Buttons::Clicked()
{
	if (this->m_ButtonReaction==1 && this->m_Delay > this->m_DelayTime)
	{
		this->m_Delay = 0;
		return 1;
	}
	if (this->m_ButtonReaction==2)
	{
		this->m_Delay = this->m_DelayTime+1;
		return 0;
	}
	else return 0;
}
float Skill_Buttons::ReturnSliderValue()
{
	return m_Value;
}
void Skill_Buttons::RemoveCooldown()
{
	m_Lock = false;
}
void Skill_Buttons::setPosition(FLOAT2 _pos)
{
	this->m_Pos = _pos;
	this->m_SkillButton->setPosition(this->m_Pos);
	this->m_cooldown->setPosition(this->m_Pos);
}
#include <iostream>
using namespace std;
int Skill_Buttons::StringtoINT(string stringInput)
{
	//----------------------------------------------------------------------------------------------------------------------------
	//	
	//----------------------------------------------------------------------------------------------------------------------------
	
	int INTout; 
	char* buf = new char[stringInput.length()];
	for(int i = 0; i < stringInput.length(); i++)
		buf[i] = stringInput.at(i);
	INTout = atoi(buf);
	delete buf; 
	return INTout;
}
void Skill_Buttons::ChangAbleBind(bool _Change)
{
	m_ChangeAble = _Change;
}
int Skill_Buttons::ReturnClicked()
{
	return this->m_id;
}
string Skill_Buttons::setID(string _ID)
{
	m_Number = _ID;
	m_id = StringtoINT(_ID);
	return m_Number;
}

void Skill_Buttons::setCooldown(float cooldown)
{
	this->m_cooldown->setVisible(true);
	this->m_cooldown->playAnimation(INT2(0, 0), INT2(3, 2), false, 12.0f / cooldown);
	this->m_cooldownTime = cooldown;
}
bool Skill_Buttons::getActiveorPassive()
{
	return this->m_Active;
}