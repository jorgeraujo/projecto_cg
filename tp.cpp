#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

// INCLUDES MARIA
/*#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>*/

//INCLUDES JORGE
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

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

// Sistema Coordenadas
GLfloat   xC=20.0, yC=20.0, zC=30.0;
GLfloat   wScreen=800.0, hScreen=600.0;
GLfloat   speed = 0.1;
GLfloat   ball_speed_x = 0.09;
GLfloat   ball_speed_z;
GLfloat   ball_position_x = 10;
GLfloat 	ball_position_z = 10;
GLfloat 	ball_position_y;
GLfloat 	aux_ball_speed_x;
GLfloat 	aux_ball_speed;
GLfloat   cube1_position_x;
GLfloat   cube1_position_z;
GLint     hit = 0;
GLint 		exit_game=0;
GLint 		pause_game=0;
GLfloat   jump_coordinate=0.5;
GLfloat   jump_speed = 0.20;
GLfloat  	inc   = 0.5;
GLint     jump = 0;
GLint 		ball_type=0;
GLint 		ball_aux=0;

// Observador
GLint 	 l1=0;
GLint 	 l2=0;
GLint 	 eyeX=21;
GLint 	 eyeY=7;
GLint 	 eyeZ=10;
GLint 	 centerX=-10;
GLint 	 centerY=-10;
GLint 	 centerZ=10;
GLint 	 upX=0;
GLint 	 upY=1;
GLint 	 upZ=0;
GLint    defineView=0;
GLint    defineProj=1;
GLint    points = 0;
GLfloat  obsP[5];

//iluminacao
int light=1;
GLfloat corLuzA[]={1.0f, 1.0f, 1.0f, 1.0f};
GLfloat corLuzD[]={1.f, 1.0f, 1.0f, 1.0f};
GLfloat corLuzE[]={0.2f, 0.2f, 0.2f, 1.0f};
GLfloat posicaoLuz[] = {0.0, 20.0, 0.0, 1.0};
GLfloat posicao1[]={ball_position_x, ball_position_y, ball_position_z, 1.0};
GLfloat direcaoLuz[]={0.0f,1.0f,0.0f};
GLfloat concentracaoLuz=20.0;
GLfloat anguloLuz=90.0;
GLfloat corP[]={1.5f,1.5f,1.5f,1.0f};

GLfloat amareloD[]={0.5,0.5,0.4,1};
GLfloat amareloE[]={0.7,0.7,0.04};
GLfloat amareloS=.078125*128;

GLfloat rubyD[]={0.61424,0.04136,0.04136,1};
GLfloat rubyE[]={0.727811,0.626959,0.626959};
GLfloat rubyS=0.6*128;

GLfloat pretoD[]={0.01,0.01,0.01,1};
GLfloat pretoE[]={0.01,0.01,0.01};
GLfloat pretoS=0;

//Transparencia
GLfloat vidroD []={ 0.1, 0.1, 0.1, 0.7};
GLfloat vidroE []={ 1, 1, 1};
GLint 	vidroS = 1;

// Texturas
GLuint  texture[10];
GLuint  texture_ball[3];
GLuint  tex;
RgbImage imag;

//Texto
char text[30];

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

	//bola
	glGenTextures(1, &texture_ball[0]);
  glBindTexture(GL_TEXTURE_2D, texture_ball[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  imag.LoadBmpFile("ball0.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

  glGenTextures(1, &texture_ball[1]);
  glBindTexture(GL_TEXTURE_2D, texture_ball[1]);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  imag.LoadBmpFile("ball1.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
}

void iluminacao(){
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	glLightfv(GL_LIGHT0, GL_AMBIENT, corLuzA);
	glLightfv(GL_LIGHT0, GL_SPECULAR, corLuzE);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, corLuzD);

	glLightfv(GL_LIGHT1, GL_POSITION, posicao1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direcaoLuz);
	glLightf (GL_LIGHT1, GL_SPOT_EXPONENT , concentracaoLuz);
	glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, anguloLuz);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);
	glLightfv(GL_LIGHT1, GL_SPECULAR, corP);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, corP);
}


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
	glEnable(GL_LIGHT1);
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
   glutSolidCube (1);
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
	glBindTexture(GL_TEXTURE_2D,texture[2]);
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
	if(ball_position_x <= 0.1){
		 if(jump_coordinate > 5)
		 {
			 points++;
			}
			ball_speed_x = ball_speed_x * -1;
			 glutPostRedisplay();

				 }

		if(ball_position_x >= 19.9 )
		{
			points--;
			ball_speed_x = ball_speed_x * -1;
				glutPostRedisplay();
		}

		//caso bata com angulo atrás ou à frente
		//printf("Bateu nas paredes frontais\n" );

	//caso bata nas paredes laterais
	if(ball_position_z >= 20 || ball_position_z <= 0)
	{

		ball_speed_z = ball_speed_z * -1;
			//printf("Bateu nas paredes de laterais\n" );
	}

	//salto da bola
			if(jump == 1)
				{
				if(jump_coordinate<7.5)
				{
		  		jump_coordinate += jump_speed;
		  	}
			}
				if(jump_coordinate >= 7.5	)
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

