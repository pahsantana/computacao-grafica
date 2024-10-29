#include <GL/glut.h>

float posX = 0.0f;
float posY = 0.0f;
float size = 0.1f;
const float speed = 0.05f;
const float sizeStep = 0.01f;

float red = 1.0f, green = 0.0f, blue = 0.0f;

void desenhaQuadrado() {
  glColor3f(red, green, blue);
  glBegin(GL_QUADS);
    glVertex2f(-size + posX, -size + posY);
    glVertex2f(size + posX, -size + posY);
    glVertex2f(size + posX, size + posY);
    glVertex2f(-size + posX, size + posY);
  glEnd();
}

void renderiza() {
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaQuadrado();
  glFlush();
}

void teclado(unsigned char tecla, int x, int y){
  switch (tecla){
    case 'r':
    case 'R':
      red = 1.0; green = 0.0; blue=0.0;
    case 'c':
    case 'C':
      posX = 0.0;
      posY = 0.0;
      size = 0.1;
      break;
    case 'g':
    case 'G':
      red = 0.0; green = 1.0; blue=0.0;
      break;
    case 'b':
    case 'B':
      red = 0.0; green = 0.0; blue=1.0;
      break;
    case '+':
      size += sizeStep;
      break;
    case '-':
      size = (size - sizeStep > 0) ? size - sizeStep: size;
      break;
  }
  glutPostRedisplay();
}

void tecladoEspecial(int tecla, int x, int y){
  switch (tecla){
    case GLUT_KEY_UP:
      posY += speed;
      break;
    case GLUT_KEY_DOWN:
      posY -= speed;
      break;
    case GLUT_KEY_RIGHT:
      posX += speed;
      break;
    case GLUT_KEY_LEFT:
      posX -= speed;
      break;
    case GLUT_KEY_HOME:
      size = 0.1;
      posX = -1 + size;
      posY = 1 - size;
      break;
    case GLUT_KEY_END:
      size = 0.1;
      posX = 1 - size;
      posY = -1 + size;
      break;
    case GLUT_KEY_PAGE_DOWN:
      posY -= speed*2;
      break;
    case GLUT_KEY_PAGE_UP:
      posY += speed*2;
      break;

  }
  glutPostRedisplay();
}

int main(int argc, char** argv)
 {
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Quadrado e Teclado");

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glutDisplayFunc(renderiza);
  glutKeyboardFunc(teclado);
  glutSpecialFunc(tecladoEspecial);

  glutMainLoop();

  return 0;
}
