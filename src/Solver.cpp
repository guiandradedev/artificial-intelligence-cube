#include "Solver.h"
#include "Cube/Cube.h"
#include <queue>
#include <vector>
#include "Cube/Move.h"
#include <set>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <cstring>
#include "DataStructure/DataStructure.h"
#include "Hasher.h"
#include <random>
#include <algorithm>
#include "Node/Node.h"
#include <queue>
#include "Strategies/AlgorithmStrategy.h"
#include "Strategies/AStarStrategy.h"
#include "Strategies/DFSStrategy.h"
#include "Strategies/BFSStrategy.h"
using namespace std::chrono;

using namespace std;

Solver::Solver()
{
    final_state.init();
}

bool Solver::is_final_state(Node *current_state, std::vector<short int> &path, int i, int *num_tries)
{
    if (current_state->cube == final_state)
    {
        cout << "Solucao encontrada na " << i << " iteracao!" << endl;

        *num_tries = i;

        cout << "Reconstrucao do cubo:" << endl;
        int moves = 0;
        while (current_state->root != nullptr)
        {
            cout << moviments_name[current_state->mov] << endl;
            path.push_back(current_state->mov);
            current_state = current_state->root;
            moves++;
        }

        cout << "Com um total de " << moves << " movimentos." << endl;

        reverse(path.begin(), path.end());

        return true;
        // break;
    }
    return false;
}

bool Solver::algorithm(AlgorithmStrategy &strategy, Cube cube, std::vector<short> &path, int *num_tries)
{
    Node* root = strategy.create_root_node(cube);
    DataStructure* structure = strategy.create_data_structure();

    unordered_set<Cube> visited;
    auto start = high_resolution_clock::now();
    int i = 0;

    structure->insert(root);
    visited.insert(root->cube);

    while (!structure->isEmpty())
    {
        Node *state = structure->remove();

        if (strategy.poda(state))
        {
            continue;
        }

        if (is_final_state(state, path, i, num_tries))
            return true;

        for (const auto &moviment : state->cube.moviments)
        {
            strategy.sucessora(state, moviment, *structure, visited);
        }
        i++;
    }
    *num_tries = i;
    auto end = high_resolution_clock::now();
    cout << "Tempo Execução: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    return false;
}

bool Solver::bfs(Cube cube, std::vector<short int> &path, int *num_tries)
{
    BFSStrategy strategy;
    cout << "Iniciando BFS..." << endl;
    return algorithm(strategy, cube, path, num_tries);
}

bool Solver::dfs(Cube cube, std::vector<short int> &path, int *num_tries)
{
    BFSStrategy strategy;
    cout << "Iniciando DFS..." << endl;
    return algorithm(strategy, cube, path, num_tries);
}

bool Solver::A_star(Cube cube, std::vector<short int> &path, int *num_tries)
{
    AStarStrategy strategy;
    cout << "Iniciando A*..." << endl;
    return algorithm(strategy, cube, path, num_tries);
}
