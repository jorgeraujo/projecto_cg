#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
// INCLUDES MARIA
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//INCLUDES JORGE
/*#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>*/

#include "RgbImage.h"

// Definir cores
#define AZUL     0.0, 0.0, 1.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0, 1.0
#define AMARELO  1.0, 1.0, 0.0, 1.0
#define VERDE    0.0, 1.0, 0.0, 1.0
#define LARANJA  1.0, 0.5, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.9, 0.92, 0.29, 1.0
#define PI		 3.14159

// Sistema Coordenadas
GLfloat   xC=20.0, yC=20.0, zC=30.0;
GLfloat   wScreen=800.0, hScreen=600.0;
GLfloat   speed = 0.1;
GLfloat   ball_speed_x = 0.09;
GLfloat   ball_speed_z;
GLfloat   ball_position_x = 10;
GLfloat 	ball_position_z = 10;
GLfloat 	ball_position_y;
GLfloat   cube1_position_x;
GLfloat   cube1_position_z;
GLint     hit = 0;
GLint 		exit_game=0;
GLint 		pause_game=0;
GLfloat   jump_coordinate;
GLfloat   jump_speed = 0.20;
GLfloat  	inc   = 0.5;
GLint     jump = 0;

// Observador
GLint    defineView=0;
GLint    defineProj=1;
GLfloat  obsP[5];


//iluminacao
int light=1;
GLfloat corLuzA[]={1.0f, 1.0f, 1.0f, 1.0f};
GLfloat corLuzD[]={1.f, 1.0f, 1.0f, 1.0f};
GLfloat corLuzE[]={0.2f, 0.2f, 0.2f, 1.0f};
GLfloat posicaoLuz[] = {0.0, 20.0, 0.0, 1.0};
GLfloat direcaoLuz[]={0.0f,1.0f,0.0f};
GLfloat concentracaoLuz=20.0;
GLfloat anguloLuz=90.0;

GLfloat yellowRubberDiffuse[]={0.5,0.5,0.4,1};
GLfloat yellowRubberSpecular[]={0.7,0.7,0.04};
GLfloat yellowRubberShininess=.078125*128;

GLfloat rubyDiffuse[]={0.61424,0.04136,0.04136,1};
GLfloat rubySpecular[]={0.727811,0.626959,0.626959};
GLfloat rubyShininess=0.6*128;

GLfloat pretoDiffuse[]={0.01,0.01,0.01,1};
GLfloat pretoSpecular[]={0.01,0.01,0.01};
GLfloat pretoShininess=0;

GLfloat GlassDiffuse []={ 0.1, 0.1, 0.1, 0.3};
GLfloat GlassSpecular []={ 1, 1, 1};
GLint GlassShininess = 1;

// Texturas
GLuint  texture[10];
GLuint  tex;
RgbImage imag;


void criaDefineTexturas(){
	// Chao y=0
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("chao.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	// Parede principal
	glGenTextures(1, &texture[2]);
 	glBindTexture(GL_TEXTURE_2D, texture[2]);
 	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 	imag.LoadBmpFile("ld.bmp");
 	glTexImage2D(GL_TEXTURE_2D, 0, 3,
 	imag.GetNumCols(),
	imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
	imag.ImageData());

 	// Parede lado esquerdo
	glGenTextures(1, &texture[3]);
 	glBindTexture(GL_TEXTURE_2D, texture[3]);
 	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 	imag.LoadBmpFile("paredep.bmp");
 	glTexImage2D(GL_TEXTURE_2D, 0, 3,
 	imag.GetNumCols(),
	imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
	imag.ImageData());

	// Parede lado direito
	glGenTextures(1, &texture[4]);
 	glBindTexture(GL_TEXTURE_2D, texture[4]);
 	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_LINEAR);
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

void iluminacao(){
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	/*glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.00f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);*/

	glLightfv(GL_LIGHT0, GL_AMBIENT, corLuzA);

	glLightfv(GL_LIGHT0, GL_SPECULAR, corLuzE);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, corLuzD);

  /* glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	 glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direcaoLuz);
	 glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, concentracaoLuz);
	 glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, anguloLuz);
	 glLightfv(GL_LIGHT0, GL_SPECULAR, corLuz);
	 glLightfv(GL_LIGHT0, GL_DIFFUSE, corLuz);
*/}


