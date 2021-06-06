#include "Lsystem.h"
GLfloat PI = 3.14;
Transformation trans;

LSystem::LSystem()
{
}

void LSystem::clearAll()
{
	grammar.clear();
	trunks.clear();
}

void LSystem::initGrammar()//load grammar
{
	grammar.Iteration();
}

void LSystem::generateFractal()
{
	trunks.clear();

	curState.pos = Node(0, 0, 0);
	curState.dir = Node(0, 1, 0);

	State stack[3000];
	for (int i = 0; i < 3000; i++)
	{
		stack[i].pos.x = 0.0;
		stack[i].pos.y = 0.0;
		stack[i].pos.z = 0.0;
		stack[i].dir.x = 0.0;
		stack[i].dir.y = 0.0;
		stack[i].dir.z = 0.0;
	}
	size_t i = 0;
	while (i < grammar.getResult().length())
	{
		TrunkPosition tmp_trunk;
		switch (grammar.getResult()[i])
		{
		case '[':
			stack[stackpointer] = curState;
			stackpointer++;;
			break;
		case ']':
			curState = stack[stackpointer - 1];
			stackpointer--;
			break;
		case '+': //in x axis		 
			trans.set(curState.dir);
			curState.dir = trans.Rotate('X', dx);
			break;
		case '-':
			trans.set(curState.dir);
			curState.dir = trans.Rotate('X', -dx);
			break;
		case '*': //in y axis
			trans.set(curState.dir);
			curState.dir = trans.Rotate('Y', dy);
			break;
		case '/':
			trans.set(curState.dir);
			curState.dir = trans.Rotate('Y', -dy);
			break;
		case '&'://in z axis
			trans.set(curState.dir);
			curState.dir = trans.Rotate('Z', dz);
			break;
		case '%':
			trans.set(curState.dir);
			curState.dir = trans.Rotate('Z', -dz);
			break;
		case 'X':
			tmp_trunk.pos1 = curState.pos;
			curState.pos.x += length * curState.dir.x;
			curState.pos.y += length * curState.dir.y;
			curState.pos.z += length * curState.dir.z;
			tmp_trunk.pos2 = curState.pos;
			tmp_trunk.radius = radius;
			trunks.push_back(tmp_trunk);
			break;
		default:
		}
		i++;
	}
}
