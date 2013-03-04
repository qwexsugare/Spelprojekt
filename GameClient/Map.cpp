#include "Map.h"

Map::Map()
{
	this->height=0;
	this->width=0;
	this->initialized=false;
	this->nodes = 0;
}
Map::Map(int width, int height)
{
	this->height=width;
	this->width=height;
	this->initialized=true;
	this->nodes = new Node*[this->height];
	for(int i=0;i<this->height;i++)
		this->nodes[i]=new Node[this->width];
}
Map::~Map()
{
	for(int i=0;i<this->height;i++)
	{
		delete[] this->nodes[i];
	}
	delete[] this->nodes;
}
Map::Map(const Map &sourceMap)
{
	this->height=sourceMap.height;
	this->width=sourceMap.width;
	this->initialized=sourceMap.initialized;

	this->nodes = new Node*[this->height];
	for(int i=0;i<this->height;i++)
		this->nodes[i]=new Node[this->width];
	for(int i=0;i<this->height;i++)
	{
		for(int j=0;j<this->width;j++)
		{
			this->nodes[i][j]=sourceMap.nodes[i][j];
		}
	}
}
Map& Map::operator=(const Map &sourceMap)
{
	if(this!=&sourceMap)
	{
		for(int i=0;i<this->height;i++)
			delete[] this->nodes[i];
		delete[] this->nodes;

		this->height=sourceMap.height;
		this->width=sourceMap.width;
		this->initialized=sourceMap.initialized;

		this->nodes = new Node*[this->height];
		for(int i=0;i<this->height;i++)
			this->nodes[i]=new Node[this->width];
		for(int i=0;i<this->height;i++)
		{
			for(int j=0;j<this->width;j++)
			{
				this->nodes[i][j]=sourceMap.nodes[i][j];
			}
		}
	}
	return *this;
}
int Map::getHeight()
{
	return this->height;
}
int Map::getWidth()
{
	return this->width;
}

void Map::resetParents()
{
	for(int i=0;i<this->height;i++)
	{
		for(int j=0;j<this->width;j++)
		{
			this->nodes[i][j].resetCostsAndParent();
		}
	}
}
Node* Map::getNode(Position p)
{
	if(p.getX()>=0&&p.getX()<this->width&&p.getY()>=0&&p.getY()<this->height)
	{
		return &this->nodes[p.getY()][p.getX()];
	}
	return 0;
}

bool Map::isValidPosition(Position p)
{
	return (p.getX()>=0&&p.getX()<this->width&&p.getY()>=0&&p.getY()<this->height);
}