void init(void){
	glEnable(GL_NORMALIZE);
	glClearColor(BLACK);
	glShadeModel(GL_SMOOTH);
	criaDefineTexturas( );
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	iluminacao();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void resizeWindow(GLsizei w, GLsizei h){
 	wScreen=w;
	hScreen=h;
	//glViewport( 0, 0, wScreen,hScreen );
	//glutReshapeWindow(wScreen,hScreen);
	glutPostRedisplay();
}

void writeText(char *string, GLfloat x, GLfloat y, GLfloat z)
{
	glColor4d(VERMELHO);
	glRasterPos3f(x,y,z);
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}

void draw_cube(void){
	glPushMatrix();
   glutSolidCube (0.5);
	 glPopMatrix();
}

void drawScene(){
	// Chao
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glPushMatrix();
		glBegin(GL_QUADS);
		//glColor4f(0.0,0.0,0.0,0.0);
			glNormal3f(0.0, 1.0, 0.0);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0 );
			glTexCoord2f(10.0f,0.0f); glVertex3i( xC, 0, 0 );
			glTexCoord2f(10.0f,10.0f); glVertex3i( xC, 0, xC);
			glTexCoord2f(0.0f,10.0f); glVertex3i( 0,  0,  xC);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Parede lado esquerdo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[4]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, -1.0);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, xC );
			glTexCoord2f(1.0f,0.0f); glVertex3i( xC, 0, xC );
			glTexCoord2f(1.0f,1.0f); glVertex3i( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3i( 0,  xC,  xC);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Parede lado direito
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[2]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0 );
			glTexCoord2f(1.0f,0.0f); glVertex3i( xC, 0, 0 );
			glTexCoord2f(1.0f,1.0f); glVertex3i( xC, xC, 0);
			glTexCoord2f(0.0f,1.0f); glVertex3i( 0,  xC,  0);
		glEnd();
	glPopMatrix();
		glDisable(GL_TEXTURE_2D);

