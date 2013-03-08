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

class Skill_Buttons
{
private:
	//-----------------------------------------------------------------------------------------------
	// int for if button is Pressed UnPressed or Hovered
	//----------------------------------------------------------------------------------------------
		int m_ButtonReaction ;
		SpriteSheet* m_SkillButton;
		SpriteSheet* m_cooldown;
		unsigned int m_skillId;
		
		float m_cooldownTime;
		int m_Delay;
		int m_DelayTime;
	//----------------------------------------------------------------------------------------------
	// Button size
	//----------------------------------------------------------------------------------------------
		FLOAT2		m_Size;
	//----------------------------------------------------------------------------------------------
	// Button position
	//----------------------------------------------------------------------------------------------
		FLOAT2		m_Pos;
		int			m_Max;
		int			m_Min;
		int			m_Keep;
		int			m_Layer;
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
		string			m_TextType;
		string			m_FullName;
		string			m_Number;
		bool			m_Lock;
		bool			m_Active;
		bool			m_ChangeAble;
		int				m_id;
	//----------------------------------------------------------------------------------------------

public:
	Skill_Buttons();
	~Skill_Buttons();

	void Init(	FLOAT2 _ScreenPos,
				FLOAT2 _Size, 
				string _TextureName, 
				string _Number,
				string _TextName, 
				unsigned int _skillId,
				float _min = 0, 
				float _max = 0, 
				float _textSize = 1,
				int _layer = 2,
				int _DelayTime = 100,
				bool _Active = false);

	int Clicked();
	void Update(float dt);
	unsigned int getSkillId();
	int GetButtonReaction();
	void RemoveCooldown();
	float ReturnSliderValue();
	void setPosition(FLOAT2 _pos);
	int StringtoINT(string stringInput);
	void ChangeButton(string _Number, bool _Active, int id);
	void ChangAbleBind(bool _Change);
	int Skill_Buttons::ReturnClicked();
	string setID(string _ID);
	void setCooldown(float cooldown);
	bool getActiveorPassive();
};

