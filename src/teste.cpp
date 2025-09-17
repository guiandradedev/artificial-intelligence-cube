#include <stdio.h>
#include <iostream>
#include <math.h>
#include "MiniCube.h"
#define GL_GLEXT_PROTOTYPES
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

struct RGB
{
    float r, g, b;
};

void display();
void specialKeysListener(int key, int x, int y);
void desenharCubinho(float x, float y, float z, RGB *coresFaces[6]);
void keyboardListener(unsigned char key, int x, int y);
void reshape(int w, int h);
void setupCube();
double rotate_y = 0, rotate_x = 0;
const float offset = 0.51f;

RGB cores[6] = {
    {1.0f, 1.0f, 0.0f}, // 0 amarelo
    {1.0f, 1.0f, 1.0f}, // 1 branco
    {0.0f, 0.0f, 1.0f}, // 2 azul
    {0.0f, 1.0f, 0.0f}, // 3 verde
    {1.0f, 0.5f, 0.0f}, // 4 laranja
    {1.0f, 0.0f, 0.0f}  // 5 vermelho
};
RGB preto = {0.0f, 0.0f, 0.0f};
MiniCube cube[2][2][2];

void setupCube()
{
    // for (int i = 0; i < 2; ++i) { // X
    //     for (int j = 0; j < 2; ++j) { // Y
    //         for (int k = 0; k < 2; ++k) { // Z
    //             cube[i][j][k].index = i * 4 + j * 2 + k;
    //             cube[i][j][k].orientation = 0;

    //             // Atribui as cores baseadas na posição (i, j, k)
    //             cube[i][j][k].mid = (j == 1) ? 0 : 1; // Topo (amarelo) ou Baixo (branco)
    //             cube[i][j][k].right = (k == 1) ? 3 : 2; // Frente (verde) ou Fundo (azul)
    //             cube[i][j][k].left = (i == 0) ? 4 : 5; // Esquerda (laranja) ou Direita (vermelho)
    //         }
    //     }
    // }

    int colors[8][3] = {
        {4, 2, 0}, // manteu
        {4, 2, 1}, // manteu
        {3, 4, 0}, // manteu
        {3, 4, 1}, // manteu
        {2, 5, 0},
        {2, 5, 1},
        {5, 3, 0},
        {5, 3, 1}};
    // Loop que insere as cores na matriz
    int index = 1;
    for (int x = 0; x < 2; ++x)
    {
        for (int y = 0; y < 2; ++y)
        {
            for (int z = 0; z < 2; ++z)
            {
                int index = x * 4 + y * 2 + z;
                cube[x][y][z].left = colors[index][0];
                cube[x][y][z].right = colors[index][1];
                cube[x][y][z].mid = colors[index][2];
                cube[x][y][z].orientation = 0;
                cube[x][y][z].index = index;
            }
        }
    }
}

// void desenharCubinho(float x, float y, float z, RGB* coresFaces[6]) {
//     glPushMatrix();
//     glTranslatef(x, y, z);

//     glBegin(GL_QUADS);
//     glColor3f(coresFaces[2]->r, coresFaces[2]->g, coresFaces[2]->b); glVertex3f(-0.5, -0.5, -0.5); glVertex3f(-0.5,  0.5, -0.5); glVertex3f( 0.5,  0.5, -0.5); glVertex3f( 0.5, -0.5, -0.5); glEnd();
//     glBegin(GL_QUADS);
//     glColor3f(coresFaces[5]->r, coresFaces[5]->g, coresFaces[5]->b); glVertex3f( 0.5, -0.5, -0.5); glVertex3f( 0.5,  0.5, -0.5); glVertex3f( 0.5,  0.5,  0.5); glVertex3f( 0.5, -0.5,  0.5); glEnd();
//     glBegin(GL_QUADS);
//     glColor3f(coresFaces[3]->r, coresFaces[3]->g, coresFaces[3]->b); glVertex3f( 0.5, -0.5,  0.5); glVertex3f( 0.5,  0.5,  0.5); glVertex3f(-0.5,  0.5,  0.5); glVertex3f(-0.5, -0.5,  0.5); glEnd();
//     glBegin(GL_QUADS);
//     glColor3f(coresFaces[4]->r, coresFaces[4]->g, coresFaces[4]->b); glVertex3f(-0.5, -0.5,  0.5); glVertex3f(-0.5,  0.5,  0.5); glVertex3f(-0.5,  0.5, -0.5); glVertex3f(-0.5, -0.5, -0.5); glEnd();
//     glBegin(GL_QUADS);
//     glColor3f(coresFaces[0]->r, coresFaces[0]->g, coresFaces[0]->b); glVertex3f( 0.5,  0.5,  0.5); glVertex3f( 0.5,  0.5, -0.5); glVertex3f(-0.5,  0.5, -0.5); glVertex3f(-0.5,  0.5,  0.5); glEnd();
//     glBegin(GL_QUADS);
//     glColor3f(coresFaces[1]->r, coresFaces[1]->g, coresFaces[1]->b); glVertex3f( 0.5, -0.5, -0.5); glVertex3f( 0.5, -0.5,  0.5); glVertex3f(-0.5, -0.5,  0.5); glVertex3f(-0.5, -0.5, -0.5); glEnd();

