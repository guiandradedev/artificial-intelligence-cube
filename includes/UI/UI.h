#pragma once

#include "Cube/Cube.h"
#include "Solver.h"
#include <string>
#include "Tools/RGB.h"

class UI
{
public:
    UI(int argc, char **argv, std::string window_title, int width, int height);
    void run();

private:
    // Métodos de Desenho
    void display();
    void renderOverlay();
    void drawText(float x, float y, const std::string &text, const RGB &color, void *font);
    void reshape(int w, int h);

    void showSolutionOverlay(const std::string &nome_algoritmo, bool achou, const std::vector<short int> &path, long long duration_ms, int num_tries);

    void drawCubies();
    inline void quadFill(const RGB &cor,
                                float x1, float y1, float z1,
                                float x2, float y2, float z2,
                                float x3, float y3, float z3,
                                float x4, float y4, float z4);

    // Métodos de Eventos
    void keyboardListener(unsigned char key, int x, int y);
    void specialKeysListener(int key, int x, int y);

    // Callbacks estáticos para o GLUT
    static void displayCallback();
    static void reshapeCallback(int w, int h);
    static void keyboardCallback(unsigned char key, int x, int y);
    static void specialKeysCallback(int key, int x, int y);

    // Estado da Aplicação
    Cube cubo;
    Solver solver;
    double rotY = 0.0, rotX = 0.0;
    const float OFFSET = 0.01f;                   // separação entre cubinhos
    const float SIZE = 0.5f;                      // semi-tamanho do cubinho
    std::string path_message, execution_time_message, algoritm_message, num_tries_message;

    // Ponteiro estático para a instância única da UI
    static UI *instance;
};