void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z)
{
glPushMatrix();
glRasterPos3f(x,y,z);
while(*string){
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
  	}
		glRotatef(90,1,1,1);
glPopMatrix();
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
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

	// Objectos
	//cubo 1
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyD);
	glMaterialfv(GL_FRONT, GL_SPECULAR, rubyE);
	glMaterialf(GL_FRONT, GL_SHININESS, rubyS);
	cube1_position_z = 5+obsP[1]-obsP[2];
	glTranslatef(19.50,0.5,cube1_position_z);
	draw_cube();
	glPopMatrix();

	//bola
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_ball[ball_type]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, amareloD);
	glMaterialfv(GL_FRONT, GL_SPECULAR, amareloE);
	glMaterialf(GL_FRONT, GL_SHININESS, amareloS);
	glTranslatef(ball_position_x,jump_coordinate,ball_position_z);
	glutSolidSphere(0.25,20,20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	drawScene();
	sprintf(text,"Pontuacao: %d",points);
	desenhaTexto(text,10,12,5);
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, vidroD);
	glMaterialfv(GL_FRONT, GL_SPECULAR, vidroE);
	glMaterialf (GL_FRONT, GL_SHININESS, vidroS);
	drawScene1();
	ball_movement();
	glPopMatrix();

// --------------------- Reflexao (not wotking) //
/*glEnable(GL_STENCIL_TEST);
glColorMask(0, 0, 0, 0);
glDisable(GL_DEPTH_TEST);
glStencilFunc(GL_ALWAYS, 1, 1);
glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

//chao
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

glColorMask(1, 1, 1, 1);
glEnable(GL_DEPTH_TEST);
glStencilFunc(GL_EQUAL, 1, 1);
glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

glPushMatrix();
glScalef(1, -1, 1);

glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyD);
glMaterialfv(GL_FRONT, GL_SPECULAR, rubyE);
glMaterialf(GL_FRONT, GL_SHININESS, rubyS);
cube1_position_z = 5+obsP[1]-obsP[2];
glTranslatef(19.50,0.5,cube1_position_z);
draw_cube();


//bola
glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture_ball[ball_type]);
glMaterialfv(GL_FRONT, GL_DIFFUSE, amareloD);
glMaterialfv(GL_FRONT, GL_SPECULAR, amareloE);
glMaterialf(GL_FRONT, GL_SHININESS, amareloS);
glTranslatef(ball_position_x,jump_coordinate,ball_position_z);
glutSolidSphere(0.25,20,20);
glDisable(GL_TEXTURE_2D);
glPopMatrix();

drawScene();
sprintf(text,"Pontuacao: %d",points);
desenhaTexto(text,10,12,5);
glPushMatrix();
glMaterialfv(GL_FRONT, GL_DIFFUSE, vidroD);
glMaterialfv(GL_FRONT, GL_SPECULAR, vidroE);
glMaterialf (GL_FRONT, GL_SHININESS, vidroS);
drawScene1();
glPopMatrix();

glPopMatrix();

glDisable(GL_STENCIL_TEST);
glEnable(GL_BLEND);
glColor4f(1, 1, 1, 0.7f);
glDisable(GL_BLEND);
*/

//---------------------

	ball_movement();

	glutSwapBuffers();
}

//EVENTOS
void keyboard(unsigned char key, int x, int y){
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

	case '2':
			if(l1 == 0){
				eyeX=eyeX-5;
				eyeY=eyeY+13;
				l1=1;
			}
			else{
				eyeX=eyeX+5;
				eyeY=eyeY-13;
				l1 = 0;
			}
		glutPostRedisplay();
		break;

		case '3':
				if(l2 == 0){
					eyeX=eyeX+7;
					eyeY=eyeY+3;
					l2=1;
				}
				else{
					eyeX=eyeX-7;
					eyeY=eyeY-3;
					l2 = 0;
				}
			glutPostRedisplay();
			break;


	case ' ':
		if(jump==0){
			jump = 1;
		}
	break;

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

	case 'x':
	case 'X':
		ball_type+=1;
		glutPostRedisplay();
	  break;

	case 27:
		exit(0);
		break;

	case 'q':
	case 'Q':
		defineProj=(defineProj+1)%2;
		break;

		case 'p':
		case 'P':
		{
			if(ball_speed_z!=0)
				{
	 	aux_ball_speed = ball_speed_z;
 			}
		if(pause_game == 0){

		 if(ball_speed_z !=0 )
		 {
			 aux_ball_speed = ball_speed_z;
			 aux_ball_speed_x = ball_speed_x;
		 }
		   ball_speed_x = 0;
			ball_speed_z = 0;
			pause_game = 1;
			glPushMatrix();
			sprintf(text,"PAUSA");
			glColor3f(1,0,0);
			glRotatef(90,0,1,0);
  writeText(text,10,10 ,10);
 		glPopMatrix();
		glutPostRedisplay();
		}

		else
		{
			ball_speed_x = aux_ball_speed_x;
			ball_speed_z = aux_ball_speed;
			pause_game = 0;
		}
	 break;
 	}
  }


	glutPostRedisplay();
}

int main(int argc, char** argv){
	srand(time(NULL));
	int r = rand()%4000 - 2000; //this produces numbers between -2000 - +2000
  float random_num = r/10000.0;
	//printf("ball_speed_z : %f\n",random_num);
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
