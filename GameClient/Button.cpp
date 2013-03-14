#include "Button.h"
#include "Input.h"
#include "Graphics.h"
#include "SoundWrapper.h"

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
			 int _DelayTime,
			 int _Cost,
			 INT2 _TextPos,
			 bool _TextBox,
			 int _id,
			 string _Skill)
{
	this->m_clicked = false;
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
	this->m_Cost			=   _Cost;
	this->m_TextPos.x		=	_TextPos.x;
	this->m_TextPos.y		=	_TextPos.y;
	this->m_ID				=	_id;
	this->m_TextBox			=	_TextBox;
	this->m_Label			=	new TextLabel(_TextName, "text1.png",INT2(m_TextPos.x, m_TextPos.y),100);
	m_Button				=	g_graphicsEngine->createSpriteSheet(this->m_TextureName,m_Pos,m_Size,INT2(3,1),m_Layer);
	this->m_clickSound		=	createSoundHandle("buttons/PushButton.wav", false, false);
	this->m_Skill			=	_Skill;
	if(m_Skill != "")
	{
		m_SpriteSkill = g_graphicsEngine->createSprite(m_Skill, FLOAT2(m_Pos.x+0.1f,m_Pos.y+0.1f),FLOAT2(0.260416667f,0.185185185f),20);
		m_SpriteSkill->setVisible(false);
	}
}
void Button::Update()
{
	m_clicked = false;

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
			this->m_Delay += 1;
			if (g_mouse->isLButtonReleased())
			{
				this->m_ButtonReaction = 1;
				this->m_Button->setCurrentFrame(INT2(1,0));

				playSound(m_clickSound);
			}
			else if(g_mouse->isLButtonDown())
			{
				this->m_Button->setCurrentFrame(INT2(1,0));
			}
			else if(g_mouse->isRButtonReleased())
			{
				this->m_ButtonReaction = 2;
				this->m_Button->setCurrentFrame(INT2(1,0));

			}
			else if(g_mouse->isRButtonDown())
			{
				this->m_Button->setCurrentFrame(INT2(1,0));
			}
			else
			{
				this->m_ButtonReaction = 3;
				this->m_Button->setCurrentFrame(INT2(2,0));
				if(m_Skill != "")
				{
					m_SpriteSkill->setVisible(true);
				}
			}
		} 
		else
		{
			this->m_ButtonReaction = 0;
			this->m_Button->setCurrentFrame(INT2(0,0));
			if(m_Skill != "")
			{
				m_SpriteSkill->setVisible(false);
			}
		}
		this->m_Delay += 1;
	}
	if (this->m_TextBox == true)
	{
		this->m_Button->setCurrentFrame(INT2(1,0));
	}

	this->Clicked();
}
int Button::GetButtonReaction()
{
	return this->m_ButtonReaction;
}
int Button::Clicked()
{
	if (this->m_ButtonReaction==1 ) //&& this->m_Delay > this->m_DelayTime)
	{
		m_clicked = true;
		this->m_Delay = 0;
		return 1;
	}
	else if(this->m_ButtonReaction==2 && this->m_Delay > this->m_DelayTime )
	{
		this->m_Delay = this->m_DelayTime+1;
		return 0;
	}
	else if(this->m_ButtonReaction==3)
	{
		this->m_Delay = this->m_DelayTime+1;
		return 3;
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
	this->m_Button = NULL;
	delete this->m_Label;
	this->m_Label = NULL;
	if(m_Skill != "")
	{
		g_graphicsEngine->removeSprite(m_SpriteSkill);
		this->m_SpriteSkill = NULL;
	}
	deactivateSound(m_clickSound);
}
void Button::RemoveSprite()
{
	this->m_ButtonReaction = 0;
	g_graphicsEngine->removeSpriteSheet(m_Button);
	this->m_Button = NULL;
}
void Button::setPosition(FLOAT2 _pos)
{
	this->m_Pos = _pos;
	this->m_Button->setPosition(m_Pos);
}
int  Button::LoseAmountOfResources(int _resources)
{
	int Lost = _resources - m_Cost;
	if (Lost <= 0)
	{
		return 0;
	}
	else return Lost;
}
void Button::SetID(int _id)
{
	this->m_ID = _id;
}
int Button::GetID()
{
	return this->m_ID;
}
float Button::GetValue()
{
	return this->m_Value;
}

void Button::setCurrentFrame(INT2 _frame)
{
	this->setCurrentFrame(_frame);
}

void Button::setKeep(int _keep)
{

}

void Button::SetTextBoxValue(bool _change)
{
	this->m_TextBox = _change;
}

void Button::setVisible(bool _visible)
{
	this->m_Button->setVisible(_visible);
	this->m_Label->setVisible(_visible);
}

void Button::setText(string _text)
{
	this->m_Label->setText(_text);
}

FLOAT2 Button::getPos()
{
	return this->m_Pos;
}

int Button::getCost()
{
	return this->m_Cost;
}

string Button::getText()
{
	return this->m_ButtonText;
}

INT2 Button::getTextPos()
{
	return this->m_TextPos;
}

string Button::getTextureName()
{
	return this->m_TextureName;
}
void  Button::setTexture(string _Image)
{
	g_graphicsEngine->removeSpriteSheet(m_Button);
	this->m_Button = NULL;
	this->m_TextureName = _Image;
	m_Button =	g_graphicsEngine->createSpriteSheet(this->m_TextureName,m_Pos,m_Size,INT2(3,1),m_Layer);
}