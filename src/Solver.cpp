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

using namespace std::chrono;

using namespace std;

// Todo:
// Implement visited hash

Solver::Solver()
{
    final_state.init();
}

bool Solver::algorithm(Cube cube, DataStructure &structure, std::vector<short int> &path, int *num_tries)
{
    unordered_set<Cube> visited;
    auto start = high_resolution_clock::now();
    int i = 0;

    Node *root = new Node{cube, nullptr, -1};
    Node *final_move;
    structure.insert(root);
    visited.insert(root->cube);

    while (!structure.isEmpty())
    {
        Node *state = structure.remove();

        if (state->cube == final_state)
        {
            cout << "Solucao encontrada na " << i << " iteracao!" << endl;
            final_move = state;

            *num_tries = i;

            cout << "Reconstrucao do cubo:" << endl;
            int moves = 0;
            while (final_move->root != nullptr)
            {
                cout << moviments_name[final_move->mov] << endl;
                path.push_back(final_move->mov);
                final_move = final_move->root;
                moves++;
            }

            cout << "Com um total de " << moves << " movimentos." << endl;

            reverse(path.begin(), path.end());

            return true;
            // break;
        }

        for (const auto &moviment : cube.moviments)
        {
            // if(strcmp(Move::reverse_moves(moviment), state->mov) == 0) continue;

            // std::cout << "Movimento: " << moviment << " na iteracao " << i << endl;

            // Se for inverso do anterior, pula pro proximo
            if (Move::isInverse(moviment, state->mov))
                continue;

            if (state->root && state->root->mov == moviment && state->mov == moviment)
                continue;

            if (state->mov == moviment && (moviment == 1 || moviment == 3 || moviment == 5))
                continue;

            Cube next_cube = state->cube.applyMove(moviment);

            if (visited.count(next_cube) == 0)
            {
                visited.insert(next_cube);

                Node *next_node = new Node{next_cube, state, moviment};

                structure.insert(next_node);
            }
        }
        i++;
    }
    *num_tries = i;
    auto end = high_resolution_clock::now();
    cout << "Tempo BFS: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    return false;
}

bool Solver::bfs(Cube cube, std::vector<short int> &path, int *num_tries)
{
    Queue queue_structure;
    cout << "Iniciando BFS..." << endl;
    return algorithm(cube, queue_structure, path, num_tries);
}

bool Solver::dfs(Cube cube, std::vector<short int> &path, int *num_tries)
{
    Stack stack_structure;
    cout << "Iniciando DFS..." << endl;
    return algorithm(cube, stack_structure, path, num_tries);
}

bool Solver::A_star(Cube cube, std::vector<short int> &path, int *num_tries)
{
    auto start = high_resolution_clock::now();
    cout << "Iniciando A*: " << endl;

    PriorityQueue priorityQueue;
    // priority_queue<AstarNode, vector<AstarNode>, greater<AstarNode>> queue;
    // priority_queue<AstarNode, vector<AstarNode>, greater<AstarNode>> queue;

    unordered_map<Cube, pair<Cube, short int>> predecessors;
    unordered_map<Cube, int> g_costs;

    int g_start = 0;
    int h_start = Hasher::get_distance(cube) + rand() % 4;
    if (h_start == -1)
    {
        cout << "erro" << endl;
        return false;
    }

    AstarNode *root = new AstarNode{cube, nullptr, -1, g_start, g_start + h_start};
    // AstarNode root{cube, g_start, g_start + h_start};

    priorityQueue.insert(root);
    // queue.push({cube, g_start, g_start + h_start});
    g_costs[cube] = g_start;
    predecessors[cube] = {cube, -1};

    Node *final_node = nullptr;
    int iterations = 0;
    while (!priorityQueue.isEmpty())
    {
        AstarNode *current_node = priorityQueue.remove();

        // AstarNode *current_node = queue.top();
        // queue.pop();
        iterations++;

        if (current_node->g_cost > g_costs[current_node->cube])
        {
            continue;
        }

        if (current_node->cube == final_state)
        {
            Cube at = final_state;
            while (!(at == cube))
            {
                auto pred_info = predecessors.at(at);
                path.push_back(pred_info.second);
                at = pred_info.first;
            }

            reverse(path.begin(), path.end());

            auto end = high_resolution_clock::now();
            cout << "Tempo A*: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
            cout << "Solucao (" << path.size() << " movimentos): ";

            for (short int move : path)
            {
                cout << moviments_name[move] << " ";
            }
            cout << endl;

            *num_tries = predecessors.size();

            return true;
        }

        for (const auto &moviment : cube.moviments)
        {
            if (predecessors.count(current_node->cube) && Move::isInverse(moviment, predecessors[current_node->cube].second))
            {
                continue;
            }

            Cube next_cube = current_node->cube.applyMove(moviment);
            int new_g_cost = current_node->g_cost + 1;

            if (g_costs.find(next_cube) == g_costs.end() || new_g_cost < g_costs[next_cube])
            {
                g_costs[next_cube] = new_g_cost;
                predecessors[next_cube] = {current_node->cube, moviment};

                int h_cost = Hasher::get_distance(next_cube) + rand() % 4;
                int f_cost = new_g_cost + h_cost;

                priorityQueue.insert(new AstarNode{next_cube, current_node, moviment, new_g_cost, f_cost});
            }
        }
    }
    return false;
}
