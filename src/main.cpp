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
#include "MarchingCube.h"

using namespace std;

SPH sph;

bool debug = false;
bool is_press = false;
Vector3D pos_pre, pos_now;

void init() {
	srand(time(NULL));
	sph = SPH(FRAME_LENGTH);
	
	GLfloat light_position[2][4] = {{0, 0, 0.5, 0}, {(float)FRAME_BASE[0], (float)FRAME_BASE[1], (float)FRAME_BASE[2], 1}};
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
	
//	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void reshape(GLsizei width, GLsizei height) {
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	width = WINDOW_WIDTH; height = WINDOW_HEIGHT;
	
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(height <= 0) {
		height = 1;
	}
	gluPerspective(75.0, (GLdouble)width/(GLdouble)height, 0.5, 500);

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

void drawEdge(const double _pos[], const double _scale[]) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color4_white);
	
	glTranslatef(_pos[0] + FRAME_BASE[0], _pos[1] + FRAME_BASE[1], _pos[2] + FRAME_BASE[2]);
	glRotated(0, 0, 0, 0);
	glScalef(_scale[0], _scale[1], _scale[2]);
	//glScalef(FRAME_SCALE[0], FRAME_SCALE[1], FRAME_SCALE[2]);		
	glutSolidCube(1);
	
	glPopMatrix();
}

void drawSphere(const Vector3D _pos) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color4_sphere);
	
	glTranslatef(_pos[0] + FRAME_BASE[0], _pos[1] + FRAME_BASE[1], _pos[2] + FRAME_BASE[2]);
	//glScalef(FRAME_SCALE[0], FRAME_SCALE[1], FRAME_SCALE[2]);	
	glRotated(0, 0, 0, 0);
	glutSolidSphere(0.03f, 100, 100);
	
	glPopMatrix();	
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (int i = 0; i < 12; i++) {
		drawEdge(WALL_EDGE[i], WALL_SCALE[i]);
	}
	
//	drawSphere(Vector3D(0, 0, 0));

	if (debug) {
		list<Particle> particle_list = sph.getList();
		for (Particle &particle : particle_list) {
			drawSphere(particle.getPosition());
			/*
			Vector3D p = particle.getPosition();
			printf("position: %lf, %lf, %lf\n", p[0], p[1], p[2]);
			p = particle.getVelocity();
			printf("velocity: %lf, %lf, %lf\n", p[0], p[1], p[2]);
			*/
		}
	} else {
		list<Particle> particle_list = sph.getList();
		vector<Vector3D> v_list;
		vector<int> index_list;
		MarchingCube marching_cube(FRAME_LENGTH, GRID_LENGTH, &particle_list);
		marching_cube.count(v_list, index_list);
		
		// printf("size: %d\n", (int)index_list.size());

		glEnable(GL_COLOR_MATERIAL);
		glBegin(GL_TRIANGLES);
			glColor4f(color4_sphere[0], color4_sphere[1], color4_sphere[2], color4_sphere[3]);
			for (int i = 0; i < index_list.size(); ++i) {
				int p = index_list[i];
				glVertex3f(v_list[p][0] + FRAME_BASE[0], v_list[p][1] + FRAME_BASE[1], v_list[p][2] + FRAME_BASE[2]);
			}
		glEnd();	
		glDisable(GL_COLOR_MATERIAL);
	}
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
	// move speed
	if (pos_now[0] != pos_pre[0] || pos_now[1] != pos_pre[1] || pos_now[2] != pos_pre[2]) {
		Vector3D delta = pos_now - pos_pre;
		Vector3D base_new = Vector3D(FRAME_BASE) + delta;
		for (int i = 0; i < 2; ++i) {
			if (abs(base_new[i]) > FRAME_LENGTH[i] * 2) {
				base_new[i] = base_new[i] / abs(base_new[i]) * (FRAME_LENGTH[i] - 0.0001);
			}
		}
		delta = base_new - FRAME_BASE;
		for (int i = 0; i < 3; ++i) FRAME_BASE[i] = base_new[i];
		pos_pre = pos_now;
		sph.setBase(delta);
		
//		printf("base %lf, %lf, %lf\n", FRAME_BASE[0], FRAME_BASE[1], FRAME_BASE[2]);
	}
	
	// cout movement
	sph.move();
	glutTimerFunc(DELTA_TIME, render, 0);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
			sph.add(Particle(Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
			break;
		case 'c':
			debug = !debug;
			break;
		case 's':
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

Vector3D coordinateTrans(int x, int y) {
	x -= WINDOW_WIDTH / 2; y -= WINDOW_HEIGHT / 2;
	return Vector3D((x + 0.0) / WINDOW_WIDTH * (FRAME_LENGTH[0] * 2.2f), (y + 0.0) / WINDOW_HEIGHT * (FRAME_LENGTH[1] * 2.2f) * -1, 0);
}

void mousepress(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			is_press = true;
			pos_pre = coordinateTrans(x, y);	
			pos_now = pos_pre;
		} else if (state == GLUT_UP) {
			is_press = false;
		}
	}
}

void mousemove(int x, int y) {
	if (is_press) {
		pos_now = coordinateTrans(x, y);
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SPH - ^.^");

	init();
// sph.add(Particle(Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
	
	for (int i = 0; i < 12; i+=1 )
		for (int j = 0; j < 12; j+=1)
			for (int k = 0; k < 12; k+=1)
				sph.add(Particle(Vector3D(-0.50 + i * 0.03, -0.2 + j * 0.03, -0.05 + k * 0.03), Vector3D(0, 0, 0)));
				//sph.add(Particle(Vector3D(0 + i, 0 + j * 0.8, 0 + k), Vector3D(0, 0, 0)));

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mousepress);
	glutMotionFunc(mousemove);
	glutTimerFunc(DELTA_TIME, render, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	
	return 0;
}
