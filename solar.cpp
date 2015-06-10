#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstring>
#define _USE_MATH_DEFINES
#include <math.h>

static GLfloat angle = 0.0;

GLfloat degreeZ = 0;
GLfloat degreeX = 0;

GLfloat dist = 50.0;

char Sun[4] = "Sun";
char planet[8][10] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};

GLUquadric *saturnRing;

class Camera {
public:
	GLfloat angleX;
	GLfloat angleY;
	GLfloat angleZ;
	GLfloat directionX;
	GLfloat directionZ;
	GLfloat directionY;
	GLfloat xPos;
	GLfloat zPos;
	GLfloat yPos;
	GLfloat Tilt;
	GLfloat Up;
public:
	Camera() {
		initialize();
	}

	void setPosition(float xDir, float yDir, float zDir, float posX, float posZ, float posY) {
		directionX = xDir;
		directionZ = zDir;
		directionY = yDir;
		xPos = posX;
		zPos = posZ;
		yPos = posY;
	}

	void initialize() {
		angleX = 0.0;
		angleY = 0.0;
		angleZ = 0.0;
		directionX = 0.0;
		directionZ = -5.0;
		directionY = 0.0;
		xPos = 0.0;
		zPos = 1.0;
		yPos = 0.0;
		Tilt = 0.0;
		Up = 1.0;
		Tilt = 0.0;
	}

	~Camera(void){}
};

Camera camera;

class Orbit {
public : 
	float x, y, rot;
	void createOribit (int k, int r, int h) {
		glColor3f(0.8, 0.8, 0.8);
		glBegin(GL_LINES);
		for (int i = 0; i < 180; i++) {
			x = r * cos(i + 0.0) - h;
			y = r * sin(i + 0.0) + k;
			glVertex3f(x + k,y - h,0);

			x = r * cos(i + 0.1) - h;
			y = r * sin(i + 0.1) + k;
			glVertex3f(x + k,y - h,0);
		}
		glEnd();
	}
};

void MyTimer(int Value) {
	angle += 0.5;
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

void MySpecialKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			degreeZ -=1;
			break;
		case GLUT_KEY_RIGHT: 
			degreeZ +=1;
			break;
		case GLUT_KEY_UP:
			degreeX -= 1;
			break;
		case GLUT_KEY_DOWN:
			degreeX += 1;
			break;
		default:
			break;
	}
	if(degreeZ > 360)
		degreeZ = 0;
	else if(degreeZ < 0)
		degreeZ = 360;

	glutPostRedisplay();
}

void MyKeyboard(unsigned char key,int x, int y) {
	switch(key) {
		case '-':
			// camera go backward
			camera.xPos -= camera.directionX * 0.3f;
			camera.zPos -= camera.directionZ * 0.3f;
			camera.yPos -= camera.directionY * 0.3f;
			break;
		case '+':
			// camera go forward
			camera.xPos += camera.directionX * 0.3f;
			camera.zPos += camera.directionZ * 0.3f;
			camera.yPos += camera.directionY * 0.3f;
			break;
		// pilot view from here
		case 'd':
			camera.angleY += 0.01f;
			camera.directionX = sin(camera.angleY);
			camera.directionZ = -cos(camera.angleY);
			break;
		case 'a':
			camera.angleY -= 0.01f;
			camera.directionX = sin(camera.angleY);
			camera.directionZ = -cos(camera.angleY);
			break;
		case 'w':
			camera.angleX += 0.01f;
			camera.directionY = sin(camera.angleX);
			camera.directionZ = -cos(camera.angleX);
			break;
		case 's':
			camera.angleX -= 0.01f;
			camera.directionY = sin(camera.angleX);
			camera.directionZ = -cos(camera.angleX);
			break;
		case 'q':
			camera.angleZ += 0.01f;
			camera.Tilt = sin(camera.angleZ);
			camera.Up = cos(camera.angleZ);
			break;
		case 'e':
			camera.angleZ -= 0.01f;
			camera.Tilt = sin(camera.angleZ);
			camera.Up = cos(camera.angleZ);
			break;
		case 'b':
			camera.angleY += M_PI;
			camera.angleX += M_PI;
			camera.directionX = sin(camera.angleY);
			camera.directionZ = -cos(camera.angleY);
			camera.directionY = sin(camera.angleX);
			break;
		case '0':
			camera.initialize();
			degreeX = degreeZ = 0;
			dist = 50;
	}
	
	glutPostRedisplay();
}

