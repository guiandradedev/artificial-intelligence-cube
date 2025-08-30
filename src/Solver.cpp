#include "Solver.h"
#include "Cube.h"
#include <queue>
#include <stack>
#include "Move.h"
#include <set>
#include <iostream>

using namespace std;

// Todo:
// Implement visited hash

Solver::Solver() {
    final_state.init();
}

// void algorithm(Data& data) {

// }

void Solver::bfs(Cube cube) {
    queue<Cube> cube_queue;
    // set<Cube> visited;
    cube_queue.push(cube);
    int i=0;
    while(!cube_queue.empty()) {
        Cube state = cube_queue.front();
        cube_queue.pop();

        if(state.is_final_state(final_state)) {
            cout << "Funcionou na " << i << " iteração" << endl;
            break;
        }

        // visited.insert(state);

        i++;
        cube_queue.push(Move::U_FW(state));
        cube_queue.push(Move::U_BW(state));
        cube_queue.push(Move::L_FW(state));
        cube_queue.push(Move::L_BW(state));
        cube_queue.push(Move::F_FW(state));
        cube_queue.push(Move::F_BW(state));

    }
}

void Solver::dfs(Cube cube) {
    stack<Cube> cube_stack;
    // set<Cube> visited;
    cube_stack.push(cube);
    int i=0;
    while(!cube_stack.empty()) {
        Cube state = cube_stack.top();
        cube_stack.pop();

        if(state.is_final_state(final_state)) {
            cout << "Funcionou na " << i << " iteração" << endl;
            break;
        }

        if(i % 1000 == 0) {
            cout << i << endl;
        }

        // visited.insert(state);

        i++;
        cube_stack.push(Move::U_FW(state));
        cube_stack.push(Move::U_BW(state));
        cube_stack.push(Move::L_FW(state));
        cube_stack.push(Move::L_BW(state));
        cube_stack.push(Move::F_FW(state));
        cube_stack.push(Move::F_BW(state));

    }
}