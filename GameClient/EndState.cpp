#include "EndState.h"
#include "Graphics.h"

EndState::EndState(bool _victorious)
{
	if(_victorious == true)
	{
		this->m_background = g_graphicsEngine->createSprite("menu_textures\\MENU-END-1.png", FLOAT2(0.0f, 0.0f), FLOAT2(2.0f, 2.0f), 0);
	}
	else
	{
		this->m_background = g_graphicsEngine->createSprite("menu_textures\\MENU-END-0.png", FLOAT2(0.0f, 0.0f), FLOAT2(2.0f, 2.0f), 0);
	}
}

EndState::~EndState()
{

}

State::StateEnum EndState::nextState()
{
	return State::MAIN_MENU;
}

void EndState::update(float _dt)
{
	int dbg = 1;
}