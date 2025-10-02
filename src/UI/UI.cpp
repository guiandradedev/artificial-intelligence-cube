#include <cstdio>
#define GL_GLEXT_PROTOTYPES
#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Cube/Cube.h"
#include "Cube/Move.h"
#include "Solver.h"
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include "UI/UI.h"

// Inicializa o ponteiro estático
UI *UI::instance = nullptr;

UI::UI(int argc, char **argv, UIDetails details)
{
    instance = this; // Armazena a instância atual para os callbacks estáticos

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(details.width, details.height);
    glutCreateWindow(details.window_title.c_str());
    glEnable(GL_DEPTH_TEST);
    // glClearColor(0.9f, 0.9f, 0.9f, 1.f);
    glClearColor(details.color.r, details.color.g, details.color.b, details.color.oppacity);

    cubo.init();

    // Registra os callbacks estáticos
    glutDisplayFunc(UI::displayCallback);
    glutReshapeFunc(UI::reshapeCallback);
    glutKeyboardFunc(UI::keyboardCallback);
    glutSpecialFunc(UI::specialKeysCallback);
}

// Thread que roda o OpenGL
void UI::run()
{
    glutMainLoop();
}

// Funcões estáticas do GLUT repassadas como parametro
void UI::displayCallback()
{
    if (instance)
        instance->display();
}
void UI::reshapeCallback(int w, int h)
{
    if (instance)
        instance->reshape(w, h);
}
void UI::keyboardCallback(unsigned char key, int x, int y)
{
    if (instance)
        instance->keyboardListener(key, x, y);
}
void UI::specialKeysCallback(int key, int x, int y)
{
    if (instance)
        instance->specialKeysListener(key, x, y);
}

void UI::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Define as posicões da câmera (rotacão e translacão)
    gluLookAt(5.0, -2.0, 2.0,
              0.0, 0.0, 0.0,
              0.0, 0.0, 1.0);
    glRotatef(-90, 0.f, 0.f, 1.f);
    glRotatef((float)rotX, 1.f, 0.f, 0.f);
    glRotatef((float)rotY, 0.f, 1.f, 0.f);

    drawCubies();
    renderOverlay(); // Texto na tela

    glutSwapBuffers();
}

void UI::drawText(float x, float y, const std::string &text, const RGB &color, void *font)
{
    glColor3f(color.r, color.g, color.b);
    glRasterPos2f(x, y);
    for (const char *c = text.c_str(); *c != '\0'; ++c)
    {
        glutBitmapCharacter(font, *c);
    }
}
void UI::reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
}
void UI::keyboardListener(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 27)
        exit(0);
    if (key == 'r' || key == 'R')
    {
        rotX = 0.0;
        rotY = 0.0;
        glutPostRedisplay();
    } // reset da câmera
    if (key == 'l' || key == 'L' || key == 'u' || key == 'U' || key == 'f' || key == 'F')
    {
        if (key == 'l'){
            cubo = Move::L_FW(cubo);
            std::cout<<"Movimentou L"<< std::endl;
        }
        if (key == 'L'){
            cubo = Move::L_BW(cubo);
            std::cout<<"Movimentou L'"<< std::endl;
        }
        if (key == 'f'){
            cubo = Move::F_FW(cubo);
            std::cout<<"Movimentou F"<< std::endl;
        }
        if (key == 'F'){
            cubo = Move::F_BW(cubo);
            std::cout<<"Movimentou F'"<< std::endl;
        }
        if (key == 'u'){
            cubo = Move::U_FW(cubo);
            std::cout<<"Movimentou U" << std::endl;
        }
        if (key == 'U'){
            cubo = Move::U_BW(cubo);
            std::cout<<"Movimentou U'"<< std::endl;
        }

       
        glutPostRedisplay();
    }
    std::vector<short int> path;
    int num_tries = 0;
    if (key == 'b' || key == 'B')
    {
        auto start = std::chrono::high_resolution_clock::now();
        bool achou = solver.bfs(cubo, path, &num_tries);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        showSolutionOverlay("BFS", achou, path, duration_ms, num_tries);
    }
    else if (key == 'd' || key == 'D')
    {
        auto start = std::chrono::high_resolution_clock::now();
        bool achou = solver.dfs(cubo, path, &num_tries);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        showSolutionOverlay("DFS", achou, path, duration_ms, num_tries);
    }
    else if (key == 'a' || key == 'A')
    {
        auto start = std::chrono::high_resolution_clock::now();
        bool achou = solver.A_star(cubo, path, &num_tries, -1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        showSolutionOverlay("A*", achou, path, duration_ms, num_tries);
    }
    if (key == 's' || key == 'S')
    {
        cubo = cubo.shuffle(10, true);
        glutPostRedisplay();
    }
}