void PolarView(GLfloat radius, GLfloat elevation, GLfloat azimuth, GLfloat twist) {
	glTranslatef(0.0, 0.0, -radius);
	glRotated(-twist, 0.0, 0.0, 1.0);
	glRotated(-elevation, 1.0, 0.0, 0.0);
	glRotated(-azimuth, 0.0, 1.0, 0.0);
}

void drawSun() {
	glRotatef(angle /30, 0.0, 1.0, 0.0);
	glutWireSphere(2.0, 20, 20);
	glScalef(0.005, 0.005, 0.005);
	glTranslatef(-50.0, -530, 0.0);

	int nameLen = (int)strlen(Sun);
	glPushMatrix();

	for (int i = 0; i < nameLen; i++) {
		glColor3f(1.0, 1.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, Sun[i]);
	}
	glPopMatrix();	
}

void drawplanet(float angle1, float x, float size, char * planetName) {	
	glRotatef(angle/angle1 , 0, 1 , 0);
	glTranslated(x, 0.0, 0.0);
	glPushMatrix();

	glutSolidSphere(size, 100, 100);
	glPopMatrix();

	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(0.005, 0.005, 0.005);
	glTranslatef(-50.0, -100-size*200, 0.0);

	glPushMatrix();

	int nameLen = (int)strlen(planetName);
	for (int i = 0; i < nameLen; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, planetName[i]);
	}

	glPopMatrix();

}

void MyDisplay() {
	angle += 0.5;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(67, 1.0, 0.1, 500.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camera.xPos, camera.yPos, camera.zPos,
			  camera.xPos+camera.directionX, camera.yPos+camera.directionY, camera.zPos+camera.directionZ,
			  camera.Tilt, camera.Up, 0.0);

	PolarView(dist, degreeX, degreeZ, 0.0);

	
	// Sun
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	drawSun();
	glPopMatrix();
	
	// Mercury
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	drawplanet(0.2409, 3.0, 0.039, planet[0]);
	glPopMatrix();
	
	// Venus
	glColor3f(0.8, 0.8, 0.32);
	glPushMatrix();
	drawplanet(0.6102, 5.0, 0.09, planet[1]);
	glPopMatrix();

	// Earth
	glColor3f(0.0, 0.3, 1.0);
	glPushMatrix();
	drawplanet(1.0, 7.0, 0.1, planet[2]);
	glPopMatrix();

	// Mars
	glColor3f(0.8, 0.5, 0.3);
	glPushMatrix();
	drawplanet(1.8809, 9.0, 0.053, planet[3]);
	glPopMatrix();
	
	// Jupiter
	glColor3f(0.5, 0.3, 0.1);
	glPushMatrix();
	drawplanet(11.862, 13.0, 1.30, planet[4]);
	glPopMatrix();

	// Saturn
	saturnRing = gluNewQuadric();
	glColor3f(0.8, 0.5, 0.3);
	glPushMatrix();
	drawplanet(29.458, 18.0, 1.12, planet[5]);
	glPopMatrix();	
	// Saturn ring
	glPushMatrix();
		glColor3f(0.9, 0.6, 0.4);
		glRotatef(angle/29.458 , 0, 1 , 0);
		glRotatef(90 , 1, 0 , 0);
		glTranslated(18.0, 0.0, 0.0);
		gluDisk(saturnRing, 1.5, 2.0, 100, 100);
	glPopMatrix();

	// Uranus
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	drawplanet(84.022, 22.0, 0.6, planet[6]);
	glPopMatrix();

	// Neptune
	glColor3f(0.4, 0.4, 1.0);
	glPushMatrix();
	drawplanet(164.774, 28.0, 0.56, planet[7]);
	glPopMatrix();

	/* planet finish */

	glRotatef(90, 1.0, 0.0, 0.0);
	Orbit *orbit = new Orbit();
	orbit->createOribit(3, 3, 3);
	orbit->createOribit(5, 5, 5);
	orbit->createOribit(7, 7, 7);
	orbit->createOribit(9, 9, 9);
	orbit->createOribit(13, 13, 13);
	orbit->createOribit(18, 18, 18);
	orbit->createOribit(22, 22, 22);
	orbit->createOribit(28, 28, 28);

	glutSwapBuffers();
}

int main (int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Solar System");

	glClearColor(0.0, 0.0, 0.0, 1.0);
	//glPointSize(5);
	glEnable(GL_DEPTH_TEST);

	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecialKey);
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(40, MyTimer, 1);
	glutMainLoop();
	return 0;
}