#pragma once

class State
{
private:
	bool m_done;
public:
	State();
	virtual ~State();

	bool isDone();
	virtual State* nextState() = 0;
	void setDone(bool _done);
	virtual void update(float _dt) = 0;
};