#include <cstdio>
#define GL_GLEXT_PROTOTYPES
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Cube.h"
#include "Move.h"
#include "Solver.h"
#include <vector>

// MiniCube cube[2][2][2];
Cube cubo;
Solver solver;

struct RGB
{
    float r, g, b;
};
static const RGB C[6] = {
    {1.f, 1.f, 0.f},  // 0 amarelo  (topo, z=0)  [z+ aponta para baixo]
    {1.f, 1.f, 1.f},  // 1 branco   (base, z=1)
    {0.f, 0.f, 1.f},  // 2 azul     (esquerda, y=0)
    {0.f, 1.f, 0.f},  // 3 verde    (direita,  y=1)
    {1.f, 0.5f, 0.f}, // 4 laranja  (traseira, x=0)
    {1.f, 0.f, 0.f}   // 5 vermelho (frente,   x=1)
};
RGB preto = {0.0f, 0.0f, 0.0f};

double rotY = 0.0, rotX = 0.0, rotZ = 0.0; // começa olhando a face vermelha, sem rotação
const float OFFSET = 0.01f;                // separação entre cubinhos
const float S = 0.5f;                      // semi-tamanho do cubinho

void setupCube()
{
    cubo.init();

    // cubo.matrix[0][0][1].orientation = 2;
    // cubo.matrix[0][1][1].orientation = 2;
    const MiniCube &cube = cubo.matrix[1][0][1];

    std::cout << "Cubinho" << cube.index << " ("
              << cube.left << " "
              << cube.right << " "
              << cube.mid << " "
              << cube.orientation << std::endl;
}

