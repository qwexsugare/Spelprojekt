#include "Pathfinder.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define vertMoveCost 100
//instead of sqrt(2) about 1,4, for performence
#define diagMoveCost 140

Pathfinder::~Pathfinder()
{
	for(int i=0;i<rows;i++)
	{
		delete  this->nodes[i];
	}
	delete this->nodes;
}
Pathfinder::Pathfinder(int x, int y)
{
	this->rows=y;
	this->cols=x;
	this->nodes = new Node* [rows];
	for(int i=0;i<rows;i++)
	{
		this->nodes[i]=new Node[cols];
	}
	this->startX=-1;
	this->startY=-1;
	this->endX=-1;
	this->endY=-1;
	int k=0;
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			this->nodes[i][j]=Node(j,i);
			this->nodes[i][j].setId(k++);
		}
	}
}
void Pathfinder::setAsWall(int x,int y)
{
	if(x>=0&&y>=0&&x<cols&&y<rows)
		this->nodes[y][x].actAsWall();
}
void Pathfinder::reset()
{
	int k=0;
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			this->nodes[i][j]=Node(j,i);
			this->nodes[i][j].setId(k++);
		}
	}
}
bool Pathfinder::setStart(int x, int y)
{
	bool valid=false;
	if(x>=0&&x<cols&&y>=0&&y<rows)
	{
		startX=x;
		startY=y;
		this->nodes[this->startY][this->startX].setToStartNode();
		valid=true;
	}
	return valid;
}
bool Pathfinder::setEnd(int x, int y)
{
	bool valid=false;
	if(x>=0&&x<cols&&y>=0&&y<rows)
	{
		endX=x;
		endY=y;
		this->nodes[this->endY][this->endX].setToEndNode();
		valid=true;
	}

	return valid;
}

string Pathfinder::getPath()
{
	Path p = Path();
	string stringPath="";
	openList.clear();
	bool startIsEnd=false;
	bool invalidStartEndPos=false;
	
	if(startX==endX&&startY==endY)
			startIsEnd=true;
	
	if(this->startX!=-1&&this->startY!=-1&&this->endX!=-1&&this->endY!=-1)
			invalidStartEndPos=true;
			
	if(!startIsEnd&&invalidStartEndPos)
	{
		Node currentNode;
		this->nodes[startY][startX].setH(this->getDistance(startX,startY,endX,endY)*vertMoveCost);
		int F=this->nodes[startY][startX].getG()+this->nodes[startY][startX].getH();

		openList.push_back(nodes[this->startY][this->startX]);
		int x=this->startX;
		int y=this->startY;

		int pos=0;
		
		while(!currentNode.isEndNode()&&!openList.empty())
		{
			F=openList[0].getH()+openList[0].getG();
			pos=0;
			for(int i=0;i<(int)openList.size();i++)
			{
				if(openList[i].getG()+openList[i].getH()<F)
				{
					F=openList[i].getG()+openList[i].getH();
					pos=i;
				}
			}
			currentNode=openList[pos];
			closedList.push_back(openList[pos]);
			openList.erase(openList.begin()+pos);
			//std::cout <<"x: " << currentNode.getX()<<" y: " << currentNode.getY()<<" F: " <<F<<" G: " << currentNode.getG()<<" H: "<< currentNode.getH()<<std::endl;
			x=currentNode.getX();
			y=currentNode.getY();
		
			//kollar grannar, glöm inte lägga till att kolla för väggar lod och vågrätt
			this->checkNeighbor(currentNode,x+1,y,false,"");
			this->checkNeighbor(currentNode,x-1,y,false,"");
			this->checkNeighbor(currentNode,x,y+1,false,"");
			this->checkNeighbor(currentNode,x,y-1,false,"");
			
			//kollar grannar diagonalt
			this->checkNeighbor(currentNode,x+1,y+1,true,"dr");
			this->checkNeighbor(currentNode,x-1,y+1,true,"dl");
			this->checkNeighbor(currentNode,x+1,y-1,true,"ur");
			this->checkNeighbor(currentNode,x-1,y-1,true,"ul");
		}

		//currentNode = this->nodes[endY][endX];
		stringstream ss;
		vector<Node> tmp;
		while(!currentNode.isStartNode())
		{
			tmp.push_back(currentNode);
			currentNode = this->nodes[currentNode.getParentY()][currentNode.getParentX()];
		}
		tmp.push_back(currentNode);
		
		vector<Node> tmp2;
		while(!tmp.empty())
		{
			ss<<tmp.back().getX()<<"/"<<tmp.back().getY()<<" ";
			tmp.pop_back();
		}
		stringPath=ss.str();

		if(this->openList.empty())
			stringPath="No path found!";
	}
	
	if(startIsEnd)
			stringPath="Already there!";
			
	if(!invalidStartEndPos)
		stringPath="Invalid start/end position";
			
	return stringPath;
}


