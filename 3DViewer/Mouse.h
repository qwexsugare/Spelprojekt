#pragma once

#include "DataStructures.h"
#include <Windows.h>

class Mouse
{
private:
	bool m_lButtonIsDown;
	bool m_lButtonIsPressed;
	bool m_rButtonIsDown;
	bool m_rButtonIsPressed;
	HWND m_hWnd;
public:
	Mouse();
	Mouse(int _x, int _y, HWND _hWnd);
	virtual ~Mouse();
	
	INT2 getPos()const;
	bool isLButtonDown()const { return this->m_lButtonIsDown; }
	bool isLButtonPressed()const { return this->m_lButtonIsPressed; }
	bool isRButtonDown()const { return this->m_rButtonIsDown; }
	bool isRButtonPressed()const { return this->m_rButtonIsPressed; }
	void lButtonDown();
	void rButtonDown();
	void lButtonUp();
	void rButtonUp();
	void setMousePosition(int _x, int _y);
	void update();
	void setMouseVisibility(bool _visible)const;
};