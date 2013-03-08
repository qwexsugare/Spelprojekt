#pragma once

class State
{
public:
	static enum StateEnum {INTRO,MAIN_MENU, CREATE_GAME, JOIN_GAME, LOBBY, GAME, SETTINGS, LORE, SCORE, CREDITS, EXIT, END, LOADING };

private:
	bool m_done;
	StateEnum m_type;
public:

	State();
	State(StateEnum _type);
	virtual ~State();

	bool isDone();
	virtual StateEnum nextState() = 0;
	void setDone(bool _done);
	virtual void update(float _dt) = 0;

	StateEnum getType();
};