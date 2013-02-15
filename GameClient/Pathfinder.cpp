#include "Pathfinder.h"

Pathfinder::Pathfinder(Map map, FLOAT2 mapSize)
{
	this->map=map;
	this->mapSize = mapSize;
}

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{

}

vector<Position> Pathfinder::getPath(Position start, Position end)
{
	vector<Position> path;

	//if the position is valid, then start runnig the aStar
	if(this->map.isValidPosition(start)&&this->map.isValidPosition(end)&&this->map.getWidth()>0 && this->map.getHeight()>0)
	{
		//first resents the parents and costs since the map is reused
		this->map.resetParents();
		//starts by calculating the H cost for the map
		//using the manhattan heuristics
		for(int i=0;i<this->map.getHeight();i++)
		{
			for(int j=0;j<this->map.getWidth();j++)
			{
				Position currPos;
				currPos.setXY(j,i);
				this->map.getNode(currPos)->setHCost(this->getManhattanDistance(currPos,end));
				this->map.getNode(currPos)->setPosition(currPos);
			}
		}
		Node* endNode= this->map.getNode(end);

		this->map.getNode(start)->putOnOpenList();
		openList.push_back(this->map.getNode(start));

		//bool to break the loop if you add the end node
		//to the closed list
		bool reachedEnd=false;
		while(!openList.empty()&&!reachedEnd)
		{
			Node* currentNode=openList[0];
			int lowestF=openList[0]->getFCost();

			//looks for the lowset F value in the openlist
			int index=0;
			for(int i=1;i<openList.size();i++)
			{
				if(openList[i]->getFCost()<lowestF)
				{
					index=i;
					lowestF= openList[i]->getFCost();
					//currentNode= openList[i];
				}
			}

			currentNode=openList[index];
			//moves the node with the lowest F from the openlist to the closed list
			currentNode->putOnClosedList();
			closedList.push_back(currentNode);
			openList[index]=openList[openList.size()-1];
			openList.pop_back();
			//if the node we add to the closed list is the endnode
			//then we are done

			if(endNode==currentNode)
				reachedEnd=true;
			else
				this->handleNodesNeighbour(currentNode);
		}
		
		//a path was found
		if(reachedEnd)
		{
			Node* currentNode=endNode;
			while(currentNode->getParent()!=0)
			{
				path.push_back(currentNode->getPosition());
				currentNode=currentNode->getParent();
			}
		}
		else
		{
			int lowestH=closedList[0]->getHCost();
			Node* closestNode = closedList[0];

			//looks for the lowset H value in the openlist
			for(int i=1;i<closedList.size();i++)
			{
				if(closedList[i]->getHCost()<lowestH)
				{
					lowestH= closedList[i]->getHCost();
					closestNode=closedList[i];
				}
			}
			while(closestNode->getParent()!=0)
			{
				path.push_back(closestNode->getPosition());
				closestNode=closestNode->getParent();
			}
		}
	}

	//just swaps the path going from start to end
	vector<Position> correctPath;
	for(int i=path.size()-1;i>=0;i--)
		correctPath.push_back(path[i]);

	vector<Position> p;
	//tries to smooth the path
	if(correctPath.size()>1)
	{
		Position start = correctPath[0];
		p.push_back(start);
		for(int i=1;i<correctPath.size()-1;i++)
		{
			if(this->walkableDistance(start,correctPath[i]))
			{
			}
			else
			{
				start=correctPath[i];
				p.push_back(start);
			}
		}
	}

	return correctPath;
}
void Pathfinder::handleNodesNeighbour(Node* currentNode)
{
	//check right to the current node
	Position nPos;
	nPos.setXY(currentNode->getPosition().getX()+1,currentNode->getPosition().getY());
	bool walkableRight = this->handleNeighbour(currentNode, nPos,NONDIAGMOVECOST);
	//left
	nPos.setXY(currentNode->getPosition().getX()-1,currentNode->getPosition().getY());
	bool walkableLeft = this->handleNeighbour(currentNode, nPos,NONDIAGMOVECOST);
	//up
	nPos.setXY(currentNode->getPosition().getX(),currentNode->getPosition().getY()+1);
	bool walkableUp = this->handleNeighbour(currentNode, nPos,NONDIAGMOVECOST);
	//down
	nPos.setXY(currentNode->getPosition().getX(),currentNode->getPosition().getY()-1);
	bool walkableDown = this->handleNeighbour(currentNode, nPos,NONDIAGMOVECOST);

	//if the vert/horz nodes arent walls, they should be checked diagonally
	//upper right
	if(walkableRight&&walkableUp)
	{
		nPos.setXY(currentNode->getPosition().getX()+1,currentNode->getPosition().getY()+1);
		this->handleNeighbour(currentNode, nPos,DIAGMOVECOST);
	}
	//lower right
	if(walkableRight&&walkableDown)
	{
		nPos.setXY(currentNode->getPosition().getX()+1,currentNode->getPosition().getY()-1);
		this->handleNeighbour(currentNode, nPos,DIAGMOVECOST);
	}
	//upper left
	if(walkableLeft&&walkableUp)
	{
		nPos.setXY(currentNode->getPosition().getX()-1,currentNode->getPosition().getY()+1);
		this->handleNeighbour(currentNode, nPos,DIAGMOVECOST);
	}
	//lower left
	if(walkableLeft&&walkableDown)
	{
		nPos.setXY(currentNode->getPosition().getX()-1,currentNode->getPosition().getY()-1);
		this->handleNeighbour(currentNode, nPos,DIAGMOVECOST);
	}
}

