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

// void algorithm(Data& data) {

// }

void Solver::bfs(Cube cube) {
    queue<Node*> cube_queue;
    unordered_set<Cube> visited;
    auto start = high_resolution_clock::now();
    int i=0;

    Node* root = new Node{cube, nullptr, ""}; 
    Node* final_move;
    cube_queue.push(root);
    visited.insert(root->cube);
    
    while(!cube_queue.empty()) {
        Node* state = cube_queue.front();
        cube_queue.pop();

        if(state->cube == final_state) {
            final_state.print();
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
                
                cube_queue.push(next_node);
            }
        }
        i++;
    }
    auto end = high_resolution_clock::now();
    cout << "Tempo BFS: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    cout << "Reconstrucao do cubo:" << endl;
    int moves = 0;
    final_move->cube.print();
    while(final_move->root != nullptr) {
        cout << final_move->mov << endl;
        final_move = final_move->root;
        moves++;
    }
    cout << final_move->mov << endl;
    cout << "Com um total de " << moves << " movimentos." << endl;
}

void Solver::dfs(Cube cube) {
    stack<Cube> cube_stack;
    // set<Cube> visited;
    unordered_set<Cube> visited;
    cube_stack.push(cube);
    int i=0;
    auto start = high_resolution_clock::now();
    while(!cube_stack.empty()) {
        Cube state = cube_stack.top();
        cube_stack.pop();

        if (visited.count(state) > 0) continue;
        visited.insert(state);

        if(state == final_state) {
            cout << "Funcionou na " << i << " iteração" << endl;
            break;
        }

        i++;
        cube_stack.push(Move::U_FW(state));
        cube_stack.push(Move::U_BW(state));
        cube_stack.push(Move::L_FW(state));
        cube_stack.push(Move::L_BW(state));
        cube_stack.push(Move::F_FW(state));
        cube_stack.push(Move::F_BW(state));

    }
    auto end = high_resolution_clock::now();
    cout << "Tempo DFS: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
}