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
        short int mov; // Movimento que gerou esse estado
    };
    Cube final_state;

    void bfs(Cube cube);
    void dfs(Cube cube);
};