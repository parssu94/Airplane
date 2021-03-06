#include <GL/glut.h>
#include "src/SOIL.h"
#include <iostream>
#include<string.h>
void* currentfont;
void setFont(void* font)
{
	currentfont=font;
}
void drawstring(float x,float y,float z,char* string)
{
	char* c;
	glRasterPos3f(x,y,z);

	for(c=string; *c!='\0'; c++)
	{	glColor3f(0.0,0.0,0.0);
		glutBitmapCharacter(currentfont,*c);
	}
}
//Sets jimmy's initial position and size.
//rsize equals half of jimmy's height and width
GLfloat x = 0.0f;
GLfloat y = 0.0f;
GLfloat rsize = 8;
int frames = 5, full = 0;
int i = 0;
//Sets the direction and velocity of jimmy at the program initialization
/*The value of these variables defines the amount of pixels along the standard Cartesian coordinate system
Jimmy moves. For example, setting xstep to -2.0f would mean that jimmy would move two pixels
in a certain amount of time defined by the frames variable. The frames variable dictates the amount of milliseconds inbetween each movement of the square.
That means that if frames = 2, I get 50 fps, and therefore 50 movements of jimmy in a second.*/
GLfloat xstep = 0.0f;   //defines mivement. Stopped if 0
GLfloat ystep = 0.0f;

GLfloat windowWidth;
GLfloat windowHeight;

GLuint tex_2d;

void keycrap(unsigned char key, int x, int y)
{
	switch (key)
	{
//32 is the ASCII value of the space key
	case 32:        //to stop jimmy
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
			glutReshapeWindow(800, 600);
			glutPositionWindow(320,150);
			full = 0;
		}
	}
}

void SpecialKeys(int key, int x, int y) //to specify direction of jimmy
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:    //move jimy in right direction
		xstep = 1.0f, ystep = 0.0f;
		break;

	case GLUT_KEY_LEFT:
		xstep = -1.0f, ystep = 0.0f;
		break;

	case GLUT_KEY_DOWN:
		xstep = 0.0f, ystep = -1.0f;
		break;

	case GLUT_KEY_UP:
		xstep = 0.0f, ystep = 1.0f;
		break;
	}

	glutPostRedisplay();
}

void draw_inst_text()
{
	char string[15][120];
	int i,lengthOfString;




	strcpy(string[0],"Instructions:");
	strcpy(string[1],"The main objectiove of this game is to go as far");
	strcpy(string[2],"as possible in your plane, without hitting the");
	strcpy(string[3],"missiles.");
        strcpy(string[4],"Press right mouse button to increase altitude!");
        strcpy(string[5],"Leaving it will automatically take you down.");
        strcpy(string[6],"Keep a close eye on the fuel guage though :P");
        strcpy(string[7],"Have FUN!!!");
	glLineWidth(3);

	glPushMatrix();
	glTranslatef(-40,50,0);
	glScalef(0.3,0.3,0.3);
	lengthOfString = (int)strlen(string[0]);
	for(i=0; i<lengthOfString; i++)
	{
		glColor3f(1,1,1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,string[0][i]);
	}
	glPopMatrix();

        glLineWidth(1);
        int y_pos_21=20;
	for(int k_t=1;k_t<=7;k_t++)
	{
	        glPushMatrix();
                glTranslatef(-40,y_pos_21-=10,0);
                glScalef(0.06,0.06,0.06);
                lengthOfString = (int)strlen(string[k_t]);
                for(i=0; i<lengthOfString; i++)
                {
                        glColor3f(1,1,1);
                        glutStrokeCharacter(GLUT_STROKE_ROMAN,string[k_t][i]);
                }
                glPopMatrix();
	}

}

void RenderScene()
{
//Clears the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);


	glEnable(GL_TEXTURE_2D);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	if (i == 0)
	{
		tex_2d = SOIL_load_OGL_texture
			 (
				 "res/instructions2.png",
				 SOIL_LOAD_RGBA,
				 SOIL_CREATE_NEW_ID,
				 SOIL_FLAG_NTSC_SAFE_RGB
			 );
		i = 1;
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(-178.0f, -100.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(178.0f, -100.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(178.0f, 100.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-178.0f, 100.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	draw_inst_text();
	glutSwapBuffers();
}



void SetupRC(void)
{
//Sets the clear color. Again, the values are in RGBA float format
	glClearColor(0.0f, 0.8f, 0.0f, 1.0f);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//Actually opens the window, initializes all the functions I made, and throws it all into a loop. Hooray!
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800,450);
	glutCreateWindow("Get the Burger 3 - OpenGL");
	glutPositionWindow(320,150);
	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(keycrap);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();

	return 0;
}