// Desenha um quadrado colorido (sem moldura; evita z-fighting)
static inline void quadFill(const RGB &cor,
                            float x1, float y1, float z1,
                            float x2, float y2, float z2,
                            float x3, float y3, float z3,
                            float x4, float y4, float z4)
{
    glColor3f(cor.r, cor.g, cor.b);
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    glVertex3f(x4, y4, z4);
    glEnd();
}
void desenharCubinho(int x, int y, int z)
{
    glPushMatrix();
    const float X = (x * 2.f - 1.f) * OFFSET;
    const float Y = (y * 2.f - 1.f) * OFFSET;
    const float Z = (z * 2.f - 1.f) * OFFSET;
    glTranslatef(X, Y, Z);

    // Get the colors for the current cubie from the Cube object's matrix
    int left_color = cubo.matrix[x][y][z].left;
    int right_color = cubo.matrix[x][y][z].right;
    int mid_color = cubo.matrix[x][y][z].mid;

    // Y = -S -> ESQUERDA (based on your cubie's left color)
    // quadFill(C[left_color],
    //             S, -S, -S, -S, -S, -S,
    //             -S, S, -S, S, S, -S);
    quadFill(C[left_color],
             0.0f, 0.0f, -S, -S, 0.0f, -S, -S, -S, -S, 0.0f, -S, -S);
    // 0.0f,0.0f,-S, -S,0.0f,-S, -S,-S-S, 0.0f,-S,-S);

    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Começa olhando para a face VERMELHA (frente, +X),
    // com topo AMARELO para cima (up = -Z)
    // gluLookAt(
    //     3.0, 0.0, 0.0,   // posição da câmera no +X
    //     0.0, 0.0, 0.0,   // olha para o centro
    //     0.0, 0.0, -1.0   // 'up' = -Z (amarelo para cima, branco para baixo)
    // );
    //     gluLookAt(
    //     5.0, 0.0, 0.0,   // posição da câmera no +X, mais longe
    //     0.0, 0.0, 0.0,   // olha para o centro
    //     0.0, 0.0, -1.0   // 'up' = -Z (amarelo para cima, branco para baixo)
    // );
    gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef((float)rotZ, 0.f, 0.f, 1.f);
    glRotatef((float)rotX, 1.f, 0.f, 0.f);
    glRotatef((float)rotY, 0.f, 1.f, 0.f);

    // Ponta esquerda e sentido horário

    // Analisar a linha que não tem 0s e pegar o sinal dela e substituir 0.0f por sinalOFFSET

    // Indice Z=0 e Orientacao = 0: left, right, mid
    // Indice Z=1 e Orientacao = 0: right, left, mid

    // Cubo inferior esquerda fundo
    // cubo.matrix[0][0][1].print();
    if (cubo.matrix[0][0][1].orientation == 0)
    {
        quadFill(C[cubo.matrix[0][0][1].right],
                 OFFSET, -S, -OFFSET,
                 S, -S, -OFFSET,
                 S, -S, -S,
                 OFFSET, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].left],
                 S, -S, -OFFSET,
                 S, -OFFSET, -OFFSET,
                 S, -OFFSET, -S,
                 S, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].mid],
                 OFFSET, -S, -S,
                 S, -S, -S,
                 S, -OFFSET, -S,
                 OFFSET, -OFFSET, -S);
    }
    else if (cubo.matrix[0][0][1].orientation == 1)
    {
        quadFill(C[cubo.matrix[0][0][1].mid],
                 OFFSET, -S, -OFFSET,
                 S, -S, -OFFSET,
                 S, -S, -S,
                 OFFSET, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].right],
                 S, -S, -OFFSET,
                 S, -OFFSET, -OFFSET,
                 S, -OFFSET, -S,
                 S, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].left],
                 OFFSET, -S, -S,
                 S, -S, -S,
                 S, -OFFSET, -S,
                 OFFSET, -OFFSET, -S);
    }
    else
    {
        quadFill(C[cubo.matrix[0][0][1].mid],
                 OFFSET, -S, -OFFSET,
                 S, -S, -OFFSET,
                 S, -S, -S,
                 OFFSET, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].right],
                 S, -S, -OFFSET,
                 S, -OFFSET, -OFFSET,
                 S, -OFFSET, -S,
                 S, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].left],
                 OFFSET, -S, -S,
                 S, -S, -S,
                 S, -OFFSET, -S,
                 OFFSET, -OFFSET, -S);
    }

    // Cubo inferior direita fundo
    if (cubo.matrix[0][1][1].orientation == 0)
    {
        quadFill(C[cubo.matrix[0][1][1].right],
                 -S, -OFFSET, -OFFSET,
                 -S, -S, -OFFSET,
                 -S, -S, -S,
                 -S, -OFFSET, -S);
        quadFill(C[cubo.matrix[0][1][1].left],
                 -S, -S, -OFFSET,
                 -OFFSET, -S, -OFFSET,
                 -OFFSET, -S, -S,
                 -S, -S, -S);
        quadFill(C[cubo.matrix[0][1][1].mid],
                 -S, -S, -S,
                 -OFFSET, -S, -S,
                 -OFFSET, -OFFSET, -S,
                 -S, -OFFSET, -S);
    }
    else if (cubo.matrix[0][1][1].orientation == 1)
    {
        quadFill(C[cubo.matrix[0][1][1].mid],
                 -S, -OFFSET, -OFFSET,
                 -S, -S, -OFFSET,
                 -S, -S, -S,
                 -S, -OFFSET, -S);
        quadFill(C[cubo.matrix[0][1][1].right],
                 -S, -S, -OFFSET,
                 -OFFSET, -S, -OFFSET,
                 -OFFSET, -S, -S,
                 -S, -S, -S);
        quadFill(C[cubo.matrix[0][1][1].left],
                 -S, -S, -S,
                 -OFFSET, -S, -S,
                 -OFFSET, -OFFSET, -S,
                 -S, -OFFSET, -S);
    }
    else
    {
        quadFill(C[cubo.matrix[0][1][1].mid],
                 -S, -OFFSET, -OFFSET,
                 -S, -S, -OFFSET,
                 -S, -S, -S,
                 -S, -OFFSET, -S);
        quadFill(C[cubo.matrix[0][1][1].right],
                 -S, -S, -OFFSET,
                 -OFFSET, -S, -OFFSET,
                 -OFFSET, -S, -S,
                 -S, -S, -S);
        quadFill(C[cubo.matrix[0][1][1].left],
                 -S, -S, -S,
                 -OFFSET, -S, -S,
                 -OFFSET, -OFFSET, -S,
                 -S, -OFFSET, -S);
    }

    // Cubo inferior esquerda frente
    // cubo.matrix[1][0][1].print();
    if (cubo.matrix[1][0][1].orientation == 0)
    {
        quadFill(C[cubo.matrix[1][0][1].right],
                 S, OFFSET, -OFFSET,
                 S, S, -OFFSET,
                 S, S, -S,
                 S, OFFSET, -S);
        quadFill(C[cubo.matrix[1][0][1].left],
                 OFFSET, S, -OFFSET,
                 S, S, -OFFSET,
                 S, S, -S,
                 OFFSET, S, -S);
        quadFill(C[cubo.matrix[1][0][1].mid],
                 S, OFFSET, -S,
                 S, S, -S,
                 OFFSET, S, -S,
                 OFFSET, OFFSET, -S);
    }
    else if (cubo.matrix[1][0][1].orientation == 1)
    {
        quadFill(C[cubo.matrix[1][0][1].mid],
                 S, OFFSET, -OFFSET,
                 S, S, -OFFSET,
                 S, S, -S,
                 S, OFFSET, -S);
        quadFill(C[cubo.matrix[1][0][1].right],
                 OFFSET, S, -OFFSET,
                 S, S, -OFFSET,
                 S, S, -S,
                 OFFSET, S, -S);
        quadFill(C[cubo.matrix[1][0][1].left],
                 S, OFFSET, -S,
                 S, S, -S,
                 OFFSET, S, -S,
                 OFFSET, OFFSET, -S);
    }
    else
    {
        // esse ta diferente?
        quadFill(C[cubo.matrix[1][0][1].left],
                 S, OFFSET, -OFFSET,
                 S, S, -OFFSET,
                 S, S, -S,
                 S, OFFSET, -S);
        quadFill(C[cubo.matrix[1][0][1].mid],
                 OFFSET, S, -OFFSET,
                 S, S, -OFFSET,
                 S, S, -S,
                 OFFSET, S, -S);
        quadFill(C[cubo.matrix[1][0][1].right],
                 S, OFFSET, -S,
                 S, S, -S,
                 OFFSET, S, -S,
                 OFFSET, OFFSET, -S);
    }

    // Cubo inferior direita frente
    if (cubo.matrix[1][1][1].orientation == 0)
    {
        quadFill(C[cubo.matrix[1][1][1].right],
                 -S, S, -OFFSET,
                 -OFFSET, S, -OFFSET,
                 -OFFSET, S, -S,
                 -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].left],
                 -S, S, -OFFSET,
                 -S, OFFSET, -OFFSET,
                 -S, OFFSET, -S,
                 -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].mid],
                 -OFFSET, S, -S,
                 -S, S, -S,
                 -S, OFFSET, -S,
                 -OFFSET, OFFSET, -S);
    }
    else if (cubo.matrix[1][1][1].orientation == 1)
    {
        quadFill(C[cubo.matrix[1][1][1].mid],
                 -S, S, -OFFSET,
                 -OFFSET, S, -OFFSET,
                 -OFFSET, S, -S,
                 -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].right],
                 -S, S, -OFFSET,
                 -S, OFFSET, -OFFSET,
                 -S, OFFSET, -S,
                 -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].left],
                 -OFFSET, S, -S,
                 -S, S, -S,
                 -S, OFFSET, -S,
                 -OFFSET, OFFSET, -S);
    }
    else
    {
        quadFill(C[cubo.matrix[1][1][1].left],
                 -S, S, -OFFSET,
                 -OFFSET, S, -OFFSET,
                 -OFFSET, S, -S,
                 -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].mid],
                 -S, S, -OFFSET,
                 -S, OFFSET, -OFFSET,
                 -S, OFFSET, -S,
                 -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].right],
                 -OFFSET, S, -S,
                 -S, S, -S,
                 -S, OFFSET, -S,
                 -OFFSET, OFFSET, -S);
    }

    // Cubo superior esquerda fundo
    if (cubo.matrix[0][0][0].orientation == 0)
    {
        // quadFill(C[cubo.matrix[0][0][0].left], // laranja (traseira)
        quadFill(C[cubo.matrix[0][0][0].left], // verde (direita)
                 OFFSET, -S, OFFSET,
                 S, -S, OFFSET,
                 S, -S, S,
                 OFFSET, -S, S);
        quadFill(C[cubo.matrix[0][0][0].right],
                 S, -S, OFFSET,
                 S, -OFFSET, OFFSET,
                 S, -OFFSET, S,
                 S, -S, S);
        quadFill(C[cubo.matrix[0][0][0].mid],
                 OFFSET, -S, S,
                 S, -S, S,
                 S, -OFFSET, S,
                 OFFSET, -OFFSET, S);
    }
    else if (cubo.matrix[0][0][0].orientation == 1)
    {
        quadFill(C[cubo.matrix[0][0][0].right], // verde (direita)
                 OFFSET, -S, OFFSET,
                 S, -S, OFFSET,
                 S, -S, S,
                 OFFSET, -S, S);
        quadFill(C[cubo.matrix[0][0][0].mid],
                 S, -S, OFFSET,
                 S, -OFFSET, OFFSET,
                 S, -OFFSET, S,
                 S, -S, S);
        quadFill(C[cubo.matrix[0][0][0].left],
                 OFFSET, -S, S,
                 S, -S, S,
                 S, -OFFSET, S,
                 OFFSET, -OFFSET, S);
    }
    else
    {
        quadFill(C[cubo.matrix[0][0][0].mid], // verde (direita)
                 OFFSET, -S, OFFSET,
                 S, -S, OFFSET,
                 S, -S, S,
                 OFFSET, -S, S);
        quadFill(C[cubo.matrix[0][0][0].left],
                 S, -S, OFFSET,
                 S, -OFFSET, OFFSET,
                 S, -OFFSET, S,
                 S, -S, S);
        quadFill(C[cubo.matrix[0][0][0].right],
                 OFFSET, -S, S,
                 S, -S, S,
                 S, -OFFSET, S,
                 OFFSET, -OFFSET, S);
    }

    // Cubo superior direita fundo
    if (cubo.matrix[0][1][0].orientation == 0)
    {
        quadFill(C[cubo.matrix[0][1][0].left], // laranja (traseira)
                 -S, -OFFSET, OFFSET,
                 -S, -S, OFFSET,
                 -S, -S, S,
                 -S, -OFFSET, S);
        quadFill(C[cubo.matrix[0][1][0].right], // azul (esquerda)
                 -S, -S, OFFSET,
                 -OFFSET, -S, OFFSET,
                 -OFFSET, -S, S,
                 -S, -S, S);
        quadFill(C[cubo.matrix[0][1][0].mid], // amarelo (face superior)
                 -S, -S, S,
                 -OFFSET, -S, S,
                 -OFFSET, -OFFSET, S,
                 -S, -OFFSET, S);
    }
    else if (cubo.matrix[0][1][0].orientation == 1)
    {
        quadFill(C[cubo.matrix[0][1][0].right], // laranja (traseira)
                 -S, -OFFSET, OFFSET,
                 -S, -S, OFFSET,
                 -S, -S, S,
                 -S, -OFFSET, S);
        quadFill(C[cubo.matrix[0][1][0].mid], // azul (esquerda)
                 -S, -S, OFFSET,
                 -OFFSET, -S, OFFSET,
                 -OFFSET, -S, S,
                 -S, -S, S);
        quadFill(C[cubo.matrix[0][1][0].left], // amarelo (face superior)
                 -S, -S, S,
                 -OFFSET, -S, S,
                 -OFFSET, -OFFSET, S,
                 -S, -OFFSET, S);
    }
    else
    {
        quadFill(C[cubo.matrix[0][1][0].mid], // laranja (traseira)
                 -S, -OFFSET, OFFSET,
                 -S, -S, OFFSET,
                 -S, -S, S,
                 -S, -OFFSET, S);
        quadFill(C[cubo.matrix[0][1][0].left], // azul (esquerda)
                 -S, -S, OFFSET,
                 -OFFSET, -S, OFFSET,
                 -OFFSET, -S, S,
                 -S, -S, S);
        quadFill(C[cubo.matrix[0][1][0].right], // amarelo (face superior)
                 -S, -S, S,
                 -OFFSET, -S, S,
                 -OFFSET, -OFFSET, S,
                 -S, -OFFSET, S);
    }

    // Cubo superior esquerda frente OK
    if (cubo.matrix[1][0][0].orientation == 0)
    {
        quadFill(C[cubo.matrix[1][0][0].left],
                 S, OFFSET, OFFSET,
                 S, S, OFFSET,
                 S, S, S,
                 S, OFFSET, S);

        quadFill(C[cubo.matrix[1][0][0].right],
                 OFFSET, S, OFFSET,
                 S, S, OFFSET,
                 S, S, S,
                 OFFSET, S, S);
        quadFill(C[cubo.matrix[1][0][0].mid],
                 S, OFFSET, S,
                 S, S, S,
                 OFFSET, S, S,
                 OFFSET, OFFSET, S);
    }
    else if (cubo.matrix[1][0][0].orientation == 1)
    {
        quadFill(C[cubo.matrix[1][0][0].right],
                 S, OFFSET, OFFSET,
                 S, S, OFFSET,
                 S, S, S,
                 S, OFFSET, S);

        quadFill(C[cubo.matrix[1][0][0].mid],
                 OFFSET, S, OFFSET,
                 S, S, OFFSET,
                 S, S, S,
                 OFFSET, S, S);
        quadFill(C[cubo.matrix[1][0][0].left],
                 S, OFFSET, S,
                 S, S, S,
                 OFFSET, S, S,
                 OFFSET, OFFSET, S);
    }
    else
    {
        quadFill(C[cubo.matrix[1][0][0].mid],
                 S, OFFSET, OFFSET,
                 S, S, OFFSET,
                 S, S, S,
                 S, OFFSET, S);

        quadFill(C[cubo.matrix[1][0][0].left],
                 OFFSET, S, OFFSET,
                 S, S, OFFSET,
                 S, S, S,
                 OFFSET, S, S);
        quadFill(C[cubo.matrix[1][0][0].right],
                 S, OFFSET, S,
                 S, S, S,
                 OFFSET, S, S,
                 OFFSET, OFFSET, S);
    }

    // Cubo superior direita frente
    if (cubo.matrix[1][1][0].orientation == 0)
    {
        quadFill(C[cubo.matrix[1][1][0].left],
                 -S, S, OFFSET,
                 -OFFSET, S, OFFSET,
                 -OFFSET, S, S,
                 -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].right], // vermelho (frente)
                 -S, S, OFFSET,
                 -S, OFFSET, OFFSET,
                 -S, OFFSET, S,
                 -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].mid],
                 -OFFSET, S, S,
                 -S, S, S,
                 -S, OFFSET, S,
                 -OFFSET, OFFSET, S);
    }
    else if (cubo.matrix[1][1][0].orientation == 1)
    {
        quadFill(C[cubo.matrix[1][1][0].right],
                 -S, S, OFFSET,
                 -OFFSET, S, OFFSET,
                 -OFFSET, S, S,
                 -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].mid], // vermelho (frente)
                 -S, S, OFFSET,
                 -S, OFFSET, OFFSET,
                 -S, OFFSET, S,
                 -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].left],
                 -OFFSET, S, S,
                 -S, S, S,
                 -S, OFFSET, S,
                 -OFFSET, OFFSET, S);
    }
    else
    {
        quadFill(C[cubo.matrix[1][1][0].mid],
                 -S, S, OFFSET,
                 -OFFSET, S, OFFSET,
                 -OFFSET, S, S,
                 -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].left], // vermelho (frente)
                 -S, S, OFFSET,
                 -S, OFFSET, OFFSET,
                 -S, OFFSET, S,
                 -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].right],
                 -OFFSET, S, S,
                 -S, S, S,
                 -S, OFFSET, S,
                 -OFFSET, OFFSET, S);
    }

    glutSwapBuffers();
}

