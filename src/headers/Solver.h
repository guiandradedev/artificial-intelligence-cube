#pragma once
#include <vector>
#include "Cube.h"
#include <functional>
#include <memory>

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

    
    struct Node2 {
        Cube cube;
        std::weak_ptr<Node2> root; // Ponteiro fraco para o pai para evitar ciclos de referência
        short int mov;
    };

    using NodePtr = std::shared_ptr<Node2>;
    using WeakNodePtr = std::weak_ptr<Node2>;
    /* 
       UFW = 0, UBW = 1,
       LFW = 2, LBW = 3,
       FFW = 4, FBW = 5
    */

    static constexpr char moviments_name[6][4] = { "UFW", "UBW", "LFW", "LBW", "FFW", "FBW" };


    void bfs(Cube cube);
    void dfs(Cube cube);

    void algorithm_parallel(const Cube& cube);
};