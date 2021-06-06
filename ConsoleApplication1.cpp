#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define SOLID 1
#define WIRE 2

int moveX, moveY;
int spinX = 0;
int spinY = 0;
int des = 0;

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
	//initional lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void drawBall(double R, double x, double y, double z, int MODE) {
	glPushMatrix();
	glTranslated(x, y, z);
	if (MODE == SOLID) {
		glutSolidSphere(R, 20, 20);
	}
	else if (MODE == WIRE) {
		glutWireSphere(R, 20, 20);
	}
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
	
	drawBall(2, 0, 1, 0, SOLID);
	drawBall(2, 1, 5, 0, SOLID);

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
	//keybord
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
	return 0;
}