//     glPopMatrix();
// }
void desenharCubinho(int i, int j, int k, MiniCube *mini)
{
    glPushMatrix();

    // Translação para a posição 3D
    float x_pos = (i * 2.0 - 1.0) * offset;
    float y_pos = (j * 2.0 - 1.0) * offset;
    float z_pos = (k * 2.0 - 1.0) * offset;
    glTranslatef(x_pos, y_pos, z_pos);

    // Face do Topo/Baixo (mid)
    glBegin(GL_QUADS);
    glColor3fv((GLfloat *)&cores[mini->mid]);
    if (j == 1)
    { // Topo
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
    }
    else
    { // Baixo
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
    }
    glEnd();

    // Face da Frente/Fundo (right)
    glBegin(GL_QUADS);
    glColor3fv((GLfloat *)&cores[mini->right]);
    if (k == 1)
    { // Frente
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
    }
    else
    { // Fundo
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
    }
    glEnd();

    // Face da Esquerda/Direita (left)
    glBegin(GL_QUADS);
    glColor3fv((GLfloat *)&cores[mini->left]);
    if (i == 0)
    { // Esquerda
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
    }
    else
    { // Direita
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
    }
    glEnd();

    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            for (int k = 0; k < 2; ++k)
            {
                desenharCubinho(i, j, k, &cube[i][j][k]);
            }
        }
    }

    glFlush();
    glutSwapBuffers();
}


// void display() {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();

//     gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//     glRotatef(rotate_x, 1.0, 0.0, 0.0);
//     glRotatef(rotate_y, 0.0, 1.0, 0.0);

//     const float offset = 0.51f;
//     const float positions[8][3] = {
//         {offset, offset, offset}, {-offset, offset, offset},
//         {-offset, offset, -offset}, {offset, offset, -offset},
//         {offset, -offset, offset}, {-offset, -offset, offset},
//         {-offset, -offset, -offset}, {offset, -offset, -offset}
//     };

//     for (int i = 0; i < 8; i++) {
//         glPushMatrix();
//         glTranslatef(positions[i][0], positions[i][1], positions[i][2]);

//         RGB* coresCubinho[6];
//         coresCubinho[0] = (positions[i][1] > 0) ? &cores[0] : &preto;
//         coresCubinho[1] = (positions[i][1] < 0) ? &cores[1] : &preto;
//         coresCubinho[2] = (positions[i][2] < 0) ? &cores[2] : &preto;
//         coresCubinho[3] = (positions[i][2] > 0) ? &cores[3] : &preto;
//         coresCubinho[4] = (positions[i][0] < 0) ? &cores[4] : &preto;
//         coresCubinho[5] = (positions[i][0] > 0) ? &cores[5] : &preto;

//         desenharCubinho(0, 0, 0, coresCubinho);
//         glPopMatrix();
//     }

//     glFlush();
//     glutSwapBuffers();
// }

void specialKeysListener(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
    {
        rotate_y += 5;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        rotate_y -= 5;
    }
    else if (key == GLUT_KEY_UP)
    {
        rotate_x += 5;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        rotate_x -= 5;
    }

    if (rotate_x > 360)
        rotate_x -= 360;
    if (rotate_x < -360)
        rotate_x += 360;
    if (rotate_y > 360)
        rotate_y -= 360;
    if (rotate_y < -360)
        rotate_y += 360;

    glutPostRedisplay();
}
void keyboardListener(unsigned char key, int x, int y)
{
    if (key == 'q')
    {
        exit(0);
    }
    else if (key == 'r')
    {
        // executa
    }
    else if (key == 'l' || key == 'L')
    {
        // rotateL();
    }
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Cubo");
    glEnable(GL_DEPTH_TEST);
    setupCube();
    // MiniCube aux = cube[0][0][0];
    // cube[0][0][0] = cube[1][1][1];
    // cube[1][1][1] = cube[0][0][0];
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeysListener);
    glutKeyboardFunc(keyboardListener);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

// g++ -Isrc/headers src/teste.cpp src/MiniCube.cpp -o teste -lGL -lGLU -lglut && ./teste