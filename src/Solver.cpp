#include "Solver.h"
#include "Cube.h"
#include <queue>
#include <stack>
#include "Move.h"
#include <set>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <chrono>
#include <algorithm>
#include <functional>
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

// void Solver::bfs(Cube cube) {
//     queue<Cube> cube_queue;
//     unordered_set<Cube> visited;
//     // set<Cube> visited;
//     auto start = high_resolution_clock::now();
//     cube_queue.push(cube);
//     int i=0;
//     while(!cube_queue.empty()) {
//         Cube state = cube_queue.front();
//         cube_queue.pop();

//         if (visited.count(state) > 0) continue;
//         visited.insert(state);

//         if(state == final_state) {
//             cout << "Funcionou na " << i << " iteração" << endl;
//             break;
//         }

//         // visited.insert(state);

//         i++;
//         cube_queue.push(Move::U_FW(state));
//         cube_queue.push(Move::U_BW(state));
//         cube_queue.push(Move::L_FW(state));
//         cube_queue.push(Move::L_BW(state));
//         cube_queue.push(Move::F_FW(state));
//         cube_queue.push(Move::F_BW(state));

//     }
//         auto end = high_resolution_clock::now();
//     cout << "Tempo BFS: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
// }

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

        // if(i % 1000 == 0) {
        //     cout << i << endl;
        // }

        // visited.insert(state);

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

vector<const char*> reconstruct_path(
    const unordered_map<Cube, pair<Cube, const char*>>& came_from,
    const Cube& initial,
    const Cube& final_state
){
    vector<const char*> path;
    Cube current = final_state;

    while (!(current == initial)) {
        auto const& pred_info = came_from.at(current);
        const char* move = pred_info.second;
        path.push_back(move);
        current = pred_info.first;
    }

    reverse(path.begin(), path.end());
    return path;
} 

void Solver::bfs(Cube initial_state){
    queue<Cube> cube_queue;
    unordered_set<Cube> visited;
    unordered_map<Cube, pair<Cube, const char*>> came_from;


    auto start = high_resolution_clock::now();

    cube_queue.push(initial_state);
    visited.insert(initial_state);

    int iterations = 0;

    while (!cube_queue.empty()){
        Cube current_state = cube_queue.front();
        cube_queue.pop();
        iterations++;

        if (current_state == final_state){
            auto end = high_resolution_clock::now();
            cout << "Solucao encontrada em " << iterations << " iterações." << endl;
            cout << "Tempo BFS: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

            vector<const char*> path = reconstruct_path(came_from, initial_state, final_state);
            cout << "Caminho " << path.size() << " movimentos.";

            for (const char* move : path){
                cout << move << " ";
            }
            cout << endl;
            return;
        }

        const pair<const char*, function<Cube(const Cube&)>> moves[] = {
            {"U_FW", Move::U_FW},
            {"U_BW", Move::U_BW},
            {"L_FW", Move::L_FW},
            {"L_BW", Move::L_BW},
            {"F_FW", Move::F_FW},
            {"F_BW", Move::F_BW}
        };

        for (const auto& move_pair : moves) {
            Cube next_state = move_pair.second(current_state);

            if (visited.count(next_state) == 0) {
                visited.insert(next_state);
                cube_queue.push(next_state);
                came_from[next_state] = {current_state, move_pair.first};
            }
        }
    }

    auto end = high_resolution_clock::now();
    cout << "Nenhuma solução encontrada em " << iterations << " iterações." <<
        " Tempo BFS: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
}