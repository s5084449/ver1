#include "transfomation.h"
#include <iostream>
#include <math.h>

double PI = 3.1415926;
using namespace std;

void Transformation::set(Node point)
{
	POld = point;
}

void Transformation::Identity()//matrix identify function
{
	T[0][0] = 1.0; T[0][1] = 0.0; T[0][2] = 0.0; T[0][3] = 0.0;
	T[1][0] = 0.0; T[1][1] = 1.0; T[1][2] = 0.0; T[1][3] = 0.0;
	T[2][0] = 0.0; T[2][1] = 0.0; T[2][2] = 1.0; T[2][3] = 0.0;
	T[3][0] = 0.0; T[3][1] = 0.0; T[3][2] = 0.0; T[3][3] = 1.0;
}

Node Transformation::Translate(float tx, float ty, float tz)//translation
{
	Identity();
	T[3][0] = tx;
	T[3][1] = ty;
	T[3][2] = tz;
	MultiMatrix();

	return POld;
}

Node Transformation::Scale(float sx, float sy, float sz)//scale up or down
{
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	T[2][2] = sz;
	MultiMatrix();

	return POld;
}

Node Transformation::Rotate(char shift, double beta) //caculate the rotated angle along axis
{
	Identity();
	double radium = (beta * PI) / 180;
	switch (shift)
	{
	case 'X': //x axis
		T[0][0] = 1;
		T[1][1] = cos(radium); T[1][2] = sin(radium);
		T[2][1] = -sin(radium); T[2][2] = sin(radium);
		break;
	case 'Y':// y axis
		T[0][0] = cos(radium); T[0][2] = -sin(radium);
		T[1][1] = 1;
		T[2][0] = sin(radium); T[2][2] = cos(radium);
		break;
	case 'Z'://z axis
		T[0][0] = cos(radium); T[0][1] = sin(radium);
		T[1][0] = -sin(radium); T[1][1] = cos(radium);
		T[2][2] = 1;
	}
	MultiMatrix();
	return POld;
}

void Transformation::MultiMatrix()
{
	Node PNew = POld;

	POld.x = PNew.x * T[0][0] + PNew.y * T[1][0] + PNew.z * T[2][0] + PNew.w * T[3][0];
	POld.y = PNew.x * T[0][1] + PNew.y * T[1][1] + PNew.z * T[2][1] + PNew.w * T[3][1];
	POld.z = PNew.x * T[0][2] + PNew.y * T[1][2] + PNew.z * T[2][2] + PNew.w * T[3][2];
	POld.w = PNew.x * T[0][3] + PNew.y * T[1][3] + PNew.z * T[2][3] + PNew.w * T[3][3];
}
