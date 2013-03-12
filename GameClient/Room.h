#pragma once

#include "Graphics.h"

class Room
{
private:
	Model* room;
	Model* character;
	PointLight* frontLight;
	PointLight* inLight;
	PointLight* backLight;
public:
	Room();
	~Room();
};