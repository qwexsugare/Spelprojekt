#pragma once

#include "state.h"
#include "Graphics.h"

class EndState : public State
{
private:
	Sprite *m_background;
public:
	EndState(bool _victorious);
	~EndState();

	StateEnum nextState();
	void update(float _dt);
};