void Pathfinder::checkNeighbor(Node currentNode,int x, int y,bool diag,string dir)
{
	if(x>=0&&y>=0&&y<rows&&x<cols)
	{
		
		if(!this->isOnClosedList(this->nodes[y][x])&&!this->nodes[y][x].isWall())
		{
			if(!this->isOnOpenList(this->nodes[y][x]))
			{
				if(!diag)
				{
					this->nodes[y][x].setG(currentNode.getG()+vertMoveCost);
					this->nodes[y][x].setH(this->getDistance(x,y,endX,endY)*vertMoveCost);
					this->nodes[y][x].setParent(currentNode.getX(),currentNode.getY());
					this->openList.push_back(this->nodes[y][x]);
				}
				else
				{
					//checks diagonals, too lazy to change the whole sctructure >_<
					if(dir=="dr")
					{
							if(!this->nodes[y-1][x].isWall()&&!this->nodes[y][x-1].isWall())
							{
								this->nodes[y][x].setG(currentNode.getG()+diagMoveCost);
								this->nodes[y][x].setH(this->getDistance(x,y,endX,endY)*vertMoveCost);
								this->nodes[y][x].setParent(currentNode.getX(),currentNode.getY());
								this->openList.push_back(this->nodes[y][x]);
							}
					}
					if(dir=="dl")
					{
							if(!this->nodes[y-1][x].isWall()&&!this->nodes[y][x+1].isWall())
							{
								this->nodes[y][x].setG(currentNode.getG()+diagMoveCost);
								this->nodes[y][x].setH(this->getDistance(x,y,endX,endY)*vertMoveCost);
								this->nodes[y][x].setParent(currentNode.getX(),currentNode.getY());
								this->openList.push_back(this->nodes[y][x]);
							}
					}
						if(dir=="ur")
						{
							if(!this->nodes[y+1][x].isWall()&&!this->nodes[y][x-1].isWall())
							{
								this->nodes[y][x].setG(currentNode.getG()+diagMoveCost);
								this->nodes[y][x].setH(this->getDistance(x,y,endX,endY)*vertMoveCost);
								this->nodes[y][x].setParent(currentNode.getX(),currentNode.getY());
								this->openList.push_back(this->nodes[y][x]);
							}
						}
						if(dir=="ul")
						{
							if(!this->nodes[y+1][x].isWall()&&!this->nodes[y][x+1].isWall())
							{
								this->nodes[y][x].setG(currentNode.getG()+diagMoveCost);
								this->nodes[y][x].setH(this->getDistance(x,y,endX,endY)*vertMoveCost);
								this->nodes[y][x].setParent(currentNode.getX(),currentNode.getY());
								this->openList.push_back(this->nodes[y][x]);
							}
						}
					}
				}
			}
			else
			{
					if(!diag)
					{
						if(currentNode.getG()+vertMoveCost<this->nodes[y][x].getG())
						{
						this->nodes[y][x].setG(currentNode.getG()+vertMoveCost);
						this->nodes[y][x].setParent(currentNode.getX(),currentNode.getY());
						
						}
					}
					else
					{
						if(currentNode.getG()+diagMoveCost<this->nodes[y][x].getG())
						{
						this->nodes[y][x].setG(currentNode.getG()+diagMoveCost);
						this->nodes[y][x].setParent(currentNode.getX(),currentNode.getY());
						}
					}
		}
	}
}

bool Pathfinder::isOnOpenList(Node node)
{
	bool onOpenList=false;
	for(int i=0;i<(int)this->openList.size()&&!onOpenList;i++)
	{
		if(this->openList[i].getId()==node.getId())
			onOpenList=true;
	}
	return onOpenList;
}
bool Pathfinder::isOnClosedList(Node node)
{
	bool onClosedList=false;
	for(int i=0;i<(int)this->closedList.size()&&!onClosedList;i++)
	{
		if(this->closedList[i].getId()==node.getId())
			onClosedList=true;
	}
	return onClosedList;
}

int Pathfinder::getDistance(int x1,int y1, int x2, int y2)
{
	int x,y;
	x=x2-x1;
	y=y2-y1;
	if(x<0)
		x*=-1;
	if(y<0)
		y*=-1;
	/*
	if(x1<x2)
	{
		totalDist+=x2-x1;
	}
	else
		totalDist+=x1-x2;
	if(y1<y2)
	{
		totalDist+=y2-y1;
	}
	else
		totalDist+=y1-y2;
		*/

	return x+y;
}