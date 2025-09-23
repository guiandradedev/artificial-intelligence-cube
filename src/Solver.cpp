#include "Solver.h"
#include "Cube.h"
#include <queue>
#include <vector>
#include <stack>
#include "Move.h"
#include <set>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <cstring>
#include "DataStructure.h"
#include "Queue.h"
#include "Stack.h"
#include "Hasher.h"
#include <random>
#include <algorithm>
#include "Node.h"
#include "AstarNode.h"
#include "PriorityQueue.h"
#include <queue>
#include "AlgorithmStrategy.h"
#include "AStarStrategy.h"
#include "DFSStrategy.h"
#include "BFSStrategy.h"
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

bool Solver::algorithm(Cube cube, DataStructure &structure, std::vector<short> &path, int *num_tries, Node *root, AlgorithmStrategy &strategy)
{
    unordered_set<Cube> visited;
    auto start = high_resolution_clock::now();
    int i = 0;

    structure.insert(root);
    visited.insert(root->cube);

    while (!structure.isEmpty())
    {
        Node *state = structure.remove();

        if (strategy.poda(state))
        {
            continue;
        }

        if (is_final_state(state, path, i, num_tries))
            return true;

        for (const auto &moviment : state->cube.moviments)
        {
            strategy.sucessora(state, moviment, structure, visited);
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
    Queue queue_structure;
    BFSStrategy strategy;
    Node *root = new Node{cube, nullptr, -1};
    cout << "Iniciando BFS..." << endl;
    return algorithm(cube, queue_structure, path, num_tries, root, strategy);
}

bool Solver::dfs(Cube cube, std::vector<short int> &path, int *num_tries)
{
    Stack stack_structure;
    BFSStrategy strategy;
    Node *root = new Node{cube, nullptr, -1};
    cout << "Iniciando DFS..." << endl;
    return algorithm(cube, stack_structure, path, num_tries, root, strategy);
}

bool Solver::A_star(Cube cube, std::vector<short int> &path, int *num_tries)
{
    AStarStrategy strategy;

    int g_start = 0;
    int h_start = Hasher::get_distance(cube);
    if (h_start == -1)
    {
        cout << "erro" << endl;
        return false;
    }

    strategy.g_costs[cube] = g_start;

    PriorityQueue priorityQueue;

    AstarNode *root = new AstarNode{cube, nullptr, -1, g_start, g_start + h_start};
    cout << "Iniciando DFS..." << endl;
    return algorithm(cube, priorityQueue, path, num_tries, root, strategy);
}
