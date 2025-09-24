#pragma once
#include <vector>
#include "Cube/Cube.h"
#include <functional>
#include <unordered_set> 

class Node;
class DataStructure;
class AlgorithmStrategy;

class Solver
{
public:
    Solver();
    Cube final_state;

    static constexpr char moviments_name[6][4] = {"UFW", "UBW", "LFW", "LBW", "FFW", "FBW"};

    using SucessoraCallback = void(*)(Node *current_state, short int moviment, DataStructure& structure, std::unordered_set<Cube>& visited);
    using PodaCallback = bool(*)(Node* current_state);

    bool A_star(Cube cube, std::vector<short int> &path, int *num_tries);
    bool bfs(Cube cube, std::vector<short int> &path, int *num_tries);
    bool dfs(Cube cube, std::vector<short int> &path, int *num_tries);

protected:
    bool is_final_state(Node* current_state, std::vector<short int> &path, int i, int *num_tries);
    bool algorithm(AlgorithmStrategy &strategy, Cube cube, std::vector<short> &path, int *num_tries);
};