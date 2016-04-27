#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>

#include "constant.h"
#include "vector3D.h"
#include "SPH.h"

void init() {
	srand(time(NULL));
	
	float light_position[2][4] = {{0, 0, 0.5, 0}, {FRAME_BASE[0], FRAME_BASE[1], FRAME_BASE[2], 1}};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position[0]);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position[1]);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, I02);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, I08);
	glLightfv(GL_LIGHT0, GL_SPECULAR, I);
	glLightfv(GL_LIGHT1, GL_AMBIENT, I02);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, I08);
	glLightfv(GL_LIGHT1, GL_SPECULAR, I);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, I);
	glMaterialf (GL_FRONT, GL_SHININESS, 40);
	
	glClearColor(color4_black[0], color4_black[1], color4_black[2], color4_black[3]);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(height <= 0) {
		height = 1;
	}
	gluPerspective(75.0, (GLfloat)width/(GLfloat)height, 0.5, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawRect(const double *a, double r, double g, double b) {
	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		for (int j=0; j<4; j++)
			glVertex3f(10 * a[j*3], 10 * a[j*3 +1], 30 * a[j*3 +2]);
	glEnd();
}
void drawObject(int index) {
	/*
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	
	glTranslated(lpOuterPoints[index][0], lpOuterPoints[index][1], -20);
	glRotated(angle[index], rotate[index][0], rotate[index][1], rotate[index][2]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color[index]);
	
	if (index == torus)
		glutSolidTorus(1, 2, 30, 30);
	else if (index == teapot)
		glutSolidTeapot(3);
	else if (index == sphere) {
		glScalef(sphereSize, sphereSize, sphereSize);
		glutSolidSphere(2.0, 100, 100);
	} else if (index == cone) {
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glutSolidCone(1.5, 3.2, 35, 35);
	} else if (index == cube) {
		glTranslated(0, 0, cubePosition);
		glRotatef(17, 0, 1, 0);
		glutSolidCube(3);
	} else  {
		glRotated(angle[5], 1, 0, 0);
		glRotated(angle[6], 0, 1, 0);
		glRotatef(45, 1, 1, 1);
		glMap2d(GL_MAP2_VERTEX_3, 0, 1, 12, 2, 0, 1, 3, 4, &Bezier[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glEnable(GL_NORMALIZE);
		glMapGrid2d(50, 0, 1, 50, 0, 1);
		glEvalMesh2(GL_FILL, 0, 50, 0, 50);
	}
	glPopMatrix();	
	*/
}

void drawEdge(const float _pos[], const float _scale[]) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color4_white);
	
	glTranslatef(_pos[0], _pos[1], _pos[2]);
	glRotated(0, 0, 0, 0);
	glScalef(_scale[0], _scale[1], _scale[2]);
	glutSolidCube(1);
	
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
//	glEnable(GL_COLOR_MATERIAL);
	for (int i = 0; i < 12; i++) {
		drawEdge(WALL_EDGE[i], WALL_SCALE[i]);
	}
//	for (i=0; i<5; i++) drawRect(wall[i], Wcolor[i][0], Wcolor[i][1], Wcolor[i][2]);
//	glDisable(GL_COLOR_MATERIAL);
	
//	for (i=1; i<8; i++) 
//		if (i != 6) drawObject(i);
	
	glFlush();
	glutSwapBuffers();
}


void render(int value) {
	/*
	//torus = 1, teapot = 2, sphere = 3, cone = 4, spline_y = 5, spline_x =6, cube =7;
	if (status == sphere) {
		if (sphereSize > 1.5 || sphereSize < 0.5) sphereDelta *= -1.0;
		sphereSize += sphereDelta;
	} else if (status == cube) {
		if (cubePosition > 6 || cubePosition < -6) cubeDelta *= -1.0;
		cubePosition += cubeDelta;
	} else angle[status] = (angle[status] + 10) % 360;
*/
	glutTimerFunc(40, render, 0);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	/*
	switch (key) {
		case 'q':
		case 'Q':
			status = 0;
			break;
		case 27:
			exit(0);
			break;
		default:
			status = key - 48;
	}
	*/
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SPH - ^.^");

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(40, render, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	
	return 0;
}
