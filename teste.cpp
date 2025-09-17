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
#include "Hasher.h"
#include <string>
#include <chrono>

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

std::string overlay_message = "";

void setupCube()
{
    cubo.init();
    Hasher::init("./src/hashing.bin");
}

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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(5.0, -2.0, 2.0,
              0.0, 0.0, 0.0,
              0.0, 0.0, 1.0);
    glRotatef(-90, 0.f, 0.f, 1.f);
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
        quadFill(C[cubo.matrix[0][0][1].right], OFFSET, -S, -OFFSET, S, -S, -OFFSET, S, -S, -S, OFFSET, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].left], S, -S, -OFFSET, S, -OFFSET, -OFFSET, S, -OFFSET, -S, S, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].mid], OFFSET, -S, -S, S, -S, -S, S, -OFFSET, -S, OFFSET, -OFFSET, -S);
    }
    else if (cubo.matrix[0][0][1].orientation == 1)
    {
        quadFill(C[cubo.matrix[0][0][1].mid], OFFSET, -S, -OFFSET, S, -S, -OFFSET, S, -S, -S, OFFSET, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].right], S, -S, -OFFSET, S, -OFFSET, -OFFSET, S, -OFFSET, -S, S, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].left], OFFSET, -S, -S, S, -S, -S, S, -OFFSET, -S, OFFSET, -OFFSET, -S);
    }
    else
    {
        quadFill(C[cubo.matrix[0][0][1].mid], OFFSET, -S, -OFFSET, S, -S, -OFFSET, S, -S, -S, OFFSET, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].right], S, -S, -OFFSET, S, -OFFSET, -OFFSET, S, -OFFSET, -S, S, -S, -S);
        quadFill(C[cubo.matrix[0][0][1].left], OFFSET, -S, -S, S, -S, -S, S, -OFFSET, -S, OFFSET, -OFFSET, -S);
    }

    // Cubo inferior direita fundo
    if (cubo.matrix[0][1][1].orientation == 0)
    {
        quadFill(C[cubo.matrix[0][1][1].right], -S, -OFFSET, -OFFSET, -S, -S, -OFFSET, -S, -S, -S, -S, -OFFSET, -S);
        quadFill(C[cubo.matrix[0][1][1].left], -S, -S, -OFFSET, -OFFSET, -S, -OFFSET, -OFFSET, -S, -S, -S, -S, -S);
        quadFill(C[cubo.matrix[0][1][1].mid], -S, -S, -S, -OFFSET, -S, -S, -OFFSET, -OFFSET, -S, -S, -OFFSET, -S);
    }
    else if (cubo.matrix[0][1][1].orientation == 1)
    {
        quadFill(C[cubo.matrix[0][1][1].mid], -S, -OFFSET, -OFFSET, -S, -S, -OFFSET, -S, -S, -S, -S, -OFFSET, -S);
        quadFill(C[cubo.matrix[0][1][1].right], -S, -S, -OFFSET, -OFFSET, -S, -OFFSET, -OFFSET, -S, -S, -S, -S, -S);
        quadFill(C[cubo.matrix[0][1][1].left], -S, -S, -S, -OFFSET, -S, -S, -OFFSET, -OFFSET, -S, -S, -OFFSET, -S);
    }
    else
    {
        quadFill(C[cubo.matrix[0][1][1].mid], -S, -OFFSET, -OFFSET, -S, -S, -OFFSET, -S, -S, -S, -S, -OFFSET, -S);
        quadFill(C[cubo.matrix[0][1][1].right], -S, -S, -OFFSET, -OFFSET, -S, -OFFSET, -OFFSET, -S, -S, -S, -S, -S);
        quadFill(C[cubo.matrix[0][1][1].left], -S, -S, -S, -OFFSET, -S, -S, -OFFSET, -OFFSET, -S, -S, -OFFSET, -S);
    }

    // Cubo inferior esquerda frente
    if (cubo.matrix[1][0][1].orientation == 0)
    {
        quadFill(C[cubo.matrix[1][0][1].right], S, OFFSET, -OFFSET, S, S, -OFFSET, S, S, -S, S, OFFSET, -S);
        quadFill(C[cubo.matrix[1][0][1].left], OFFSET, S, -OFFSET, S, S, -OFFSET, S, S, -S, OFFSET, S, -S);
        quadFill(C[cubo.matrix[1][0][1].mid], S, OFFSET, -S, S, S, -S, OFFSET, S, -S, OFFSET, OFFSET, -S);
    }
    else if (cubo.matrix[1][0][1].orientation == 1)
    {
        quadFill(C[cubo.matrix[1][0][1].mid], S, OFFSET, -OFFSET, S, S, -OFFSET, S, S, -S, S, OFFSET, -S);
        quadFill(C[cubo.matrix[1][0][1].right], OFFSET, S, -OFFSET, S, S, -OFFSET, S, S, -S, OFFSET, S, -S);
        quadFill(C[cubo.matrix[1][0][1].left], S, OFFSET, -S, S, S, -S, OFFSET, S, -S, OFFSET, OFFSET, -S);
    }
    else
    {
        // esse ta diferente?
        quadFill(C[cubo.matrix[1][0][1].left], S, OFFSET, -OFFSET, S, S, -OFFSET, S, S, -S, S, OFFSET, -S);
        quadFill(C[cubo.matrix[1][0][1].mid], OFFSET, S, -OFFSET, S, S, -OFFSET, S, S, -S, OFFSET, S, -S);
        quadFill(C[cubo.matrix[1][0][1].right], S, OFFSET, -S, S, S, -S, OFFSET, S, -S, OFFSET, OFFSET, -S);
    }

    // Cubo inferior direita frente
    if (cubo.matrix[1][1][1].orientation == 0)
    {
        quadFill(C[cubo.matrix[1][1][1].right], -S, S, -OFFSET, -OFFSET, S, -OFFSET, -OFFSET, S, -S, -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].left], -S, S, -OFFSET, -S, OFFSET, -OFFSET, -S, OFFSET, -S, -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].mid], -OFFSET, S, -S, -S, S, -S, -S, OFFSET, -S, -OFFSET, OFFSET, -S);
    }
    else if (cubo.matrix[1][1][1].orientation == 1)
    {
        quadFill(C[cubo.matrix[1][1][1].mid], -S, S, -OFFSET, -OFFSET, S, -OFFSET, -OFFSET, S, -S, -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].right], -S, S, -OFFSET, -S, OFFSET, -OFFSET, -S, OFFSET, -S, -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].left], -OFFSET, S, -S, -S, S, -S, -S, OFFSET, -S, -OFFSET, OFFSET, -S);
    }
    else
    {
        quadFill(C[cubo.matrix[1][1][1].left], -S, S, -OFFSET, -OFFSET, S, -OFFSET, -OFFSET, S, -S, -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].mid], -S, S, -OFFSET, -S, OFFSET, -OFFSET, -S, OFFSET, -S, -S, S, -S);
        quadFill(C[cubo.matrix[1][1][1].right], -OFFSET, S, -S, -S, S, -S, -S, OFFSET, -S, -OFFSET, OFFSET, -S);
    }

    // Cubo superior esquerda fundo
    if (cubo.matrix[0][0][0].orientation == 0)
    {
        // quadFill(C[cubo.matrix[0][0][0].left], // laranja (traseira)
        quadFill(C[cubo.matrix[0][0][0].left], OFFSET, -S, OFFSET, S, -S, OFFSET, S, -S, S, OFFSET, -S, S);
        quadFill(C[cubo.matrix[0][0][0].right], S, -S, OFFSET, S, -OFFSET, OFFSET, S, -OFFSET, S, S, -S, S);
        quadFill(C[cubo.matrix[0][0][0].mid], OFFSET, -S, S, S, -S, S, S, -OFFSET, S, OFFSET, -OFFSET, S);
    }
    else if (cubo.matrix[0][0][0].orientation == 1)
    {
        quadFill(C[cubo.matrix[0][0][0].right], OFFSET, -S, OFFSET, S, -S, OFFSET, S, -S, S, OFFSET, -S, S);
        quadFill(C[cubo.matrix[0][0][0].mid], S, -S, OFFSET, S, -OFFSET, OFFSET, S, -OFFSET, S, S, -S, S);
        quadFill(C[cubo.matrix[0][0][0].left], OFFSET, -S, S, S, -S, S, S, -OFFSET, S, OFFSET, -OFFSET, S);
    }
    else
    {
        quadFill(C[cubo.matrix[0][0][0].mid], OFFSET, -S, OFFSET, S, -S, OFFSET, S, -S, S, OFFSET, -S, S);
        quadFill(C[cubo.matrix[0][0][0].left], S, -S, OFFSET, S, -OFFSET, OFFSET, S, -OFFSET, S, S, -S, S);
        quadFill(C[cubo.matrix[0][0][0].right], OFFSET, -S, S, S, -S, S, S, -OFFSET, S, OFFSET, -OFFSET, S);
    }

    // Cubo superior direita fundo
    if (cubo.matrix[0][1][0].orientation == 0)
    {
        quadFill(C[cubo.matrix[0][1][0].left], -S, -OFFSET, OFFSET, -S, -S, OFFSET, -S, -S, S, -S, -OFFSET, S);
        quadFill(C[cubo.matrix[0][1][0].right], -S, -S, OFFSET, -OFFSET, -S, OFFSET, -OFFSET, -S, S, -S, -S, S);
        quadFill(C[cubo.matrix[0][1][0].mid], -S, -S, S, -OFFSET, -S, S, -OFFSET, -OFFSET, S, -S, -OFFSET, S);
    }
    else if (cubo.matrix[0][1][0].orientation == 1)
    {
        quadFill(C[cubo.matrix[0][1][0].right], -S, -OFFSET, OFFSET, -S, -S, OFFSET, -S, -S, S, -S, -OFFSET, S);
        quadFill(C[cubo.matrix[0][1][0].mid], -S, -S, OFFSET, -OFFSET, -S, OFFSET, -OFFSET, -S, S, -S, -S, S);
        quadFill(C[cubo.matrix[0][1][0].left], -S, -S, S, -OFFSET, -S, S, -OFFSET, -OFFSET, S, -S, -OFFSET, S);
    }
    else
    {
        quadFill(C[cubo.matrix[0][1][0].mid], -S, -OFFSET, OFFSET, -S, -S, OFFSET, -S, -S, S, -S, -OFFSET, S);
        quadFill(C[cubo.matrix[0][1][0].left], -S, -S, OFFSET, -OFFSET, -S, OFFSET, -OFFSET, -S, S, -S, -S, S);
        quadFill(C[cubo.matrix[0][1][0].right], -S, -S, S, -OFFSET, -S, S, -OFFSET, -OFFSET, S, -S, -OFFSET, S);
    }

    // Cubo superior esquerda frente OK
    if (cubo.matrix[1][0][0].orientation == 0)
    {
        quadFill(C[cubo.matrix[1][0][0].left], S, OFFSET, OFFSET, S, S, OFFSET, S, S, S, S, OFFSET, S);
        quadFill(C[cubo.matrix[1][0][0].right], OFFSET, S, OFFSET, S, S, OFFSET, S, S, S, OFFSET, S, S);
        quadFill(C[cubo.matrix[1][0][0].mid], S, OFFSET, S, S, S, S, OFFSET, S, S, OFFSET, OFFSET, S);
    }
    else if (cubo.matrix[1][0][0].orientation == 1)
    {
        quadFill(C[cubo.matrix[1][0][0].right], S, OFFSET, OFFSET, S, S, OFFSET, S, S, S, S, OFFSET, S);
        quadFill(C[cubo.matrix[1][0][0].mid], OFFSET, S, OFFSET, S, S, OFFSET, S, S, S, OFFSET, S, S);
        quadFill(C[cubo.matrix[1][0][0].left], S, OFFSET, S, S, S, S, OFFSET, S, S, OFFSET, OFFSET, S);
    }
    else
    {
        quadFill(C[cubo.matrix[1][0][0].mid], S, OFFSET, OFFSET, S, S, OFFSET, S, S, S, S, OFFSET, S);
        quadFill(C[cubo.matrix[1][0][0].left], OFFSET, S, OFFSET, S, S, OFFSET, S, S, S, OFFSET, S, S);
        quadFill(C[cubo.matrix[1][0][0].right], S, OFFSET, S, S, S, S, OFFSET, S, S, OFFSET, OFFSET, S);
    }

    // Cubo superior direita frente
    if (cubo.matrix[1][1][0].orientation == 0)
    {
        quadFill(C[cubo.matrix[1][1][0].left], -S, S, OFFSET, -OFFSET, S, OFFSET, -OFFSET, S, S, -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].right], -S, S, OFFSET, -S, OFFSET, OFFSET, -S, OFFSET, S, -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].mid], -OFFSET, S, S, -S, S, S, -S, OFFSET, S, -OFFSET, OFFSET, S);
    }
    else if (cubo.matrix[1][1][0].orientation == 1)
    {
        quadFill(C[cubo.matrix[1][1][0].right], -S, S, OFFSET, -OFFSET, S, OFFSET, -OFFSET, S, S, -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].mid], -S, S, OFFSET, -S, OFFSET, OFFSET, -S, OFFSET, S, -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].left], -OFFSET, S, S, -S, S, S, -S, OFFSET, S, -OFFSET, OFFSET, S);
    }
    else
    {
        quadFill(C[cubo.matrix[1][1][0].mid], -S, S, OFFSET, -OFFSET, S, OFFSET, -OFFSET, S, S, -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].left], -S, S, OFFSET, -S, OFFSET, OFFSET, -S, OFFSET, S, -S, S, S);
        quadFill(C[cubo.matrix[1][1][0].right], -OFFSET, S, S, -S, S, S, -S, OFFSET, S, -OFFSET, OFFSET, S);
    }

    if (!overlay_message.empty())
    {
        // Salva as matrizes atuais
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        gluOrtho2D(0, viewport[2], 0, viewport[3]);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        // Define cor do texto (vermelho)
        glColor3f(1.0f, 0.0f, 0.0f);
        // Posição: canto superior esquerdo
        float x = 10.0f;
        float y = viewport[3] - 30.0f;
        glRasterPos2f(x, y);
        for (const char *c = overlay_message.c_str(); *c != '\0'; ++c)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }

        // Restaura as matrizes
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

    glutSwapBuffers();
}

