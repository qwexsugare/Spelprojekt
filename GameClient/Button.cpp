#include "Button.h"

Button::Button()
{
}
void Button::Init(FLOAT2 _ScreenPos,
			 FLOAT2 _Size, 
			 string _TextureName, 
			 string _TextName, 
			 float _min, 
			 float _max, 
			 float _textSize,
			 int _layer,
			 int _DelayTime)
{
	this->m_ButtonReaction	=	0;
	this->m_Value = 0;
	//-----------------------------------------------------------------------------------------------
	//	Name of the textures and text
	//-----------------------------------------------------------------------------------------------
	this->m_TextureName		=	_TextureName;
	
	this->m_ButtonText		=	_TextName;
	if(_max !=0)
	{
	this->m_Min				=	_min + _ScreenPos.x;
	this->m_Max				=	_max + _ScreenPos.x;
	}
	else 
	{
		this->m_Min				=	_min;
		this->m_Max				=	_max;
	}
	this->m_Pos.x			=	_ScreenPos.x;
	this->m_Pos.y			=	_ScreenPos.y;
	this->m_Size.x			=	_Size.x;
	this->m_Size.y			=	_Size.y;
	this->m_Delay			=	0;
	this->m_DelayTime		=	_DelayTime;
	this->m_Keep			=	0;
	this->m_Layer			=	_layer;
	m_Button = g_graphicsEngine->createSpriteSheet(this->m_TextureName,m_Pos,m_Size,INT2(3,1),m_Layer);
}
void Button::Update()
{
	//Get the mouse position
	INT2 tmpPos2 = g_mouse->getPos();

	INT2 m_SS = g_graphicsEngine->getRealScreenSize();
	FLOAT2 tmpPos;
	tmpPos2.y = m_SS.y - tmpPos2.y;
	tmpPos.x =(tmpPos2.x/ (float)m_SS.x) * 2 -1;
	tmpPos.y =(tmpPos2.y/ (float)m_SS.y) * 2 -1;
	FLOAT2 halfSize = FLOAT2(this->m_Size.x / 2, this->m_Size.y/2);
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
	this->m_ButtonReaction = 0;
	g_graphicsEngine->removeSpriteSheet(m_Button);
	m_Button = NULL;
}
void Button::setPosition(FLOAT2 _pos)
{
	//g_graphicsEngine->removeSpriteSheet(m_Button);
	this->m_Pos = _pos;
	//m_Button = g_graphicsEngine->createSpriteSheet(this->m_TextureName,m_Pos,m_Size,INT2(3,1),2);
	this->m_Button->setPosition(this->m_Pos);
}
