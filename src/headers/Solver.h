#ifndef SOLVER_H
#define SOLVER_H

#pragma once
#include <vector>
#include "Cube.h"
#include <functional>

class DataStructure; // Declaracao antecipada

class Solver
{
protected:
    bool algorithm(Cube cube, DataStructure &structure, std::vector<Cube>& path);

public:
    Solver();
    struct Node{
        Cube cube;
        Node *root;
        short int mov; // Movimento que gerou esse estado
    };
    
    Cube final_state;

    struct AstarNode{
        Cube cube;
        int g_cost; // custo para chegar
        int f_cost; // f = g + h, custo total

        bool operator>(const AstarNode &other) const
        {
            return f_cost > other.f_cost;
        }
    };

    /*
       UFW = 0, UBW = 1,
       LFW = 2, LBW = 3,
       FFW = 4, FBW = 5
    */

    static constexpr char moviments_name[6][4] = {"UFW", "UBW", "LFW", "LBW", "FFW", "FBW"};

    void A_star(Cube cube);
    bool bfs(Cube cube, std::vector<Cube>& path);
    bool dfs(Cube cube, std::vector<Cube>& path);
};

#endif