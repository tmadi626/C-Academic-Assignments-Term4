// C++ Implementation of Quadtree Tree
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
#define NUM_POINTS 1998

// Used to hold details of a point
struct Point
{
	float x;
	float y;
	Point(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	Point()
	{
		x = 0.0f;
		y = 0.0f;
	}
};

// The objects that we want stored in the quadtree
struct Node
{
	Point pos;
	int index;
	Node(Point _pos, int _index)
	{
		pos = _pos;
		index = _index;
	}
	Node()
	{
		index = -1;
	}
};

// The main quadtree class
class Quadtree
{
	private:
	// Contains details of node
	Node *n;

	// Children of this tree
	Quadtree *topLeftTree;
	Quadtree *topRightTree;
	Quadtree *botLeftTree;
	Quadtree *botRightTree;

	public:
	// Hold details of the boundary of this node
	Point topLeft;
	Point botRight;
	Quadtree()
	{
		topLeft = Point(0, 0);
		botRight = Point(0, 0);
		n = NULL;
		topLeftTree = NULL;
		topRightTree = NULL;
		botLeftTree = NULL;
		botRightTree = NULL;
	}
	Quadtree(Point topL, Point botR)
	{
		n = NULL;
		topLeftTree = NULL;
		topRightTree = NULL;
		botLeftTree = NULL;
		botRightTree = NULL;
		topLeft = topL;
		botRight = botR;
	}
	void insert(Node*);
	void findclosest(Point, float*, int*);
	bool inBoundary(Point);
	float distance(float pTree, float p);

};

// Insert a node into the quadtree
void Quadtree::insert(Node *node)
{
	if (node == NULL)
		return;

	// Current quad cannot contain it
	if (!inBoundary(node->pos))
		return;

	if (n == NULL)
	{
		n = node;
	}
	else {	

		if ((topLeft.x + botRight.x) / 2 >= node->pos.x)
		{
			// Indicates topLeftTree
			if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
			{
				if (topLeftTree == NULL)
					topLeftTree = new Quadtree(Point(topLeft.x, topLeft.y),Point((topLeft.x + botRight.x) / 2, (topLeft.y + botRight.y) / 2));
				topLeftTree->insert(node);
			}
	
			// Indicates botLeftTree
			else
			{
				if (botLeftTree == NULL)
					botLeftTree = new Quadtree(Point(topLeft.x,(topLeft.y + botRight.y) / 2),Point((topLeft.x + botRight.x) / 2,botRight.y));
				botLeftTree->insert(node);
			}
		}
		else
		{
			// Indicates topRightTree
			if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
			{
				if (topRightTree == NULL)
					topRightTree = new Quadtree( Point((topLeft.x + botRight.x) / 2, topLeft.y), Point(botRight.x, (topLeft.y + botRight.y) / 2));
				topRightTree->insert(node);
			}
	
			// Indicates botRightTree
			else
			{
				if (botRightTree == NULL)
					botRightTree = new Quadtree(Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),Point(botRight.x, botRight.y));
				botRightTree->insert(node);
			}
		}
	}
}

float Quadtree::distance(float pTree, float p){
	return abs(pTree-p);
}

// Finds the closest node to the point p in the quadtree
// Returns the closest node's Euclidean distance in bestdist and the index of the
// closest node in bestindex.
// A mostly empty stub is provided below.
void Quadtree::findclosest(Point p, float* bestdist, int* bestindex)
{
	//the node is NULL means no poin inserted as we need points to make a node
	if( n == NULL ){
		return;
	}
	//if it is still in boundries and if this node is not null then it means the point is here //this is where we change the variables //then keep digging further in the quad tree and sub quads
	else if( n != NULL ){
		float x = n->pos.x;
		float y = n->pos.y;
		float d = sqrt( pow(p.x - x , 2) + pow(p.y - y , 2) );

		if(d<= *bestdist){
			*bestdist = d;
			*bestindex = n->index;
		}

		if( this->topLeftTree != NULL ){
			if(topLeftTree->n != NULL ){

				if(topLeftTree->inBoundary(p)  ||(distance(topLeftTree->botRight.x, p.x)<=*bestdist && distance(topLeftTree->botRight.y, p.y)<=*bestdist)){
					topLeftTree->findclosest(p, bestdist, bestindex);
				}
			}
		}
		if( this->topRightTree != NULL ){
			if( topRightTree->n != NULL ){
				if(topRightTree->inBoundary(p) ||(distance(topRightTree->topLeft.x, p.x)<=*bestdist && distance(topRightTree->botRight.y, p.y)<=*bestdist)){ //something changed<<<
					topRightTree->findclosest(p, bestdist, bestindex);
				}
			}
		}
		if( this->botLeftTree != NULL ){
			if(botLeftTree->n != NULL ){

				if(botLeftTree->inBoundary(p)||(distance(botLeftTree->botRight.x, p.x)<=*bestdist && distance(botLeftTree->topLeft.y, p.y)<=*bestdist)){
					botLeftTree->findclosest(p, bestdist, bestindex);
				}
			}
		}
		if( this->botRightTree != NULL ){
			if(botRightTree->n != NULL ){

				if(botRightTree->inBoundary(p)  ||(distance(botRightTree->topLeft.x, p.x)<=*bestdist && distance(botRightTree->topLeft.y, p.y)<=*bestdist)){
					botRightTree->findclosest(p, bestdist, bestindex);
				}
			}
		}
		if(this->topLeftTree == NULL && this->topRightTree == NULL && this->botLeftTree == NULL && this->botRightTree == NULL){
			return;
		}
	}
};

// Check if current quadtree contains the point
bool Quadtree::inBoundary(Point p){
	return (p.x >= topLeft.x &&
		p.x <= botRight.x &&
		p.y >= topLeft.y &&
		p.y <= botRight.y);
}

// Driver program
int main()
{
	srand(time(NULL));
	Point p1(0,0);
	Point p2(1000,1000);
	Quadtree Square(p1, p2);
	Point p[NUM_POINTS];
	cout << "Program started, this is good"<< endl;
	cout << "Number of points inserted: "<< NUM_POINTS << endl;

	// Insert randomly generated points into quadtree
	for (int i = 0; i < NUM_POINTS; i++)
	{
		p[i] = Point( (float) rand()/RAND_MAX*1000, (float) rand()/RAND_MAX*1000 );
		Node* point = new Node(p[i], i);
		Square.insert(point);
	}
	float d = 10000;
	int index = -1;
	Point searchpoint(600,600);
	cout << "searching for Point: 600, 600"<< endl;

	// Search for closest point to searchpoint in the quadtree with your implementation of the search function
	Square.findclosest(searchpoint,&d, &index);
	float curdist;
	float bestdist = 1000000;
	int bestindex;

	// Find the closest point index and distance by searching through the randomly generated points 
	// sequentially.
	for (int i = 0; i < NUM_POINTS; i++)
	{
		curdist = sqrt((p[i].x-searchpoint.x)*(p[i].x-searchpoint.x)+(p[i].y-searchpoint.y)*(p[i].y-searchpoint.y));
		if (curdist < bestdist)
		{
			bestdist = curdist;
			bestindex = i;
		}
	}

	// If your search function worked correctly, then the closest distance and closest point index 
	// should be the same from the search function as from a brute-force search
	if ((fabs(d-bestdist)>0.01) || (index != bestindex))
		cout << "The correct closest point index and distance were not found correctly." << endl;
	else
		cout << "Congratulations! The correct closest point index and distance were found!" << endl;
	return 0;
}
