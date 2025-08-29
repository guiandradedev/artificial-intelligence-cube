#include "Cube.h"
#include <queue>
#include <iostream>
#include <random>
#include <set>
#include "Move.h"
// x - tras | frente
// y - esquerda | direita
// z - cima | baixo
using namespace std;

bool is_final_state(Cube cube, Cube original) {
    bool is_valid = true;

    for(int i=0; i<2 && is_valid; i++) {
        for(int j=0; j<2 && is_valid; j++) {
            for(int k=0; k<2 && is_valid; k++) {
                if(cube.matrix[i][j][k] != original.matrix[i][j][k]) {
                    is_valid = false;
                }
            }
        }
    }
    return is_valid;

}

int main() {
    Cube cubo;
    cubo.init();
    cubo.print();
    cout << "" << endl;

    // cubo.position(0,0,0).print();
    // cubo.position(1,0,0).print();

    Cube newCube = cubo.cloneMatrix();
    newCube = Move::U_BW(newCube);

    // cout << "" << endl;
    // newCube.print();
    // cout << "" << endl;

    // // newCube = newCube.R();

    // // cout << "" << endl;
    // // newCube.print();
    // // cout << "" << endl;

    // cubo.print();

    // Cube shuffledCube = cubo.shuffle(1);
    // shuffledCube.print();


    queue<Cube> cube_queue;
    // set<Cube> visited;
    cube_queue.push(newCube);
    int i=0;
    while(!cube_queue.empty()) {
        Cube state = cube_queue.front();
        cube_queue.pop();

        if(is_final_state(state, cubo)) {
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

    return 0;
}
