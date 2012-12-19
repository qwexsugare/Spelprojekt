#include "Button.h"

Button::Button()
{
}
void Button::Init(INT2 _ScreenPos,
			 INT2 _Size, 
			 string _TextureName, 
			 string _TextName, 
			 int _min, 
			 int _max, 
			 float _textSize,
			 int _DelayTime)
{
	this->m_ButtonReaction	=	0;
	this->m_Value = 0;
	//-----------------------------------------------------------------------------------------------
	//	Name of the textures and text
	//-----------------------------------------------------------------------------------------------
	this->m_TextureName		=	_TextureName;
	
	this->m_ButtonText		=	_TextName;
	this->m_Min				=	_min + _ScreenPos.x;
	this->m_Max				=	_max + _ScreenPos.x;
	this->m_Pos.x			=	_ScreenPos.x;
	this->m_Pos.y			=	_ScreenPos.y;
	this->m_Size			=	_Size;
	this->m_Delay			=	0;
	this->m_DelayTime		=	_DelayTime;
	this->m_Keep			=	0;

	m_Pos.x = 2* ((float)m_Pos.x) / 1920 - 1;
	m_Pos.y = 2* ((float)m_Pos.y) / 1080 - 1;

	_Size.x = 2* ((float)_Size.x) / 1920;
	_Size.y = 2* ((float)_Size.y) / 1080;

	m_Button = g_graphicsEngine->createSpriteSheet(this->m_TextureName,m_Pos,_Size,INT2(3,1),2);
}
void Button::Update()
{
	//Get the mouse position
	INT2 tmpPos = g_mouse->getPos();
	tmpPos.y = 1080 - tmpPos.y;
	INT2 halfSize = INT2(this->m_Size.x / 2, this->m_Size.y / 2);
	if(m_Keep == 0)
	{
		if(tmpPos.x >= this->m_Pos.x - halfSize.x && tmpPos.y >= this->m_Pos.y - halfSize.y &&
		   tmpPos.x <= this->m_Pos.x + halfSize.x && tmpPos.y <= this->m_Pos.y + halfSize.y) 
		{
			if (GetKeyState(VK_LBUTTON)< 0)
			{
				m_ButtonReaction = 1;
				m_Button->setCurrentFrame(INT2(1,0));
			}
			else if(GetKeyState(VK_RBUTTON)< 0)
			{
				m_ButtonReaction = 1;
				m_Button->setCurrentFrame(INT2(1,0));
			}
			else
			{
				m_ButtonReaction = 2;
				m_Button->setCurrentFrame(INT2(2,0));
			}
		} 
		else 
		{
			m_ButtonReaction = 0;
			m_Button->setCurrentFrame(INT2(0,0));
		}
		this->m_Delay += 1;
		if(this->m_Max != 0)
		{
			float tmp_Pos = m_Pos.x;
			if(this->m_ButtonReaction == 1)
			{
				this->m_Pos.x = tmpPos.x;
				if (tmpPos.x > m_Max)
				{
					m_Keep = 1;
				}
				if (tmpPos.x < m_Min)
				{
					m_Keep = 1;
				}
				m_Keep = 1;
			}
		}
	}
	if(m_Keep == 1)
	{
		this->m_Pos.x = tmpPos.x;
		m_Value = ((float)tmpPos.x/385.0f)*100.0f;
		if (tmpPos.x > m_Max)
		{
			this->m_Pos.x = m_Max;
			m_Value = 100.0f;
			g_graphicsEngine->removeSpriteSheet(m_Button);
			m_Button = g_graphicsEngine->createSpriteSheet(this->m_TextureName,m_Pos,m_Size,INT2(3,1),2);
		}
		if (tmpPos.x < m_Min)
		{
			this-> m_Pos.x = m_Min;
			m_Value = 0.0f;
			g_graphicsEngine->removeSpriteSheet(m_Button);
			m_Button = g_graphicsEngine->createSpriteSheet(this->m_TextureName,m_Pos,m_Size,INT2(3,1),2);
		}
		g_graphicsEngine->removeSpriteSheet(m_Button);
		m_Button = g_graphicsEngine->createSpriteSheet(this->m_TextureName,m_Pos,m_Size,INT2(3,1),2);
		if(GetKeyState(VK_LBUTTON) < 0)
		{
			m_Keep = 1;
		}
		else m_Keep =0;
	}

}
int Button::GetButtonReaction()
{
	return this->m_ButtonReaction;
}
int Button::Clicked()
{
	if (this->m_ButtonReaction==1 && this->m_Delay > this->m_DelayTime )
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
float Button::ReturnSliderValue()
{
	return m_Value;
}
Button::~Button()
{
	this->m_ButtonReaction =0;
	g_graphicsEngine->removeSpriteSheet(m_Button);
	m_Button = NULL;
}
