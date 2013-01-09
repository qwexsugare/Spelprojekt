#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "EntityHandler.h"

//Import a map and update it, creating new enemies when needed
class MapHandler
{
private:

public:
	MapHandler();
	~MapHandler();

	void loadMap(std::string filename);
	void update();
	bool isDone();
};

#endif