//parede frente
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[3]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glNormal3f(1.0, 0.0, 0.0);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0 );
			glTexCoord2f(1.0f,0.0f); glVertex3i( 0, 0, xC );
			glTexCoord2f(1.0f,1.0f); glVertex3i( 0, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3i( 0,  xC,  0);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//parede tras
void drawScene1(){
		glPushMatrix();
			glBegin(GL_QUADS);
				glColor4f(1.0,1.0,1.0,0.5);
				glNormal3f(-1.0, 0.0, 0.0);
				glVertex3i( xC,  0, xC);
				glVertex3i( xC, 0, 0 );
				glVertex3i(xC, xC, 0);
				glVertex3i( xC,  xC,  xC);
		glEnd();
	glPopMatrix();
}

void ball_movement(){
  cube1_position_z = 5+obsP[1]-obsP[2];
	cube1_position_x = 19.75;
	/* caso a bola bata na parede de trás ou na da frente ( a direito )*/
	if(ball_position_x <= 0.1 || ball_position_x >= 19.9 ){
		ball_speed_x = ball_speed_x * -1;
		//caso bata com angulo atrás ou à frente

		//printf("Bateu nas paredes frontais\n" );
		glutPostRedisplay();
	}

	//caso bata nas paredes laterais
	if(ball_position_z >= 20 || ball_position_z <= 0)
	{

		ball_speed_z = ball_speed_z * -1;
			//printf("Bateu nas paredes de laterais\n" );
	}

	//salto da bola
			if(jump == 1)
				{
				if(jump_coordinate<5)
				{
		  		jump_coordinate += jump_speed;
		  	}
			}
				if(jump_coordinate >= 5)
				{
					jump = 0;
				}

			if(jump == 0)
			{
				if(jump_coordinate > 0.5 )
				{
				 jump_coordinate -= jump_speed;
				}
			}
   //colisão com os raquetas(cubos)
	 if(ball_position_x >= cube1_position_x-0.5 )
	 {
		 if(ball_position_z <= cube1_position_z + 0.3 && ball_position_z >= cube1_position_z - 0.3 )
		 {
			 ball_speed_x = ball_speed_x * -1;
			 //printf("BATEU NO CUBO\n");
		 }
	 }


			//actualização
			ball_position_x += ball_speed_x;
			ball_position_z += ball_speed_z;
		  glutPostRedisplay();
}

void display(void){
	// Apagar
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Janela Visualizacao
	glViewport (0,0,wScreen, hScreen);

	// Projeccao
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (defineProj) {
		case 1: gluPerspective(110, wScreen/hScreen, 0.5, zC); break;
		default: glOrtho (-xC,xC,-yC,yC,-zC,zC);
			break;
	}

	// Modelo+View(camera/observador)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(21, 7, 10,-10,-10,10, 0, 1, 0);

	// Objectos
	//cubo 1
	glPushMatrix();
	//glColor4f(LARANJA);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpecular );
	glMaterialf(GL_FRONT, GL_SHININESS, rubyShininess);
	//glColor4f(VERDE);
	cube1_position_z = 5+obsP[1]-obsP[2];
	glTranslatef(19.75,1,cube1_position_z);
	draw_cube();
	glPopMatrix();

	//cubo 2
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, rubyShininess);
	//glColor4f(AMARELO);
	glTranslatef(19.75,1,15+obsP[3]-obsP[4]);
	draw_cube();
	glPopMatrix();

	//bola
	glPushMatrix();
	//glColor4f(BLACK);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowRubberDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellowRubberSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, yellowRubberShininess);
	glTranslatef(ball_position_x,jump_coordinate,ball_position_z);
	glutSolidSphere(0.25,20,20);
	glPopMatrix();

	//glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//glBlendFunc(GL_SRC_ALPHA,	GL_ONE_MINUS_SRC_ALPHA);
	drawScene();
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_BLEND);

	//glDepthMask(GL_FALSE);
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, GlassDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, GlassSpecular);
	glMaterialf (GL_FRONT, GL_SHININESS, GlassShininess);
	drawScene1();
	glPopMatrix();

	//glDepthMask(GL_TRUE);

	ball_movement();

	glutSwapBuffers();
}

//EVENTOS
void keyboard(unsigned char key, int x, int y){
	char* aux;
	switch (key) {
		case'1':
		if(light){
			glDisable(GL_LIGHT0);
			light=0;
			glutPostRedisplay();
		}
		else{
			glEnable(GL_LIGHT0);
			light=1;
			glutPostRedisplay();
		}
	break;

	case ' ':
		if(jump==0){
			jump = 1;
		}
	break;

/* case 'p':
 case 'P':
 			if(pause_game==0){
				pause_game=1;
				aux = (char *)calloc(1, sizeof(char) * 2);
				strcpy(aux, "PAUSED");
				writeText(aux, 1.0, 1.0, 1.0);
				free(aux);
				glutPostRedisplay();
			}
			else{
				pause_game=0;
			}
	 break;*/

	// Obj 1 anda para a esquerda
	case 'A':
	case 'a':
	if(5+obsP[1]-obsP[2] <= xC-2 ){
		obsP[1] = obsP[1] + inc;
	}
	glutPostRedisplay();
	break;

	// Obj 1 anda para a direita
	case 'd':
	case 'D':
	if(5+obsP[1]-obsP[2] >= 2){
		obsP[2] = obsP[2]+inc;
	}
	glutPostRedisplay();
	break;

	// Obj 2 anda para a esquerda
	case 'j':
	case 'J':
	if(15+obsP[3]-obsP[4] <= xC-2){
		obsP[3] = obsP[3] + inc;
	}
	glutPostRedisplay();
	break;

// O bj 2 anda para a direita
	case 'L':
	case 'l':
	if(15+obsP[3]-obsP[4] >= 2){
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

int main(int argc, char** argv){
	srand(time(NULL));
	int r = rand()%4000 - 2000; //this produces numbers between -2000 - +2000
  float random_num = r/10000.0;
	printf("ball_speed_z : %f\n",random_num);
	ball_speed_z = random_num;

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
