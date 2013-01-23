#pragma once

class State
{
private:
	bool m_done;
public:
	static enum StateEnum {MAIN_MENU, CREATE_GAME, JOIN_GAME, LOBBY, GAME, SETTINGS, LORE, SCORE, CREDITS, EXIT };

	State();
	virtual ~State();

	bool isDone();
	virtual StateEnum nextState() = 0;
	void setDone(bool _done);
	virtual void update(float _dt) = 0;
};