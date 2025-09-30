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
        // cout << "Solucao encontrada na " << i << " iteracao!" << endl;

        *num_tries = i;

        // cout << "Reconstrucao do cubo:" << endl;
        // int moves = 0;
        while (current_state->root != nullptr)
        {
            // cout << moviments_name[current_state->mov] << endl;
            path.push_back(current_state->mov);
            current_state = current_state->root;
            // moves++;
        }

        // cout << "Com um total de " << moves << " movimentos." << endl;

        reverse(path.begin(), path.end());

        return true;
        // break;
    }
    return false;
}

void Solver::cleanup_memory(std::vector<Node*>& all_nodes, DataStructure* structure) {
    // cout << "Limpando memoria... " << all_nodes.size() << " nos e a estrutura de dados." << endl;
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
    int i =-1;

    structure->insert(root);
    int j = 0;
    visited.insert(root->cube);

    while (!structure->isEmpty())
    {
        
        i++;
        std::cout << "\nLINHA:" << i;
        
        Node *state = structure->remove();

        if (is_final_state(state, path, i, num_tries)) {
            cleanup_memory(all_nodes, structure);
            std::cout << "\nLinha estado final " << i << endl;
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

    }
    // cout << "Linha " << j << endl;

    if(structure->isEmpty())
    {
        std::cout<<"\nESVAZIOU A ESTRUTURA!";
    }

    std::cout<<"\nchegou";

    *num_tries = i;
    auto end = high_resolution_clock::now();
    // cout << "Tempo Execução: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
    cleanup_memory(all_nodes, structure);

    return false;
}

bool Solver::bfs(Cube cube, std::vector<short int> &path, int *num_tries)
{
    BFSStrategy strategy;
    // cout << "Iniciando BFS..." << endl;
    return algorithm(strategy, cube, path, num_tries);
}

bool Solver::dfs(Cube cube, std::vector<short int> &path, int *num_tries)
{
   int max_search_depth = 20; // Limite para não ficar em loop infinito
    *num_tries = 0;
    std::cout << "Iniciando DFS com Aprofundamento Iterativo..." << std::endl;

    // Este loop é a implementação do IDDFS
    for (int current_max_depth = 1; current_max_depth <= max_search_depth; current_max_depth++)
    {
        std::cout << "\nTentando com profundidade maxima: " << current_max_depth;
        
        // A estratégia é recriada a cada iteração, resetando a busca
        DFSStrategy strategy;
        strategy.max_depth = current_max_depth;
        
        int iteration_tries = 0;

        // Chama o algoritmo para a profundidade atual
        if (algorithm(strategy, cube, path, &iteration_tries)) {
            *num_tries += iteration_tries;
            std::cout << "\nSolucao encontrada na profundidade " << current_max_depth << "!" << std::endl;
            return true; // Encontrou? PARA TUDO e retorna a solução.
        }

        *num_tries += iteration_tries; // Acumula tentativas se não encontrou
    }

    std::cout << "\nSolucao nao encontrada dentro do limite de profundidade." << std::endl;
    return false;
}

bool Solver::A_star(Cube cube, std::vector<short int> &path, int *num_tries, int noise)
{
    AStarStrategy strategy;
    strategy.setNoise(noise);
    // cout << "Iniciando A*..." << endl;
    return algorithm(strategy, cube, path, num_tries);
}