void UI::specialKeysListener(int key, int x, int y)
{
    // Realiza a rotacão da câmera utilizando as setas do teclado
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

// Desenha quadrados no plano 3D
inline void UI::quadFill(const RGB &cor,
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

// Funcões especificas para modularidade do código
void UI::showSolutionOverlay(const std::string &nome_algoritmo, bool achou, const std::vector<short int> &path, long long duration_ms, int num_tries)
{
    if (achou)
    {
        std::ostringstream oss;
        algoritm_message = "Caminho " + nome_algoritmo;
        execution_time_message = "Tempo de execucao: " + std::to_string(duration_ms) + " ms";
        num_tries_message = "Numero de estados visitados: " + std::to_string(num_tries);
        num_moves_message = "Numero de movimentos: " + std::to_string(path.size());
        if (!path.empty())
        {
            for (size_t i = 0; i < path.size() - 1; ++i)
            {
                oss << moviments_name[path[i]] << " -> ";
            }
            oss << moviments_name[path.back()]; // Adiciona o último sem "->"
        }
        path_message = oss.str();
    }
    else
    {
        algoritm_message = "Algoritmo " + nome_algoritmo;
        execution_time_message = ""; // Limpa a mensagem de tempo
        path_message = "Solucao nao encontrada.";
    }
    glutPostRedisplay();
}
void UI::renderOverlay()
{
    // Prepara o ambiente 2D para desenhar texto
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    gluOrtho2D(0, viewport[2], 0, viewport[3]);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    // Desenha a mensagem da solução uma embaixo da outra
    float y_pos = viewport[3] - 30.0f;
    const float line_height = 20.0f; // Espaçamento entre as linhas

    if (!algoritm_message.empty())
    {
        drawText(10.0f, y_pos, algoritm_message, {1.0f, 0.0f, 0.0f}, GLUT_BITMAP_HELVETICA_18);
        y_pos -= line_height; // Move a posição Y para a próxima linha
    }
    if (!execution_time_message.empty())
    {
        drawText(10.0f, y_pos, execution_time_message, {1.0f, 0.0f, 0.0f}, GLUT_BITMAP_HELVETICA_18);
        y_pos -= line_height; // Move a posição Y para a próxima linha
    }
    if (!path_message.empty())
    {
        drawText(10.0f, y_pos, path_message, {1.0f, 0.0f, 0.0f}, GLUT_BITMAP_HELVETICA_18);
        y_pos -= line_height; // Move a posição Y para a próxima linha
    }
    if (!num_tries_message.empty())
    {
        drawText(10.0f, y_pos, num_tries_message, {1.0f, 0.0f, 0.0f}, GLUT_BITMAP_HELVETICA_18);
        y_pos -= line_height; // Move a posição Y para a próxima linha
    }
    if (!num_moves_message.empty())
    {
        drawText(10.0f, y_pos, num_moves_message, {1.0f, 0.0f, 0.0f}, GLUT_BITMAP_HELVETICA_18);
    }

    // Desenha um texto de ajuda fixo
    std::string help_text = "Setas: Rotacionar Camera | s: Embaralhar | b: BFS | d: DFS | a: A* | r: Resetar Camera | q: Sair";
    drawText(10.0f, 10.0f, help_text, {0.2f, 0.2f, 0.2f}, GLUT_BITMAP_HELVETICA_12);

    // Restaura o ambiente 3D
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
void UI::drawCubies()
{
    // Analisar a linha que não tem 0s e pegar o sinal dela e substituir 0.0f por sinalOFFSET

    // Indice Z=0 e Orientacao = 0: left, right, mid
    // Indice Z=1 e Orientacao = 0: right, left, mid
    if (cubo.matrix[0][0][1].orientation == 0)
    {
        quadFill(CubeColors[cubo.matrix[0][0][1].right], OFFSET, -SIZE, -OFFSET, SIZE, -SIZE, -OFFSET, SIZE, -SIZE, -SIZE, OFFSET, -SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][1].left], SIZE, -SIZE, -OFFSET, SIZE, -OFFSET, -OFFSET, SIZE, -OFFSET, -SIZE, SIZE, -SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][1].mid], OFFSET, -SIZE, -SIZE, SIZE, -SIZE, -SIZE, SIZE, -OFFSET, -SIZE, OFFSET, -OFFSET, -SIZE);
    }
    else if (cubo.matrix[0][0][1].orientation == 1)
    {
        quadFill(CubeColors[cubo.matrix[0][0][1].mid], OFFSET, -SIZE, -OFFSET, SIZE, -SIZE, -OFFSET, SIZE, -SIZE, -SIZE, OFFSET, -SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][1].right], SIZE, -SIZE, -OFFSET, SIZE, -OFFSET, -OFFSET, SIZE, -OFFSET, -SIZE, SIZE, -SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][1].left], OFFSET, -SIZE, -SIZE, SIZE, -SIZE, -SIZE, SIZE, -OFFSET, -SIZE, OFFSET, -OFFSET, -SIZE);
    }
    else
    {
        quadFill(CubeColors[cubo.matrix[0][0][1].mid], OFFSET, -SIZE, -OFFSET, SIZE, -SIZE, -OFFSET, SIZE, -SIZE, -SIZE, OFFSET, -SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][1].right], SIZE, -SIZE, -OFFSET, SIZE, -OFFSET, -OFFSET, SIZE, -OFFSET, -SIZE, SIZE, -SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][1].left], OFFSET, -SIZE, -SIZE, SIZE, -SIZE, -SIZE, SIZE, -OFFSET, -SIZE, OFFSET, -OFFSET, -SIZE);
    }

    // Cubo inferior direita fundo
    if (cubo.matrix[0][1][1].orientation == 0)
    {
        quadFill(CubeColors[cubo.matrix[0][1][1].right], -SIZE, -OFFSET, -OFFSET, -SIZE, -SIZE, -OFFSET, -SIZE, -SIZE, -SIZE, -SIZE, -OFFSET, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][1].left], -SIZE, -SIZE, -OFFSET, -OFFSET, -SIZE, -OFFSET, -OFFSET, -SIZE, -SIZE, -SIZE, -SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][1].mid], -SIZE, -SIZE, -SIZE, -OFFSET, -SIZE, -SIZE, -OFFSET, -OFFSET, -SIZE, -SIZE, -OFFSET, -SIZE);
    }
    else if (cubo.matrix[0][1][1].orientation == 1)
    {
        quadFill(CubeColors[cubo.matrix[0][1][1].mid], -SIZE, -OFFSET, -OFFSET, -SIZE, -SIZE, -OFFSET, -SIZE, -SIZE, -SIZE, -SIZE, -OFFSET, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][1].right], -SIZE, -SIZE, -OFFSET, -OFFSET, -SIZE, -OFFSET, -OFFSET, -SIZE, -SIZE, -SIZE, -SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][1].left], -SIZE, -SIZE, -SIZE, -OFFSET, -SIZE, -SIZE, -OFFSET, -OFFSET, -SIZE, -SIZE, -OFFSET, -SIZE);
    }
    else
    {
        quadFill(CubeColors[cubo.matrix[0][1][1].mid], -SIZE, -OFFSET, -OFFSET, -SIZE, -SIZE, -OFFSET, -SIZE, -SIZE, -SIZE, -SIZE, -OFFSET, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][1].right], -SIZE, -SIZE, -OFFSET, -OFFSET, -SIZE, -OFFSET, -OFFSET, -SIZE, -SIZE, -SIZE, -SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][1].left], -SIZE, -SIZE, -SIZE, -OFFSET, -SIZE, -SIZE, -OFFSET, -OFFSET, -SIZE, -SIZE, -OFFSET, -SIZE);
    }

    // Cubo inferior esquerda frente
    if (cubo.matrix[1][0][1].orientation == 0)
    {
        quadFill(CubeColors[cubo.matrix[1][0][1].right], SIZE, OFFSET, -OFFSET, SIZE, SIZE, -OFFSET, SIZE, SIZE, -SIZE, SIZE, OFFSET, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][1].left], OFFSET, SIZE, -OFFSET, SIZE, SIZE, -OFFSET, SIZE, SIZE, -SIZE, OFFSET, SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][1].mid], SIZE, OFFSET, -SIZE, SIZE, SIZE, -SIZE, OFFSET, SIZE, -SIZE, OFFSET, OFFSET, -SIZE);
    }
    else if (cubo.matrix[1][0][1].orientation == 1)
    {
        quadFill(CubeColors[cubo.matrix[1][0][1].mid], SIZE, OFFSET, -OFFSET, SIZE, SIZE, -OFFSET, SIZE, SIZE, -SIZE, SIZE, OFFSET, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][1].right], OFFSET, SIZE, -OFFSET, SIZE, SIZE, -OFFSET, SIZE, SIZE, -SIZE, OFFSET, SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][1].left], SIZE, OFFSET, -SIZE, SIZE, SIZE, -SIZE, OFFSET, SIZE, -SIZE, OFFSET, OFFSET, -SIZE);
    }
    else
    {
        // esse ta diferente?
        quadFill(CubeColors[cubo.matrix[1][0][1].left], SIZE, OFFSET, -OFFSET, SIZE, SIZE, -OFFSET, SIZE, SIZE, -SIZE, SIZE, OFFSET, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][1].mid], OFFSET, SIZE, -OFFSET, SIZE, SIZE, -OFFSET, SIZE, SIZE, -SIZE, OFFSET, SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][1].right], SIZE, OFFSET, -SIZE, SIZE, SIZE, -SIZE, OFFSET, SIZE, -SIZE, OFFSET, OFFSET, -SIZE);
    }

    // Cubo inferior direita frente
    if (cubo.matrix[1][1][1].orientation == 0)
    {
        quadFill(CubeColors[cubo.matrix[1][1][1].right], -SIZE, SIZE, -OFFSET, -OFFSET, SIZE, -OFFSET, -OFFSET, SIZE, -SIZE, -SIZE, SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][1].left], -SIZE, SIZE, -OFFSET, -SIZE, OFFSET, -OFFSET, -SIZE, OFFSET, -SIZE, -SIZE, SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][1].mid], -OFFSET, SIZE, -SIZE, -SIZE, SIZE, -SIZE, -SIZE, OFFSET, -SIZE, -OFFSET, OFFSET, -SIZE);
    }
    else if (cubo.matrix[1][1][1].orientation == 1)
    {
        quadFill(CubeColors[cubo.matrix[1][1][1].mid], -SIZE, SIZE, -OFFSET, -OFFSET, SIZE, -OFFSET, -OFFSET, SIZE, -SIZE, -SIZE, SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][1].right], -SIZE, SIZE, -OFFSET, -SIZE, OFFSET, -OFFSET, -SIZE, OFFSET, -SIZE, -SIZE, SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][1].left], -OFFSET, SIZE, -SIZE, -SIZE, SIZE, -SIZE, -SIZE, OFFSET, -SIZE, -OFFSET, OFFSET, -SIZE);
    }
    else
    {
        quadFill(CubeColors[cubo.matrix[1][1][1].left], -SIZE, SIZE, -OFFSET, -OFFSET, SIZE, -OFFSET, -OFFSET, SIZE, -SIZE, -SIZE, SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][1].mid], -SIZE, SIZE, -OFFSET, -SIZE, OFFSET, -OFFSET, -SIZE, OFFSET, -SIZE, -SIZE, SIZE, -SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][1].right], -OFFSET, SIZE, -SIZE, -SIZE, SIZE, -SIZE, -SIZE, OFFSET, -SIZE, -OFFSET, OFFSET, -SIZE);
    }

    // Cubo superior esquerda fundo
    if (cubo.matrix[0][0][0].orientation == 0)
    {
        // quadFill(CubeColors[cubo.matrix[0][0][0].left], // laranja (traseira)
        quadFill(CubeColors[cubo.matrix[0][0][0].left], OFFSET, -SIZE, OFFSET, SIZE, -SIZE, OFFSET, SIZE, -SIZE, SIZE, OFFSET, -SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][0].right], SIZE, -SIZE, OFFSET, SIZE, -OFFSET, OFFSET, SIZE, -OFFSET, SIZE, SIZE, -SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][0].mid], OFFSET, -SIZE, SIZE, SIZE, -SIZE, SIZE, SIZE, -OFFSET, SIZE, OFFSET, -OFFSET, SIZE);
    }
    else if (cubo.matrix[0][0][0].orientation == 1)
    {
        quadFill(CubeColors[cubo.matrix[0][0][0].right], OFFSET, -SIZE, OFFSET, SIZE, -SIZE, OFFSET, SIZE, -SIZE, SIZE, OFFSET, -SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][0].mid], SIZE, -SIZE, OFFSET, SIZE, -OFFSET, OFFSET, SIZE, -OFFSET, SIZE, SIZE, -SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][0].left], OFFSET, -SIZE, SIZE, SIZE, -SIZE, SIZE, SIZE, -OFFSET, SIZE, OFFSET, -OFFSET, SIZE);
    }
    else
    {
        quadFill(CubeColors[cubo.matrix[0][0][0].mid], OFFSET, -SIZE, OFFSET, SIZE, -SIZE, OFFSET, SIZE, -SIZE, SIZE, OFFSET, -SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][0].left], SIZE, -SIZE, OFFSET, SIZE, -OFFSET, OFFSET, SIZE, -OFFSET, SIZE, SIZE, -SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[0][0][0].right], OFFSET, -SIZE, SIZE, SIZE, -SIZE, SIZE, SIZE, -OFFSET, SIZE, OFFSET, -OFFSET, SIZE);
    }

    // Cubo superior direita fundo
    if (cubo.matrix[0][1][0].orientation == 0)
    {
        quadFill(CubeColors[cubo.matrix[0][1][0].left], -SIZE, -OFFSET, OFFSET, -SIZE, -SIZE, OFFSET, -SIZE, -SIZE, SIZE, -SIZE, -OFFSET, SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][0].right], -SIZE, -SIZE, OFFSET, -OFFSET, -SIZE, OFFSET, -OFFSET, -SIZE, SIZE, -SIZE, -SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][0].mid], -SIZE, -SIZE, SIZE, -OFFSET, -SIZE, SIZE, -OFFSET, -OFFSET, SIZE, -SIZE, -OFFSET, SIZE);
    }
    else if (cubo.matrix[0][1][0].orientation == 1)
    {
        quadFill(CubeColors[cubo.matrix[0][1][0].right], -SIZE, -OFFSET, OFFSET, -SIZE, -SIZE, OFFSET, -SIZE, -SIZE, SIZE, -SIZE, -OFFSET, SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][0].mid], -SIZE, -SIZE, OFFSET, -OFFSET, -SIZE, OFFSET, -OFFSET, -SIZE, SIZE, -SIZE, -SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][0].left], -SIZE, -SIZE, SIZE, -OFFSET, -SIZE, SIZE, -OFFSET, -OFFSET, SIZE, -SIZE, -OFFSET, SIZE);
    }
    else
    {
        quadFill(CubeColors[cubo.matrix[0][1][0].mid], -SIZE, -OFFSET, OFFSET, -SIZE, -SIZE, OFFSET, -SIZE, -SIZE, SIZE, -SIZE, -OFFSET, SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][0].left], -SIZE, -SIZE, OFFSET, -OFFSET, -SIZE, OFFSET, -OFFSET, -SIZE, SIZE, -SIZE, -SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[0][1][0].right], -SIZE, -SIZE, SIZE, -OFFSET, -SIZE, SIZE, -OFFSET, -OFFSET, SIZE, -SIZE, -OFFSET, SIZE);
    }

    // Cubo superior esquerda frente OK
    if (cubo.matrix[1][0][0].orientation == 0)
    {
        quadFill(CubeColors[cubo.matrix[1][0][0].left], SIZE, OFFSET, OFFSET, SIZE, SIZE, OFFSET, SIZE, SIZE, SIZE, SIZE, OFFSET, SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][0].right], OFFSET, SIZE, OFFSET, SIZE, SIZE, OFFSET, SIZE, SIZE, SIZE, OFFSET, SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][0].mid], SIZE, OFFSET, SIZE, SIZE, SIZE, SIZE, OFFSET, SIZE, SIZE, OFFSET, OFFSET, SIZE);
    }
    else if (cubo.matrix[1][0][0].orientation == 1)
    {
        quadFill(CubeColors[cubo.matrix[1][0][0].right], SIZE, OFFSET, OFFSET, SIZE, SIZE, OFFSET, SIZE, SIZE, SIZE, SIZE, OFFSET, SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][0].mid], OFFSET, SIZE, OFFSET, SIZE, SIZE, OFFSET, SIZE, SIZE, SIZE, OFFSET, SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][0].left], SIZE, OFFSET, SIZE, SIZE, SIZE, SIZE, OFFSET, SIZE, SIZE, OFFSET, OFFSET, SIZE);
    }
    else
    {
        quadFill(CubeColors[cubo.matrix[1][0][0].mid], SIZE, OFFSET, OFFSET, SIZE, SIZE, OFFSET, SIZE, SIZE, SIZE, SIZE, OFFSET, SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][0].left], OFFSET, SIZE, OFFSET, SIZE, SIZE, OFFSET, SIZE, SIZE, SIZE, OFFSET, SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[1][0][0].right], SIZE, OFFSET, SIZE, SIZE, SIZE, SIZE, OFFSET, SIZE, SIZE, OFFSET, OFFSET, SIZE);
    }

    // Cubo superior direita frente
    if (cubo.matrix[1][1][0].orientation == 0)
    {
        quadFill(CubeColors[cubo.matrix[1][1][0].left], -SIZE, SIZE, OFFSET, -OFFSET, SIZE, OFFSET, -OFFSET, SIZE, SIZE, -SIZE, SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][0].right], -SIZE, SIZE, OFFSET, -SIZE, OFFSET, OFFSET, -SIZE, OFFSET, SIZE, -SIZE, SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][0].mid], -OFFSET, SIZE, SIZE, -SIZE, SIZE, SIZE, -SIZE, OFFSET, SIZE, -OFFSET, OFFSET, SIZE);
    }
    else if (cubo.matrix[1][1][0].orientation == 1)
    {
        quadFill(CubeColors[cubo.matrix[1][1][0].right], -SIZE, SIZE, OFFSET, -OFFSET, SIZE, OFFSET, -OFFSET, SIZE, SIZE, -SIZE, SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][0].mid], -SIZE, SIZE, OFFSET, -SIZE, OFFSET, OFFSET, -SIZE, OFFSET, SIZE, -SIZE, SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][0].left], -OFFSET, SIZE, SIZE, -SIZE, SIZE, SIZE, -SIZE, OFFSET, SIZE, -OFFSET, OFFSET, SIZE);
    }
    else
    {
        quadFill(CubeColors[cubo.matrix[1][1][0].mid], -SIZE, SIZE, OFFSET, -OFFSET, SIZE, OFFSET, -OFFSET, SIZE, SIZE, -SIZE, SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][0].left], -SIZE, SIZE, OFFSET, -SIZE, OFFSET, OFFSET, -SIZE, OFFSET, SIZE, -SIZE, SIZE, SIZE);
        quadFill(CubeColors[cubo.matrix[1][1][0].right], -OFFSET, SIZE, SIZE, -SIZE, SIZE, SIZE, -SIZE, OFFSET, SIZE, -OFFSET, OFFSET, SIZE);
    }
}