#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/* INCLUDES MARIA
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
*/

/* includes jorge */
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include "RgbImage.h"

//--------------------------------- Definir cores
#define AZUL     0.0, 0.0, 1.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0, 1.0
#define AMARELO  1.0, 1.0, 0.0, 1.0
#define VERDE    0.0, 1.0, 0.0, 1.0
#define LARANJA  1.0, 0.5, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.9, 0.92, 0.29, 1.0
#define PI		 3.14159

//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat   xC=20.0, yC=20.0, zC=30.0;
GLfloat     wScreen=800.0, hScreen=600.0;
GLfloat     speed = 0.1;
GLfloat    ball_position = 17;
GLint      hit = 0;


//------------------------------------------------------------ Observador
GLint    defineView=0;
GLint    defineProj=1;
GLfloat  obsP[4] ;
GLfloat  inc   = 0.5;

//================================================================================
//=========================================================================== INIT

//------------------------------------------------------------ Texturas
GLuint  texture[10];
GLuint  tex;
RgbImage imag;


void criaDefineTexturas()
{
	//----------------------------------------- Chao y=0
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("chao.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- Parede principal
	glGenTextures(1, &texture[2]);
 	glBindTexture(GL_TEXTURE_2D, texture[2]);
 	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 	imag.LoadBmpFile("ld.bmp");
 	glTexImage2D(GL_TEXTURE_2D, 0, 3,
 	imag.GetNumCols(),
	imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
	imag.ImageData());

 	//----------------------------------------- Parede lado esquerdo
	glGenTextures(1, &texture[3]);
 	glBindTexture(GL_TEXTURE_2D, texture[3]);
 	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 	imag.LoadBmpFile("paredep.bmp");
 	glTexImage2D(GL_TEXTURE_2D, 0, 3,
 	imag.GetNumCols(),
	imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
	imag.ImageData());

	//----------------------------------------- Parede lado direito
	glGenTextures(1, &texture[4]);
 	glBindTexture(GL_TEXTURE_2D, texture[4]);
 	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 	imag.LoadBmpFile("ld.bmp");
 	glTexImage2D(GL_TEXTURE_2D, 0, 3,
 	imag.GetNumCols(),
	imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
	imag.ImageData());
}


void init(void)
{
	glClearColor(BLACK);
	glShadeModel(GL_SMOOTH);
	criaDefineTexturas( );
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}


void resizeWindow(GLsizei w, GLsizei h)
{
 	wScreen=w;
	hScreen=h;
	//glViewport( 0, 0, wScreen,hScreen );
	//glutReshapeWindow(wScreen,hScreen);
	glutPostRedisplay();
}

void draw_cube(void)
{
	glPushMatrix();
   glutSolidCube (0.5);
	 glPopMatrix();

}


void drawScene(){
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=0 com textura
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0 );
			glTexCoord2f(10.0f,0.0f); glVertex3i( xC, 0, 0 );
			glTexCoord2f(10.0f,10.0f); glVertex3i( xC, 0, xC);
			glTexCoord2f(0.0f,10.0f); glVertex3i( 0,  0,  xC);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Parede
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[4]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, xC );
			glTexCoord2f(1.0f,0.0f); glVertex3i( xC, 0, xC );
			glTexCoord2f(1.0f,1.0f); glVertex3i( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3i( 0,  xC,  xC);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Parede
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[2]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0 );
			glTexCoord2f(1.0f,0.0f); glVertex3i( xC, 0, 0 );
			glTexCoord2f(1.0f,1.0f); glVertex3i( xC, xC, 0);
			glTexCoord2f(0.0f,1.0f); glVertex3i( 0,  xC,  0);
		glEnd();
	glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Parede
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[3]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0 );
			glTexCoord2f(1.0f,0.0f); glVertex3i( 0, 0, xC );
			glTexCoord2f(1.0f,1.0f); glVertex3i( 0, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3i( 0,  xC,  0);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//*****************************************************

}



void ball_movement()
{

	if(ball_position <= 0)
	{
		hit = 1;
		printf("BATEU\n");
	}

	if(hit==0)
	{
		ball_position -= speed;
		glutPostRedisplay();
	}
	else if( hit == 1 ){
		ball_position += speed;
		glutPostRedisplay();
	}
}

void display(void){

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Apagar ]
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Janela Visualizacao ]
	glViewport (0,0,wScreen, hScreen);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Projeccao]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (defineProj) {
		case 1: gluPerspective(110, wScreen/hScreen, 0.5, zC); break;
		default: glOrtho (-xC,xC,-yC,yC,-zC,zC);
			break;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Modelo+View(camera/observador) ]
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*
	glRotatef(-20,0,1,0);
	glRotatef(2,0,0,1);
	*/
	gluLookAt(21, 7, 10,-10,-10,10, 0, 1, 0);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Objectos ]

	//cubo 1
	glPushMatrix();
	glColor4f(LARANJA);
	glTranslatef(19.75,1,5+obsP[1]-obsP[2]);
	draw_cube();
	glPopMatrix();

	//cubo 2
	glPushMatrix();
	glColor4f(AMARELO);
	glTranslatef(19.75,1,15+obsP[3]-obsP[4]);
	draw_cube();
	glPopMatrix();

	//bola
	glPushMatrix();
	glColor4f(BLACK);
	glTranslatef(ball_position,0.5,10);
	glutSolidSphere(0.25,20,20);
	glPopMatrix();
	drawScene();

	ball_movement();


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}






//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){

	switch (key) {

	//--------------------------- Textura no papel de parede
	case 'A':
	case 'a':
	if(5+obsP[1]-obsP[2] <= xC-2 )
	{
		obsP[1] = obsP[1] + inc;
	}
		glutPostRedisplay();
		break;
	//--------------------------- Projeccao
	case 'd':
	case 'D':
	if(5+obsP[1]-obsP[2] >= 2)
	{
		obsP[2] = obsP[2]+inc;
	}
		glutPostRedisplay();
		break;
	//--------------------------- Escape

	case 'j':
	case 'J':
		if(15+obsP[3]-obsP[4] <= xC-2)
		{
			obsP[3] = obsP[3] + inc;
		}
		glutPostRedisplay();
		break;

//--------------------------- Escape

case 'L':
case 'l':
if(15+obsP[3]-obsP[4] >= 2)
{
	obsP[4] = obsP[4] + inc;
}
	glutPostRedisplay();
	break;

	case 27:
		exit(0);
		break;
  }

	glutPostRedisplay();
}
//======================================================= MAIN
int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (wScreen, hScreen);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("----------------------------- SQUASH -----------------------------                 Maria Filipa Rosa e Jorge Araujo");

	init();


	glutDisplayFunc(display);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
