#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/* INCLUDES MARIA */
#include <GL/glut.h>
#include <GL/gl.h>	
#include <GL/glu.h>	

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
GLint     wScreen=800, hScreen=600;


//------------------------------------------------------------ Observador
GLint    defineView=0;
GLint    defineProj=1;
GLfloat  raiox   = 30;
GLfloat  raioz   = 10;
GLfloat  angulo = 0.35*PI;
GLfloat  obsP[] = {raiox*cos(angulo), 10, raioz*sin(angulo)};
GLfloat  incy   = 0.5;
GLfloat  inca   = 0.03;

//------------------------------------------------------------ Texturas
GLint    repete=2;
GLfloat  rr=1;
GLint    maxR  =20;
GLint    numFrames =5; //numero de imagens a colocar em loop na tela
GLint		 curr_frame = 5;
GLint    msec=100;					//.. definicao do timer (actualizacao)

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
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 	imag.LoadBmpFile("paredep.bmp");
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
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 	imag.LoadBmpFile("le.bmp");
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
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
			glTexCoord2f(10.0f,0.0f); glVertex3i( xC, 0, xC );
			glTexCoord2f(10.0f,10.0f); glVertex3i( xC, xC, xC);
			glTexCoord2f(0.0f,10.0f); glVertex3i( 0,  xC,  xC);
		glEnd();
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Parede 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[2]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0 );
			glTexCoord2f(10.0f,0.0f); glVertex3i( xC, 0, 0 );
			glTexCoord2f(10.0f,10.0f); glVertex3i( xC, xC, 0);
			glTexCoord2f(0.0f,10.0f); glVertex3i( 0,  xC,  0);
		glEnd();
	glPopMatrix();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Parede 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[3]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0 );
			glTexCoord2f(10.0f,0.0f); glVertex3i( 0, 0, xC );
			glTexCoord2f(10.0f,10.0f); glVertex3i( 0, xC, xC);
			glTexCoord2f(0.0f,10.0f); glVertex3i( 0,  xC,  0);
		glEnd();
	glPopMatrix();

	//*****************************************************

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
		case 1: gluPerspective(88.0, wScreen/hScreen, 0.1, zC); break;
		default: glOrtho (-xC,xC,-yC,yC,-zC,zC);
			break;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Modelo+View(camera/observador) ]
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0,0,0, 0, 1, 0);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Objectos ]
	drawScene();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}


void Timer(int value)
{
	//TODO: mudar imagem na tela
	if(curr_frame == 1){
		curr_frame = numFrames;
	}
  curr_frame--;
	glutPostRedisplay();
	glutTimerFunc(msec,Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){

	switch (key) {

	//--------------------------- Textura no papel de parede
	case 't':
	case 'T':
		glutPostRedisplay();
		break;
	//--------------------------- Projeccao
	case 'q':
	case 'Q':
		defineProj=(defineProj+1)%2;
		glutPostRedisplay();
		break;
	//--------------------------- Escape
	case 27:
		exit(0);
		break;
  }
}

void teclasNotAscii(int key, int x, int y){
    if(key == GLUT_KEY_UP)
		obsP[1]=obsP[1]+incy;
	if(key == GLUT_KEY_DOWN)
		obsP[1]=obsP[1]-incy;
	if(key == GLUT_KEY_LEFT)
		angulo=angulo+inca;
	if(key == GLUT_KEY_RIGHT)
		angulo=angulo-inca;

	if (obsP[1]> yC)
		obsP[1]= yC;
    if (obsP[1]<-yC)
		obsP[1]=-yC;
    obsP[0] = raiox*cos(angulo);
	obsP[2] = raioz*sin(angulo);

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

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}