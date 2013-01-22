#include "Skill_Buttons.h"

Skill_Buttons::Skill_Buttons()
{
}
void Skill_Buttons::Init(FLOAT2 _ScreenPos,
			 FLOAT2 _Size, 
			 string _TextureName, 
			 string _Number, 
			 string _TextType, 
			 float _min, 
			 float _max, 
			 float _textSize,
			 int _layer,
			 int _DelayTime,
			 bool _Active)
{
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
	m_SkillButton = g_graphicsEngine->createSpriteSheet(this->m_FullName,m_Pos,m_Size,INT2(3,1),m_Layer);
}
void Skill_Buttons::Update()
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
}
int Skill_Buttons::GetButtonReaction()
{
	return this->m_ButtonReaction;
}
void Skill_Buttons::ChangeButton(string _Number, bool _Active)
{
	this->m_id				=	StringtoINT(_Number);	
	this->m_Number			=	_Number;
	this->m_FullName		=	m_TextureName + m_Number + m_TextType;
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
	g_graphicsEngine->removeSpriteSheet(m_SkillButton);
	m_SkillButton = g_graphicsEngine->createSpriteSheet(this->m_FullName,m_Pos,m_Size,INT2(3,1),2);
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
Skill_Buttons::~Skill_Buttons()
{
	this->m_ButtonReaction = 0;
	g_graphicsEngine->removeSpriteSheet(m_SkillButton);
	m_SkillButton = NULL;
}

