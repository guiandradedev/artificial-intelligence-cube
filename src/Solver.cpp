#include "headers/Solver.h"
#include "headers/Cube.h"
#include <queue>
#include <stack>
#include "headers/Move.h"
#include <set>
#include <iostream>
#include <unordered_set>
#include <chrono>
#include <cstring>
#include "headers/DataStructure.h"
#include "headers/Queue.h"
#include "headers/Stack.h"


using namespace std::chrono;
namespace std {
    template<>
    struct hash<Cube> {
        size_t operator()(const Cube& c) const {
            size_t h = 0;
            for (int x = 0; x < 2; ++x) {
                for (int y = 0; y < 2; ++y) {
                    for (int z = 0; z < 2; ++z) {
                        const MiniCube& m = c.matrix[x][y][z];
                        h ^= std::hash<int>{}(m.left) + 0x9e3779b9 + (h << 6) + (h >> 2);
                        h ^= std::hash<int>{}(m.right) + 0x9e3779b9 + (h << 6) + (h >> 2);
                        h ^= std::hash<int>{}(m.mid) + 0x9e3779b9 + (h << 6) + (h >> 2);
                        h ^= std::hash<short>{}(m.orientation) + 0x9e3779b9 + (h << 6) + (h >> 2);
                    }
                }
            }
            return h;
        }
    };
}

using namespace std;

// Todo:
// Implement visited hash

Solver::Solver() {
    final_state.init();
}

void Solver::algorithm(Cube cube, DataStructure& structure, int max_depth) {

    unordered_set<Cube> visited;
    auto start = high_resolution_clock::now();
    int i=0;

    Node* root = new Node{cube, nullptr, {},0}; 
    Node* final_move = nullptr;
    structure.insert(root);
    visited.insert(root->cube);
    
    while(!structure.isEmpty() && final_move == nullptr) {
        Node* state = structure.remove();

        if(state->cube == final_state) {
            cout << "Solucao encontrada na " << i << " iteracao!" << endl;
            final_move = state;
            break;
        }

        for(const auto& moviment : state->cube.moviments) {
            // if(strcmp(Move::reverse_moves(moviment), state->mov) == 0) continue;
            
            // std::cout << "Movimento: " << moviment << " na iteracao " << i << endl;
            
            // Se for inverso do anterior, pula pro proximo
            if(Move::isInverse(moviment, state->mov)){
                continue;
            }

            Cube next_cube = state->cube.applyMove(moviment);
            
            if (visited.count(next_cube) == 0) {
                visited.insert(next_cube);
                
                if(max_depth >= 0){
                    if(state->depth == 13){
                        cout << "\nBOMBAA!\n";
                    }
                    cout << state->depth;
                }

                if (max_depth >= 0 && state->depth > max_depth) {
                    continue; 
                }

                Node* next_node = new Node{next_cube, state, moviment,state->depth+1};
                
                structure.insert(next_node);
            }
        }
        i++;
    }
    auto end = high_resolution_clock::now();
    cout << "Tempo de execução do algoritmo: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    if (final_move == nullptr) {
        cout << "Nenhuma solução encontrada até a profundidade " << max_depth << endl;
        return;
    }

    cout << "Reconstrucao do cubo:" << endl;
    int moves = 0;
    while(final_move->root != nullptr) {
        cout << moviments_name[final_move->mov] << endl;
        final_move = final_move->root;
        moves++;
    }
    
    cout << "Com um total de " << moves << " movimentos." << endl;
}

void Solver::bfs(Cube cube) {
    Queue queue_structure;
    cout << "Iniciando BFS..." << endl;
    algorithm(cube, queue_structure, -1);
}

void Solver::dfs(Cube cube) { 
    Stack stack_structure;
    cout << "Iniciando DFS..." << endl;
    algorithm(cube, stack_structure, 12);
}