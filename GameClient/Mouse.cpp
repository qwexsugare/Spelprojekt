#include "Mouse.h"

Mouse::Mouse(int _x, int _y,  HWND _hWnd)
{
	this->m_hWnd = _hWnd;
	SetCursorPos(_x, _y);
	
	this->m_lButtonIsDown = false;
	this->m_lButtonIsReleased = false;
	this->m_lButtonIsPressed = false;
	this->m_rButtonIsDown = false;
	this->m_rButtonIsPressed = false;
	this->m_rButtonIsReleased = false;

	ShowCursor(false);

	this->m_cursor = new Cursor();
	this->m_cursor->setPosition(this->getPos());
}

Mouse::~Mouse()
{
	delete this->m_cursor;
}

INT2 Mouse::getPos()const
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(this->m_hWnd, &pos);

	return INT2(pos.x, pos.y);
}

void Mouse::lButtonDown()
{
	if(!this->m_lButtonIsDown)
	{
		this->m_lButtonIsPressed = true;
		this->m_cursor->setFrame(Cursor::CLICK, 1);
	}
	this->m_lButtonIsDown = true;
}

void Mouse::rButtonDown()
{
	if(!this->m_rButtonIsDown)
		this->m_rButtonIsPressed = true;
	this->m_rButtonIsDown = true;
}

void Mouse::lButtonUp()
{
	m_lButtonIsDown = false;
	m_lButtonIsReleased = true;
	this->m_cursor->setFrame(Cursor::DEFAULT, 1);
}

void Mouse::rButtonUp()
{
	m_rButtonIsDown = false;
	m_rButtonIsReleased = true;
}

void Mouse::setMousePosition(int _x, int _y)
{
	SetCursorPos(_x, _y);
}

void Mouse::setMouseVisibility(bool _visible)const
{
	if(_visible)
		while(ShowCursor(TRUE) < 0);
	else
		while(ShowCursor(FALSE) >= 0);
}

void Mouse::update()
{
	//RECT rc;
	//GetWindowRect(this->m_hWnd, &rc);
	//ClipCursor(&rc);

	m_lButtonIsPressed = false;
	m_lButtonIsReleased = false;
	m_rButtonIsPressed = false;
	m_rButtonIsReleased = false;

	this->m_cursor->setPosition(this->getPos());
	//this->m_cursor->setFrame(Cursor::DEFAULT);
}

void Mouse::updateCursorPosMoreFrequently()
{
	this->m_cursor->setPosition(this->getPos());
}

Cursor *Mouse::getCursor()
{
	return this->m_cursor;
}