void specialKeysListener(int key, int, int)
{
    if (key == GLUT_KEY_RIGHT)
        rotY += 5;
    else if (key == GLUT_KEY_LEFT)
        rotY -= 5;
    else if (key == GLUT_KEY_UP)
        rotX += 5;
    else if (key == GLUT_KEY_DOWN)
        rotX -= 5;
    glutPostRedisplay();
}

void showSolutionOverlay(const std::string &nome_algoritmo, bool achou, const std::vector<Solver::Node *> &path, long long duration_ms)
{
    if (achou)
    {
        overlay_message = "Caminho " + nome_algoritmo + ": ";
        for (size_t i = 0; i < path.size(); ++i)
        {
            Solver::Node *node_path = path[i];
            overlay_message += Solver::moviments_name[node_path->mov] + std::string(" -> ");
        }
        overlay_message += "\nTempo: " + std::to_string(duration_ms) + " ms";
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
    if (key == 'l' || key == 'L' || key == 'u' || key == 'U' || key == 'f' || key == 'F')
    {
        if (key == 'l')
            cubo = Move::L_FW(cubo);
        if (key == 'L')
            cubo = Move::L_BW(cubo);
        if (key == 'f')
            cubo = Move::F_FW(cubo);
        if (key == 'F')
            cubo = Move::F_BW(cubo);
        if (key == 'u')
            cubo = Move::U_FW(cubo);
        if (key == 'U')
            cubo = Move::U_BW(cubo);

        std::cout << "Mudou" << std::endl;
        glutPostRedisplay();
    }
    std::vector<Solver::Node *> path;
    if (key == 'b' || key == 'B')
    {
        auto start = std::chrono::high_resolution_clock::now();
        bool achou = solver.bfs(cubo, path);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        showSolutionOverlay("BFS", achou, path, duration_ms);
    }
    else if (key == 'd' || key == 'D')
    {
        solver.dfs(cubo, path);
    }
    else if (key == 'a' || key == 'A')
    {
        solver.A_star(cubo);
    }
    if (key == 's' || key == 'S')
    {
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