//returns true if the node is walkble
bool Pathfinder::handleNeighbour(Node* currentNode,Position neighbourPos,int cost)
{
	bool walkable=true;
	if(this->map.isValidPosition(neighbourPos))
	{
		Node* neighbourNode =this->map.getNode(neighbourPos);
		if(neighbourNode->isWall())
			walkable=false;
	
		if(walkable&&!neighbourNode->isOnClosedList())
		{
			if(!neighbourNode->isOnOpenlist())
			{
				neighbourNode->setGCost(currentNode->getGCost()+currentNode->getAdditionalCost() + cost);
				neighbourNode->setParent(currentNode);
				neighbourNode->putOnOpenList();
				this->openList.push_back(neighbourNode);
			}
			else
			{
				if(neighbourNode->getGCost()+neighbourNode->getAdditionalCost()>(currentNode->getGCost()+currentNode->getAdditionalCost() + cost))
				{
					neighbourNode->setGCost(currentNode->getGCost()+currentNode->getAdditionalCost() + cost);
					neighbourNode->setParent(currentNode);
				}
			}
		}
	}
	else
		walkable=false;
	return walkable;
}
int Pathfinder::getManhattanDistance(Position p1, Position p2)
{
	return (abs(p1.getX() -p2.getX())+abs(p1.getY()-p2.getY()))*NONDIAGMOVECOST;
}

float Pathfinder::distance(Position p1, Position p2)
{
	return sqrt((p2.getX()-p1.getX())*(p2.getX()-p1.getX())+(p2.getY()-p1.getY())*(p2.getY()-p1.getY()));
}
int Pathfinder::diretion(int x1,int x2)
{
	return x2-x1;
}

bool Pathfinder::walkableDistance(Position p1, Position p2)
{
	//first gets the distance between the two nodes
	float distance = this->distance(p1,p2);
	//Calulates at what rate the direction changes
	float xrate = (this->diretion(p1.getX(),p2.getX()))/distance;
	float yrate = (this->diretion(p1.getY(),p2.getY()))/distance;
	bool walkable=true;

	//rate distance
	float rDistance = sqrt(xrate*xrate+yrate*yrate);
	float limiter =0;
	int counter=0;
	Position pt;
	if(xrate<0&&yrate<0)
		pt=p2;
	else
		pt=p1;
	while(limiter<distance&&walkable)
	{
		Position p;
		p.setXY(xrate*counter*rDistance+pt.getX(),yrate*counter*rDistance+pt.getY());
		cout << p.getX() << p.getY() << endl;
		if(this->map.getNode(p)->isWall())
			walkable=false;
		limiter+=rDistance;
		counter++;
	}
	return walkable;
}

Path Pathfinder::getPath(FLOAT2 start, FLOAT2 end)
{
	Position startPos = Position(start.x * this->map.getWidth() / this->mapSize.x, start.y * this->map.getHeight() / this->mapSize.y);
	Position endPos = Position(end.x * this->map.getWidth() / this->mapSize.x, end.y * this->map.getHeight() / this->mapSize.y);

	vector<Position> path = this->getPath(startPos, endPos);

	FLOAT2 *points = new FLOAT2[path.size()];

	for(int i = 0; i < path.size(); i++)
	{
		points[i] = FLOAT2(this->mapSize.x * path[i].getX() / this->map.getWidth(), this->mapSize.y * path[i].getY() / this->map.getHeight());
	}

	Path p  = Path(path.size(), points);
	delete[] points;
	return p;
}