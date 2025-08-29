#include "Solver.h"
#include "Cube.h"
#include <queue>
#include "Move.h"
#include <set>
#include <iostream>

using namespace std;

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