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
#include "Hasher.h"
using namespace std::chrono;

using namespace std;

Solver::Solver()
{
    final_state.init();
    Hasher::init("./src/hashing.bin");
}

bool Solver::is_final_state(Node *current_state, std::vector<short int> &path, int i, int *num_tries)
{
    if (current_state->cube == final_state)
    {


        *num_tries = i;

        while (current_state->root != nullptr)
        {
            path.push_back(current_state->mov);
            current_state = current_state->root;
        }

        reverse(path.begin(), path.end());

        return true;
    }
    return false;
}

void Solver::cleanup_memory(std::vector<Node*>& all_nodes, DataStructure* structure) {
    delete structure; 
    for (Node* node : all_nodes) {
        delete node; 
    }
}


bool Solver::algorithm(AlgorithmStrategy &strategy, Cube cube, std::vector<short> &path, int *num_tries)
{
    Node* root = strategy.create_root_node(cube);
    DataStructure* structure = strategy.create_data_structure();

    std::vector<Node*> all_nodes;
    all_nodes.push_back(root);

    unordered_set<Cube> visited;
    auto start = high_resolution_clock::now();
    int i = 0;

    structure->insert(root);
    int j = 0;
    visited.insert(root->cube);

    while (!structure->isEmpty())
    {
        Node *state = structure->remove();

        if (is_final_state(state, path, i, num_tries)) {
            cleanup_memory(all_nodes, structure);
            return true;
        }

        if (strategy.poda(state))
        {
            continue;
        }

        for (const auto &moviment : state->cube.moviments)
        {
            j++;
            strategy.sucessora(state, moviment, *structure, visited, all_nodes);
        }
        i++;
    }
    *num_tries = i;
    auto end = high_resolution_clock::now();
    cleanup_memory(all_nodes, structure);

    return false;
}

bool Solver::bfs(Cube cube, std::vector<short int> &path, int *num_tries)
{
    BFSStrategy strategy;
    return algorithm(strategy, cube, path, num_tries);
}

bool Solver::dfs(Cube cube, std::vector<short int> &path, int *num_tries)
{
    int strategy_max_depth = 14;
    *num_tries = 0;

    for(int max_depth = 1; max_depth <= strategy_max_depth; max_depth++) {
        DFSStrategy strategy;
        strategy.max_depth = max_depth;

        int iteration_tries = 0;
        if (algorithm(strategy, cube, path, &iteration_tries)) {
            *num_tries += iteration_tries;
            return true;
        }
        *num_tries += iteration_tries;

    }
    return false;
}

bool Solver::A_star(Cube cube, std::vector<short int> &path, int *num_tries, int noise)
{
    AStarStrategy strategy;
    strategy.setNoise(noise);
    return algorithm(strategy, cube, path, num_tries);
}
