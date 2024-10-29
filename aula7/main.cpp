#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

float color[3] = {1.0f, 0.0f, 0.0f};
float xPos = 0.0, yPos = 0.0;
float size = 0.2;

float tx = 0.0, ty=0.0;
float angulo = 0.0;
float incremento = 3.0;
float escala = 1.0;

float speedX = 0.02, speedY = 0.02;

void desenhaQuadrado(float x, float y)
{
 glColor3f(color[0], color[1], color[2]);

 glBegin(GL_QUADS);
   glVertex2f(xPos - size, yPos - size);
   glVertex2f(xPos + size, yPos - size);
   glVertex2f(xPos + size, yPos + size);
   glVertex2f(xPos - size, yPos + size);
 glEnd();
}

void display()
{
 glClear(GL_COLOR_BUFFER_BIT);

 ///desenhaQuadrado(xPos, yPos);

 //color[0]=0; color[1]=1; color[2]=0;      //ficar verde na parte da transformação

 //glScalef(1.0, 0.5, 1.0);                //x multiplica por 1, y multiplica por 0.5 e o z a gente não usa//
 //desenhaQuadrado(xPos, yPos);

 //glLoadIdentity();                       //carregar a matriz de identidade, para uma transformação não afetar a outra//
 //glTranslatef(0.5, 0.0, 0.0);            //transladando
 //glScalef(1.0, 2.0, 1.0);
 //desenhaQuadrado(xPos, yPos);

// glMatrixMode(GL_MODELVIEW);
// glLoadIdentity();

glPushMatrix(); // carrega a matrix novamente

//quadrado

glTranslatef(tx, ty, 0.0);
glRotatef(angulo, 0.0, 0.0, 1.0);
glScalef(escala,escala, 1.0);
desenhaQuadrado(xPos,yPos);

glPopMatrix();
glutSwapBuffers();

//quadrado 1
//glPushMatrix();     //fazer cópia da matriz
//color[0]=0; color[1]=1; color[2]=0;
//glTranslatef(0.5, 0.0, 0.0);   //primeiro ele translada e depois rotaciona, a ordem faz diferença//
//glRotatef(45, 0.0, 0.0, 1.0);  //rotacionar em 45 graus em torno do eixo z (por isso marca o z com 1)// 
//desenhaQuadrado(xPos,yPos);
//glPopMatrix();                  //garante que uma transformção não afete a outra


//quadrado 2
//glPushMatrix();                          //faz a cópia da matriz
//color[0]=0; color[1]=0; color[2]=1;        //aqui queremos uma rotação primeiro, depois uma translação//
//glRotatef(45, 0.0, 0.0, 1.0);
//glTranslatef(0.5, 0.0, 0.0);     
//desenhaQuadrado(xPos,yPos);
//glPopMatrix();                           //garante que uma transformção não afete a outra

 glFlush();
}

void atualiza(int valor){
  tx += speedX;
  ty += speedY;
  angulo+= incremento;
  // bater
  if( tx + size > 1.0 || tx - size < -1.0)
    speedX = -speedX;
  if( ty + size > 1.0 || ty - size < -1.0)
    speedY = -speedY;
  glutPostRedisplay();
  glutTimerFunc(16,atualiza,0);
}

void teclado(unsigned char tecla, int x, int y)
{
  switch(tecla)
  {
    case 'w':
    ty +=0.01;
    break;
    case 's':
    ty -= 0.01;
    break;
    case 'a':
    tx -= 0.01;
    break;
    case 'd':
    tx += 0.01;
    break;
    case 'q':
     angulo += 5.0;
     break;
    case 'e':
     angulo -=5.0;
     break;
    case '+':
     escala += 0.01;
     break;
    case '-':
     escala -= 0.01;
     break; 
  }
  glutPostRedisplay();
}

void mouse (int botao, int estado, int x, int y)
{
  if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
  {
    speedX = ((rand() % 100 ) / 100.0) * 0.04 - 0.02;  //-0.02 e 0.02
    speedY = ((rand() % 100 ) / 100.0) * 0.04 - 0.02;  //-0.02 e 0.02
    color[0] = ((rand() % 100 ) / 100.0);
    color[1] = ((rand() % 100 ) / 100.0);  
    color[2] = ((rand() % 100 ) / 100.0);
  }
  if (botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
  {
    speedX = 0.0;  
    speedY = 0.0;  
    incremento = 0.0;
    glutTimerFunc(0, atualiza, 0);
  }
}

void inicializa()
{
 glClearColor(1.0, 1.0, 1.0, 1.0);
 glMatrixMode(GL_MODELVIEW); //matriz para fazer as transf geometicas//
 glLoadIdentity(); //garante que comece sem nenhunha transformação//
}

int main(int argc, char** argv)
{
  srand(time(NULL));
 glutInit(&argc, argv);
 glutInitWindowSize(500, 500);
 glutCreateWindow("Transformacoes Geometricas");

 inicializa();

 glutDisplayFunc(display);
 glutKeyboardFunc(teclado);
 glutMouseFunc(mouse);
 glutTimerFunc(0,atualiza,0);
 
 glutMainLoop();

 return 0;
}