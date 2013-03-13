#pragma once
#include <vector>
#include "GraphicsHandler.h"
#include "DataStructures.h"
#include "Model.h"
#include "Camera.h"
#include "Text.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Mouse.h"
#include "TextLabel.h"
#include <sstream>

using namespace std;
class Slider
{
private:
	//-----------------------------------------------------------------------------------------------
	// int for if Slider is Pressed UnPressed or Hovered
	//----------------------------------------------------------------------------------------------
		int m_SliderReaction;
		SpriteSheet* m_Slider;
		TextLabel* m_Label;
	//----------------------------------------------------------------------------------------------
	// Slider size
	//----------------------------------------------------------------------------------------------
		FLOAT2		m_Size;
	//----------------------------------------------------------------------------------------------
	// Slider position
	//----------------------------------------------------------------------------------------------
		FLOAT2		m_Pos;
		int			m_Keep,
					m_Layer,
					m_Cost,
					m_ID;
		INT2		m_TextPos;
		float		m_Value,
					m_Max,
					m_Min;
		bool		m_TextBox;
	//----------------------------------------------------------------------------------------------
	// Wave name
	//----------------------------------------------------------------------------------------------
		string			m_Sound;
	//----------------------------------------------------------------------------------------------
	// Textures used, text on Slider and active texture.
	//----------------------------------------------------------------------------------------------
		string			m_SliderText;

		string			m_TextureName;

	//----------------------------------------------------------------------------------------------

public:
	Slider();
	~Slider();
	int m_Delay;
	int m_DelayTime;
	void Init(	FLOAT2 _ScreenPos,
				float _offset,
				FLOAT2 _Size, 
				string _TextureName, 
				string _TextName,  
				float _min = 0, 
				float _max = 0, 
				float _textSize = 1,
				int _layer = 2,
				int _DelayTime = 100,
				int _Cost = 0,
				INT2 _TextPos = INT2(0,0),
				bool _TextBox = false,
				int _id = 0);

	void Slider::RemoveSprite();
	int Clicked();
	void Update();
	int GetSliderReaction();
	float ReturnSliderValue();
	void setPosition(float _pos);
	void SetID(int _id);
	int GetID();
	int LoseAmountOfResources(int _resources);
	float GetValue();
	void SetTextBoxValue(bool _change);
	void setVisible(bool _visible);
	void setValue(float _value);
	FLOAT2 getPos();
	int getCost();
	string getText();
	INT2 getTextPos();
	string getTextureName();
};