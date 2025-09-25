#include "Cube/Cube.h"
#include <iostream>
#include <random>
#include "Cube/Move.h"
#include "Solver.h"
#include "Cube/MiniCube.h"
#include "Hasher.h"
#include "vector"
#include "Node/Node.h"

using namespace std;

int main() {

    srand(time(NULL));
    Cube cubo;
    cubo.init();
    cubo.print();
    cout << "" << endl;
    Hasher::init("./src/hashing.bin");
    
    cubo = cubo.shuffle(10, true);
    std::vector<short int> path;
    int num_tries;

    
    Solver solver;
    
    solver.dfs(cubo, path, &num_tries);

    return 0;
}
