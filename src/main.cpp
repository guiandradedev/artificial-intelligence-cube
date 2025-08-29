#include "Cube.h"
#include <iostream>
#include <random>
#include "Move.h"
#include "Solver.h"

using namespace std;


int main() {
    srand(time(NULL));
    Cube cubo;
    cubo.init();
    cubo.print();
    cout << "" << endl;

    // cubo.position(0,0,0).print();
    // cubo.position(1,0,0).print();

    Cube newCube = cubo.cloneMatrix();
    // newCube = Move::U_BW(newCube);

    // cout << "" << endl;
    // newCube.print();
    // cout << "" << endl;

    // // newCube = newCube.R();

    // // cout << "" << endl;
    // // newCube.print();
    // // cout << "" << endl;

    // cubo.print();

    Cube shuffledCube = cubo.shuffle(1);
    shuffledCube.print();

    Solver::bfs(shuffledCube);

    shuffledCube.print();

 
    return 0;
}
