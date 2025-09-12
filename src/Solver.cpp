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

using namespace std::chrono;

using namespace std;

// Todo:
// Implement visited hash

Solver::Solver()
{
    final_state.init();
}

void Solver::algorithm(Cube cube, DataStructure &structure)
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
            break;
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
    auto end = high_resolution_clock::now();
    cout << "Tempo BFS: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    cout << "Reconstrucao do cubo:" << endl;
    int moves = 0;
    while (final_move->root != nullptr)
    {
        cout << moviments_name[final_move->mov] << endl;
        final_move = final_move->root;
        moves++;
    }

    cout << "Com um total de " << moves << " movimentos." << endl;
}

void Solver::bfs(Cube cube)
{
    Queue queue_structure;
    cout << "Iniciando BFS..." << endl;
    algorithm(cube, queue_structure);
}

void Solver::dfs(Cube cube)
{
    Stack stack_structure;
    cout << "Iniciando DFS..." << endl;
    algorithm(cube, stack_structure);
}

void Solver::A_star(Cube cube)
{
    cout << "Iniciando A*: " << endl;

    auto start = high_resolution_clock::now();

    priority_queue<AstarNode, vector<AstarNode>, greater<AstarNode>> queue;

    unordered_map<Cube, pair<Cube, short int>> predecessors;
    unordered_map<Cube, int> g_costs;

    int g_start = 0;
    int h_start = Hasher::get_distance(cube) + rand()%4 ;
    if (h_start == -1)
    {
        cout << "erro" << endl;
        return;
    }

    queue.push({cube, g_start, g_start + h_start});
    g_costs[cube] = g_start;
    predecessors[cube] = {cube, -1};

    Node* final_node = nullptr;
    int iterations = 0;

    while (!queue.empty())
    {
        AstarNode current_node = queue.top();

        queue.pop();
        iterations++;

        if(current_node.g_cost > g_costs[current_node.cube])
        {
            continue;
        }

        if (current_node.cube == final_state)
        {
            
            vector<short int> path;

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

            for(short int move : path) 
            {
                cout << moviments_name[move] << " ";
            }
            cout << endl;

            return;
        }
        
        for (const auto& moviment : cube.moviments)
        {
            if (predecessors.count(current_node.cube) && Move::isInverse(moviment, predecessors[current_node.cube].second))
            {
                continue;
            }

            Cube next_cube = current_node.cube.applyMove(moviment);
            int new_g_cost = current_node.g_cost +1;

            if (g_costs.find(next_cube) == g_costs.end() || new_g_cost < g_costs[next_cube]) {
                g_costs[next_cube] = new_g_cost;
                predecessors[next_cube] = {current_node.cube, moviment};
                
                int h_cost = Hasher::get_distance(next_cube) + rand()%4;
                int f_cost = new_g_cost + h_cost;
                
                queue.push({next_cube, new_g_cost, f_cost});
            }
        }
    }
    
}
