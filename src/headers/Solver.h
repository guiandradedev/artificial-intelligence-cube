#pragma once
#include <vector>
#include "Cube.h"
#include <functional>

class DataStructure; // Declaracao antecipada

class Solver {
protected:
    void algorithm(Cube cube, DataStructure& structure, int max_depth);

public:
    Solver();       
    struct Node {
        Cube cube;
        Node* root;
        short int mov; // Movimento que gerou esse estado
        int depth;
    };
    Cube final_state;

    /* 
       UFW = 0, UBW = 1,
       LFW = 2, LBW = 3,
       FFW = 4, FBW = 5
    */

    static constexpr char moviments_name[6][4] = { "UFW", "UBW", "LFW", "LBW", "FFW", "FBW" };


    void bfs(Cube cube);
    void dfs(Cube cube);
};