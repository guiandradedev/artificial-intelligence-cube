#pragma once

#include "Cube.h"
#include <functional>

class DataStructure; // Declaracao antecipada

class Solver {
protected:
    void algorithm(Cube cube, DataStructure& structure);

public:
    Solver();       
    struct Node {
        Cube cube;
        Node* root;
        char mov[4];
    };
    Cube final_state;

    void bfs(Cube cube);
    void dfs(Cube cube);
};