//Lsystem.h
#include <GL/glut.h>
#include "grammar.h"
#include "transfomation.h"


class State      
{
public:
	Node pos;
	Node dir;    
	State() {}
};

class TrunkPosition
{
public:
	Node pos1;
	Node pos2;
	double radius;
	TrunkPosition() {}
};

class LSystem
{
public:
	int stackpointer;
	double dx, dy, dz;    // 
	double length;     // initial length
	double lengthFactor; // 
	double radius;   // initial ruadius
	double radiusFactor;  //
	State curState;  
	double leafRadius;  // 
	Grammar grammar;    // grammar

	vector<TrunkPosition> trunks;//all branches
	LSystem();
	void clearAll();
	void initGrammar();
	void generateFractal();
};