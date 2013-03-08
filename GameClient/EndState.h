#pragma once

#include "state.h"

class EndState : public State
{
private:

public:
	EndState(bool _victorious);
	~EndState();

	StateEnum nextState();
	void update(float _dt);
};

