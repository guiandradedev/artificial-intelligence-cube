#include <stdio.h>
// nao tem o stdarg.h
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display();
void specialKeys(int key, int x, int y) ;

double rotate_y = 0, rotate_x = 0;
struct RGB {
    float r, g, b;
};
RGB cores[6] = {
    {1.0f, 1.0f, 0.0f}, // 0 amarelo
    {1.0f, 1.0f, 1.0f}, // 1 branco
    {0.0f, 0.0f, 1.0f}, // 2 azul
    {0.0f, 1.0f, 0.0f}, // 3 verde
    {1.0f, 0.5f, 0.0f}, // 4 laranja
    {1.0f, 0.0f, 0.0f}  // 5 vermelho
};
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa a tela e o buffer de profundidade
    glLoadIdentity(); // Reseta a matriz de transformacao

    // Aplica as rotacoes
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    // Face 1 - vermelho (centro)
    glBegin(GL_POLYGON);
        glColor3f(cores[5].r, cores[5].g, cores[5].b);  glVertex3f(-0.5, -0.5, -0.5);
        glColor3f(cores[5].r, cores[5].g, cores[5].b);  glVertex3f(-0.5,  0.5, -0.5);
        glColor3f(cores[5].r, cores[5].g, cores[5].b);  glVertex3f( 0.5,  0.5, -0.5);
        glColor3f(cores[5].r, cores[5].g, cores[5].b);  glVertex3f( 0.5, -0.5, -0.5);
    glEnd();

    // Face 2 - verde (direita)
    glBegin(GL_POLYGON);
        glColor3f(cores[3].r, cores[3].g, cores[3].b);  glVertex3f( 0.5, -0.5, -0.5);
        glColor3f(cores[3].r, cores[3].g, cores[3].b);  glVertex3f( 0.5,  0.5, -0.5);
        glColor3f(cores[3].r, cores[3].g, cores[3].b);  glVertex3f( 0.5,  0.5,  0.5);
        glColor3f(cores[3].r, cores[3].g, cores[3].b);  glVertex3f( 0.5, -0.5,  0.5);
    glEnd();

    // Face 3 - laranja (atras)
    glBegin(GL_POLYGON);
        glColor3f(cores[4].r, cores[4].g, cores[4].b);  glVertex3f( 0.5, -0.5,  0.5);
        glColor3f(cores[4].r, cores[4].g, cores[4].b);  glVertex3f( 0.5,  0.5,  0.5);
        glColor3f(cores[4].r, cores[4].g, cores[4].b);  glVertex3f(-0.5,  0.5,  0.5);
        glColor3f(cores[4].r, cores[4].g, cores[4].b);  glVertex3f(-0.5, -0.5,  0.5);
    glEnd();

    // Face 4 - azul (esquerda)
    glBegin(GL_POLYGON);
        glColor3f(cores[2].r, cores[2].g, cores[2].b);  glVertex3f(-0.5, -0.5,  0.5);
        glColor3f(cores[2].r, cores[2].g, cores[2].b);  glVertex3f(-0.5,  0.5,  0.5);
        glColor3f(cores[2].r, cores[2].g, cores[2].b);  glVertex3f(-0.5,  0.5, -0.5);
        glColor3f(cores[2].r, cores[2].g, cores[2].b);  glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // Face 5 - amarelo (topo)
    glBegin(GL_POLYGON);
        glColor3f(cores[0].r, cores[0].g, cores[0].b);  glVertex3f( 0.5,  0.5,  0.5);
        glColor3f(cores[0].r, cores[0].g, cores[0].b);  glVertex3f( 0.5,  0.5, -0.5);
        glColor3f(cores[0].r, cores[0].g, cores[0].b);  glVertex3f(-0.5,  0.5, -0.5);
        glColor3f(cores[0].r, cores[0].g, cores[0].b);  glVertex3f(-0.5,  0.5,  0.5);
    glEnd();

    // Face 6 - branco (baixo)
    glBegin(GL_POLYGON);
        glColor3f(cores[1].r, cores[1].g, cores[1].b);  glVertex3f( 0.5, -0.5, -0.5);
        glColor3f(cores[1].r, cores[1].g, cores[1].b);  glVertex3f( 0.5, -0.5,  0.5);
        glColor3f(cores[1].r, cores[1].g, cores[1].b);  glVertex3f(-0.5, -0.5,  0.5);
        glColor3f(cores[1].r, cores[1].g, cores[1].b);  glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glFlush();
    glutSwapBuffers();

}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) {
        rotate_y += 10;
    } else if(key == GLUT_KEY_LEFT) {
        rotate_y -= 5;
    } else if(key == GLUT_KEY_UP) {
        rotate_x += 10;
    } else if(key == GLUT_KEY_DOWN) {
        rotate_x -= 5;
    }
    glutPostRedisplay();
}
 
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Cubo");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}