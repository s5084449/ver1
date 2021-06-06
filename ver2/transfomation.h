//transformation.h

class Node{
public:
	Node() :x(0), y(0), z(0), w(1) {}
	Node(float xx, float yy, float zz): x(xx), y(yy), z(zz), w(1) {}
public:
	float x, y, z, w;
};

class Transformation {
public:
	Transformation() {}
	void set(Node point);
	void Identity();
	Node Translate(float, float, float);
	Node Scale(float, float, float);
	Node Rotate(char, double);
	void MultiMatrix();

public:
	Node POld;//matrix
	float T[4][4];
};
