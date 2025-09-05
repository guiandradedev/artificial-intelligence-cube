#include "Solver.h"
#include "Cube.h"
#include <queue>
#include <stack>
#include "Move.h"
#include <set>
#include <iostream>
#include <unordered_set>
#include <chrono>
#include <cstring>
#include "DataStructure.h"
#include "Queue.h"
#include "Stack.h"

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

void Solver::algorithm(Cube cube, DataStructure& structure) {
    unordered_set<Cube> visited;
    auto start = high_resolution_clock::now();
    int i=0;

    Node* root = new Node{cube, nullptr, ""}; 
    Node* final_move;
    structure.insert(root);
    visited.insert(root->cube);
    
    while(!structure.isEmpty()) {
        Node* state = structure.remove();

        if(state->cube == final_state) {
            cout << "Solucao encontrada na " << i << " iteracao!" << endl;
            final_move = state;
            break;
        }

        for(const auto& moviment : cube.moviments) {
            // Se for inverso do anterior, pula pro proximo
            if(strcmp(Move::reverse_moves(moviment), state->mov) == 0) continue;

            Cube next_cube = state->cube.applyMove(moviment);
            
            if (visited.count(next_cube) == 0) {
                visited.insert(next_cube);
                
                Node* next_node = new Node{next_cube, state, {}}; 
                strcpy(next_node->mov, moviment);
                
                structure.insert(next_node);
            }
        }
        i++;
    }
    auto end = high_resolution_clock::now();
    cout << "Tempo BFS: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    cout << "Reconstrucao do cubo:" << endl;
    int moves = 0;
    while(final_move->root != nullptr) {
        cout << final_move->mov << endl;
        final_move = final_move->root;
        moves++;
    }
    cout << final_move->mov << endl;
    cout << "Com um total de " << moves << " movimentos." << endl;
}

void Solver::bfs(Cube cube) {
    Queue queue_structure;
    cout << "Iniciando BFS..." << endl;
    algorithm(cube, queue_structure);
}

void Solver::dfs(Cube cube) {
    Stack stack_structure;
    cout << "Iniciando DFS..." << endl;
    algorithm(cube, stack_structure);
}