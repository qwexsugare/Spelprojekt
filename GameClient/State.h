#pragma once

class State
{
public:
	State();
	virtual ~State();

	virtual void update(float _dt) = 0;
	virtual void render() = 0;
	virtual bool done() = 0;
	virtual State* nextState() = 0;
};