void specialKeysListener(int key, int, int)
{
    // if (key == GLUT_KEY_RIGHT) rotY += 5;
    // else if (key == GLUT_KEY_LEFT) rotY -= 5;
    // else if (key == GLUT_KEY_UP)   rotX += 5;
    // else if (key == GLUT_KEY_DOWN) rotX -= 5;
    if (key == GLUT_KEY_RIGHT)
    {
        rotY += 5;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        rotY -= 5;
    }
    else if (key == GLUT_KEY_UP)
    {
        rotX += 5;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        rotX -= 5;
    }
    glutPostRedisplay();
}

void keyboardListener(unsigned char key, int, int)
{
    if (key == 'q' || key == 27)
        exit(0);
    if (key == 'r' || key == 'R')
    {
        rotX = 0.0;
        rotY = 0.0;
        glutPostRedisplay();
    } // reset
    if (key == 'l')
    {
        cubo = Move::L_FW(cubo);
        std::cout << "Mudou" << std::endl;
        glutPostRedisplay();
    }
    else if (key == 'L')
    {
        cubo = Move::L_BW(cubo);
        std::cout << "Mudou" << std::endl;
        glutPostRedisplay();
    }
    else if (key == 'u')
    {
        cubo = Move::U_FW(cubo);
        std::cout << "Mudou" << std::endl;
        glutPostRedisplay();
    }
    else if (key == 'U')
    {
        cubo = Move::U_BW(cubo);
        std::cout << "Mudou" << std::endl;
        glutPostRedisplay();
    }
    else if (key == 'f')
    {
        cubo = Move::F_FW(cubo);
        std::cout << "Mudou" << std::endl;
        glutPostRedisplay();
    }
    else if (key == 'F')
    {
        cubo = Move::F_BW(cubo);
        std::cout << "Mudou" << std::endl;
        glutPostRedisplay();
    }
    std::vector<Cube> path;
    if(key == 'b' || key == 'B') {
        bool achou = solver.bfs(cubo, path);
        if(achou) {
            for (Cube cube_path : path) {
                cubo = cube_path;
            }
        }
        glutPostRedisplay();
    } else if(key == 'd' || key == 'D') {
        solver.dfs(cubo, path);
    } else if(key == 'a' || key == 'A') {
        solver.A_star(cubo);
    }
    if(key == 's' || key == 'S') {
        cubo = cubo.shuffle(10, true);
        glutPostRedisplay();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(720, 720);
    glutCreateWindow("Cubo 2x2 - Frente Vermelha, Amarelo em cima (z+ para baixo)");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.9f, 0.9f, 0.9f, 1.f);

    setupCube();

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeysListener);
    glutKeyboardFunc(keyboardListener);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}