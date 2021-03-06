#include <GL/glut.h>
#include "src/SOIL.h"
#include <iostream>
#define MAX 10
#define UP 1
#define DOWN 0

using namespace std;

float y_pos=-100;
float theta=0;
bool state;
class plane
{
public:
	float x[MAX], y[MAX], i;
	float ymax, ymin;
	int button;
	plane()
	{
		x[1]=-10, x[2]=40, x[3]=-10;
		y[1]=5, y[2]=5, y[3]=-5;
	}
	void draw_plane()
	{
		glColor3f(1,0,0);
		glBegin(GL_TRIANGLES);
		glVertex2f(x[1], y[1]);
		glVertex2f(x[2], y[2]);
		glVertex2f(x[3], y[3]);
		glEnd();
	}
} plane1;

int frames = 5, full = 0;
int i = 0;
//Sets the direction and velocity of airplane at the program initialization
/*The value of these variables defines the amount of pixels along the standard Cartesian coordinate system
airplane moves. For example, setting xstep to -2.0f would mean that airplane would move two pixels
in a certain amount of time defined by the frames variable. The frames variable dictates the amount of milliseconds inbetween each movement of the square.
That means that if frames = 2, I get 50 fps, and therefore 50 movements of airplane in a second.*/
GLfloat xstep = 0.0f;   //defines movement. Stopped if 0
GLfloat ystep = 0.0f;

GLfloat windowWidth;
GLfloat windowHeight;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
//32 is the ASCII value of the space key
	case 32:        //to stop airplane
		xstep = 0.0f, ystep = 0.0f;
		break;

//27 is the ASCII value of the ESC key
	case 27:        //exit game
		exit(0);
		break;

	case 'f':       //full screen
		if (full == 0)
		{
			glutFullScreen();
			full = 1;
		}
		else
		{
			glutReshapeWindow(800, 450);
			glutPositionWindow(320,150);
			full = 0;
		}
	}
}


void mouse(int button, int m_state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON && m_state==GLUT_DOWN)
	{
		state=UP;
		cout<<"Going Up!"<<endl;
	}
	else if(button==GLUT_LEFT_BUTTON && m_state==GLUT_UP)
	{
		state=DOWN;
		cout<<"Going Down"<<endl;
	}
}

void RenderScene()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(-150,y_pos,0);
	glRotatef(theta,0,0,1);
	plane1.draw_plane();
	glPopMatrix();

	glutSwapBuffers();

}

void TimerFunction(int value)
{
	if(state==UP)
	{
		if(y_pos<=90)
			y_pos++;
                if(theta<0)
                        theta+=.3;
		else
                        theta+=.1;
	}
	else
	{
		if(y_pos>=-100)
			y_pos--;
                if(y_pos>-90)
                {
                        if(theta>0)
                                theta-=.3;
                        else
                                theta-=.1;
                }
	}

	glutPostRedisplay();
	glutTimerFunc(frames,TimerFunction, 1);
}

void SetupRC(void)
{
//Sets the clear color. Again, the values are in RGBA float format
	glClearColor(0.0f, 0.8f, 0.0f, 1.0f);
}

void ChangeSize(int w, int h)
{
	GLfloat aspectRatio;

//Prevents a divid by zero. We wouldn't want that, now, would we.
	if(h == 0)
		h = 1;

//Makes sure that the OpenGL viewport fills the whole screen
	glViewport(0, 0, w, h);

//Resets the coordinate system so that the center of the window is (0,0,0) Cartesian x,y,z style
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

//Sets the clipping volume to the dimensions of the window, including depth ^_^
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
	{
		windowWidth = 100;
		windowHeight = 100 / aspectRatio;
		glOrtho (-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
	}
	else
	{
		windowWidth = 100 * aspectRatio;
		windowHeight = 100;
		glOrtho (-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
	}

}

//Actually opens the window, initializes all the functions I made, and throws it all into a loop. Hooray!
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800,450);
	glutCreateWindow("");
	glutPositionWindow(320,150);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();

	return 0;
}
