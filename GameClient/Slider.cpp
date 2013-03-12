#include "Slider.h"
#include "Input.h"
#include "Graphics.h"

Slider::Slider()
{
}
void Slider::Init(FLOAT2 _ScreenPos,
			float _offset,
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
			 int _id)
{
	this->m_SliderReaction	=	0;
	this->m_Value = 0;
	//-----------------------------------------------------------------------------------------------
	//	Name of the textures and text
	//-----------------------------------------------------------------------------------------------
	this->m_TextureName		=	_TextureName;
	
	this->m_SliderText		=	_TextName;
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
	m_Slider				=	g_graphicsEngine->createSpriteSheet(this->m_TextureName,m_Pos,m_Size,INT2(3,1),m_Layer);

	// Now for the crazy offset calculation, prepare for the ride of a lifetime!
	m_Pos.x += _offset;
	// Here we copy
	float interval = m_Max-m_Min;
	float pos = m_Pos.x-m_Min;
	this->m_Value = pos/interval;
	g_graphicsEngine->removeSpriteSheet(this->m_Slider);
	this->m_Slider = g_graphicsEngine->createSpriteSheet(this->m_TextureName,this->m_Pos,this->m_Size,INT2(3,1),2);
	this->m_Slider->setCurrentFrame(INT2(0,0));
}
void Slider::Update()
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
		   tmpPos.x <= this->m_Pos.x + halfSize.x && tmpPos.y <= this->m_Pos.y + halfSize.y && this->m_Max != 0 && g_mouse->isLButtonDown())
		{
			float tmp_Pos = this->m_Pos.x;

			this->m_Pos.x = tmpPos.x;

			this->m_Keep = 1;

			this->m_SliderReaction = 1;
			this->m_Slider->setCurrentFrame(INT2(1,0));
		}
	}
	if(this->m_Keep == 1)
	{
		this->m_Pos.x = tmpPos.x;
		float interval = m_Max-m_Min;
		float pos = m_Pos.x-m_Min;
		this->m_Value = pos/interval;
		if (tmpPos.x > this->m_Max)
		{
			this->m_Pos.x = this->m_Max;
			this->m_Value = 1.0f;
			g_graphicsEngine->removeSpriteSheet(this->m_Slider);
			this->m_Slider = g_graphicsEngine->createSpriteSheet(this->m_TextureName,this->m_Pos,this->m_Size,INT2(3,1),2);
		}
		if (tmpPos.x < this->m_Min)
		{
			this->m_Pos.x = this->m_Min;
			this->m_Value = 0.0f;
			g_graphicsEngine->removeSpriteSheet(this->m_Slider);
			this->m_Slider = g_graphicsEngine->createSpriteSheet(this->m_TextureName,this->m_Pos,this->m_Size,INT2(3,1),2);
		}
		g_graphicsEngine->removeSpriteSheet(this->m_Slider);
		this->m_Slider = g_graphicsEngine->createSpriteSheet(this->m_TextureName,this->m_Pos,this->m_Size,INT2(3,1),2);
		this->m_Slider->setCurrentFrame(INT2(0,0));
		if(GetKeyState(VK_LBUTTON) < 0)
		{
			this->m_Keep = 1;
			this->m_Slider->setCurrentFrame(INT2(2,0));
		}
		else this->m_Keep =0;
	}
	if(m_TextBox == true)
	{
		this->m_Slider->setCurrentFrame(INT2(1,0));
	}

}
int Slider::GetSliderReaction()
{
	return this->m_SliderReaction;
}
int Slider::Clicked()
{
	if (this->m_SliderReaction==1 && this->m_Delay > this->m_DelayTime )
	{
		this->m_Delay = 0;
		return 1;
	}
	else if(this->m_SliderReaction==2 && this->m_Delay > this->m_DelayTime )
	{
		this->m_Delay = this->m_DelayTime+1;
		return 0;
	}
	else if(this->m_SliderReaction==3)
	{
		this->m_Delay = this->m_DelayTime+1;
		return 3;
	}
	else return 0;
}
float Slider::ReturnSliderValue()
{
	return m_Value;
}
Slider::~Slider()
{
	this->m_SliderReaction = 0;
	g_graphicsEngine->removeSpriteSheet(m_Slider);
	this->m_Slider = NULL;
	delete this->m_Label;
	this->m_Label = NULL;
}
void Slider::RemoveSprite()
{
	this->m_SliderReaction = 0;
	g_graphicsEngine->removeSpriteSheet(m_Slider);
	this->m_Slider = NULL;
}
void Slider::setPosition(FLOAT2 _pos)
{
	this->m_Pos = _pos;
	this->m_Slider->setPosition(m_Pos);
}
int  Slider::LoseAmountOfResources(int _resources)
{
	int Lost = _resources - m_Cost;
	if (Lost <= 0)
	{
		return 0;
	}
	else return Lost;
}
void Slider::SetID(int _id)
{
	this->m_ID = _id;
}
int Slider::GetID()
{
	return this->m_ID;
}
float Slider::GetValue()
{
	return this->m_Value;
}
void Slider::SetTextBoxValue(bool _change)
{
	this->m_TextBox = _change;
}

void Slider::setVisible(bool _visible)
{
	this->m_Slider->setVisible(_visible);
	this->m_Label->setVisible(_visible);
}

FLOAT2 Slider::getPos()
{
	return this->m_Pos;
}

int Slider::getCost()
{
	return this->m_Cost;
}

string Slider::getText()
{
	return this->m_SliderText;
}

INT2 Slider::getTextPos()
{
	return this->m_TextPos;
}

string Slider::getTextureName()
{
	return this->m_TextureName;
}