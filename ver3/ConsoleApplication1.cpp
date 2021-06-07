#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "Lsystem.h"

#define SOLID 1
#define WIRE 2

int moveX, moveY;
int spinX = 0;
int spinY = 0;
int des = 0;
GLfloat Pi1 = 3.14159;

Trunk trunk;
LSystem lsrule(trunk);

void init() {
	//init lighting and colour
	GLfloat ambient[] = { 0.5, 0.8, 0.1, 0.1 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { -80.0, 50.0, 25.0, 1.0 };
	//lighting mode
	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat local_view[] = { 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	//ambient light
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//diffuse light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	//lighting positon
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//initional lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	lsrule.initGrammar();
	lsrule.generateFractal();
}


void drawCylinder(double r, double h) {
	for (int i = 0; i < 360; i += 50) { 
		float temp = i * Pi1 / 180;
		float temp1 = (i + 50) * Pi1 / 180;
		glBegin(GL_QUADS);
		glTexCoord2f((temp * r * trunk.radius_shrink) / (2 * Pi1), 0.0f); glVertex3f(r * cos(temp) * trunk.radius_shrink, 0, r * sin(temp) * trunk.radius_shrink);
		glTexCoord2f((temp * r) / (2 * Pi1), 1.0f); glVertex3f(r * cos(temp), h, r * sin(temp)); 
		glTexCoord2f((temp1 * r) / (2 * Pi1), 1.0f); glVertex3f(r * cos(temp1), h, r * sin(temp1));
		glTexCoord2f((temp1 * r * trunk.radius_shrink) / (2 * Pi1), 0.0f); glVertex3f(r * cos(temp1) * trunk.radius_shrink, 0.0f, r * sin(temp1) * trunk.radius_shrink);
		glEnd();
	}

}

void  DrawChannel(Node A, Node B, double r)
{
	// starting with coordinate(0,1,0)  the end coor is(0,1-distance,0)  
	// distance：started by(x1,y1,z1)and end with(x2,y2,z2) 
	// target vector
	GLfloat  dx = B.x - A.x;
	GLfloat  dy = B.y - A.y;
	GLfloat  dz = B.z - A.z;
	// caculate distance
	GLfloat   distance = sqrt(dx * dx + dy * dy + dz * dz);
	// caculate transformation distance  
	GLfloat  px = A.x;
	GLfloat  py = A.y - 1;
	GLfloat  pz = A.z;
	//end vertex coordinate    
	GLfloat  bx = px;
	GLfloat  by = (1 - distance) + py;
	GLfloat  bz = pz;
	//start vector  
	GLfloat  sx = bx - A.x;
	GLfloat  sy = by - A.y;
	GLfloat  sz = bz - A.z;
	// caculate distance between start vector and target vetor  
	GLfloat fx = sy * dz - dy * sz;
	GLfloat fy = sz * dx - sx * dz;
	GLfloat fz = sx * dy - dx * sy;
	//  
	GLfloat ax = fabs(B.x - bx);
	GLfloat ay = fabs(B.y - by);
	GLfloat az = fabs(B.z - bz);
	GLfloat length = sqrt(ax * ax + ay * ay + az * az);
	// caculate  the intersect angle
	GLfloat angle = acos((distance * distance * 2 - length * length) / (2 * distance * distance)) * 180.0f / 3.14159;
	// draw cylinder  
	glPushMatrix(); 
	glTranslatef(A.x, A.y, A.z);
	glRotatef(angle, fx, fy, fz);
	glTranslatef(0, -distance, 0);
	drawCylinder(r, distance);
	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	//init colour
	glColor3f(1.0, 1.0, 1.0);
	//init obj place
	glLoadIdentity();
	//camera position
	gluLookAt(-2.0, -1.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotated(spinX, 0, 1, 0);
	glRotated(spinY, 1, 0, 0);
	glTranslated(0, 0, des);
	
	for (int i = 0; i < lsrule.trunks.size(); i++) {
	/*cout << lsrule.trunks[i].radius << endl;*/
		DrawChannel(lsrule.trunks[i].pos1, lsrule.trunks[i].pos2, lsrule.trunks[i].radius);
	}
	glPopMatrix();
	glutSwapBuffers();
}

void mouseClick(int btn, int state, int x, int y) {
	moveX = x;
	moveY = y;
	GLfloat ambient[] = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 0.1 };
	//environment lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//enable lighting
	glEnable(GL_LIGHT0);
}

void keyPressed(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		spinX -= 2;
		break;
	case 'd':
		spinX += 2;
		break;
	case 'w':
		des += 2;
		break;
	case 's':
		des -= 2;
		break;
	/*case 'c':  //level
		lsrule.grammar.level += 1;
		lsrule.initGrammar();
		lsrule.generateFractal();
		break;
	case 'v':  
		lsrule.grammar.level -= 1;
		lsrule.initGrammar();
		lsrule.generateFractal();
		break;
	case 'q':  
		lsrule.clearAll();
		trunk.length += 0.25;
		lsrule.initGrammar();
		lsrule.generateFractal();
		break;
	case 'e': 
		trunk.length -= 0.25;
		lsrule.clearAll();
		lsrule.initGrammar();
		lsrule.generateFractal();
		break;*/
	}
	glutPostRedisplay();
}
//
void mouseMove(int x, int y) {
	int dx = x - moveX;
	int dy = y - moveY;
	printf("dx;%dx,dy:%dy\n", dx, dy);
	spinX += dx;
	spinY += dy;
	glutPostRedisplay();
	moveX = x;
	moveY = y;
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
	return 0;
}