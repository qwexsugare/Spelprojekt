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

extern GraphicsHandler* g_graphicsEngine;
extern Mouse* g_mouse;

using namespace std;
class Button
{
private:
	//-----------------------------------------------------------------------------------------------
	// int for if button is Pressed UnPressed or Hovered
	//----------------------------------------------------------------------------------------------
		int m_ButtonReaction ;
		SpriteSheet* m_Button;
		
	//----------------------------------------------------------------------------------------------
	// Button size
	//----------------------------------------------------------------------------------------------
		FLOAT2		m_Size;
	//----------------------------------------------------------------------------------------------
	// Button position
	//----------------------------------------------------------------------------------------------
		FLOAT2		m_Pos;
		int			m_Max,
					m_Min,
					m_Keep,
					m_Layer,
					m_Cost;
		float		m_Value;
	//----------------------------------------------------------------------------------------------
	// Wave name
	//----------------------------------------------------------------------------------------------
		string			m_Sound;
	//----------------------------------------------------------------------------------------------
	// Textures used, text on button and active texture.
	//----------------------------------------------------------------------------------------------
		string			m_ButtonText;

		string			m_TextureName;

	//----------------------------------------------------------------------------------------------

public:
	Button();
	~Button();
	int m_Delay;
	int m_DelayTime;
	void Init(	FLOAT2 _ScreenPos,
				FLOAT2 _Size, 
				string _TextureName, 
				string _TextName,  
				float _min = 0, 
				float _max = 0, 
				float _textSize = 1,
				int _layer = 2,
				int _DelayTime = 100,
				int _Cost = 0);
	void Button::RemoveSprite();
	int Clicked();
	void Update();
	int GetButtonReaction();
	float ReturnSliderValue();
	void setPosition(FLOAT2 _pos);
	int LoseAmountOfResources(int _resources);
};

