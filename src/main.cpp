#include "Cube.h"
#include <iostream>
#include <random>
#include "Move.h"
#include "Solver.h"
#include "MiniCube.h"

using namespace std;

void print(Cube cube) {
int planner[8][6];
        // int x=0,y=0,z=0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            planner[i][j] = -1;
        }
    }

    // back
    planner[0][2] = cube.matrix[0][0][1].left;
    planner[0][3] = cube.matrix[0][1][1].right;
    planner[1][2] = cube.matrix[0][0][0].left;
    planner[1][3] = cube.matrix[0][1][0].right;
    
    // Top
    planner[2][2] = cube.matrix[0][0][0].mid;
    planner[2][3] = cube.matrix[0][1][0].mid;
    planner[3][2] = cube.matrix[1][0][0].mid;
    planner[3][3] = cube.matrix[1][1][0].mid;

    // FRONT
    planner[4][2] = cube.matrix[1][0][0].right;
    planner[4][3] = cube.matrix[1][1][0].left;
    planner[5][2] = cube.matrix[1][0][1].right;
    planner[5][3] = cube.matrix[1][1][1].left;
    
    // DOWN
    planner[6][2] = cube.matrix[1][0][1].mid;
    planner[6][3] = cube.matrix[1][1][1].mid;
    planner[7][2] = cube.matrix[0][0][1].mid;
    planner[7][3] = cube.matrix[0][1][1].mid;
    
    // Left
    planner[2][0] = cube.matrix[0][0][1].right;
    planner[2][1] = cube.matrix[0][0][0].right;
    planner[3][0] = cube.matrix[1][0][1].left;
    planner[3][1] = cube.matrix[1][0][0].left;
    
    planner[2][4] = cube.matrix[0][1][0].left;
    planner[2][5] = cube.matrix[0][1][1].left;
    planner[3][4] = cube.matrix[1][1][0].right;
    planner[3][5] = cube.matrix[1][1][1].right;

    char colorMap[] = {'Y', 'W', 'B', 'G', 'O', 'R'}; 

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            if (planner[i][j] == -1) {
                cout << "  ";   // vazio
            } else {
                cout << colorMap[planner[i][j]] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    srand(time(NULL));
    Cube cubo;
    cubo.init();
    cubo.print();
    cout << "" << endl;

    print(cubo);
    

    // // cubo.position(0,0,0).print();
    // // cubo.position(1,0,0).print();

    // Cube newCube = cubo.cloneMatrix();
    // // newCube = Move::U_BW(newCube);

    // // cout << "" << endl;
    // // newCube.print();
    // // cout << "" << endl;

    // // // newCube = newCube.R();

    // // // cout << "" << endl;
    // // // newCube.print();
    // // // cout << "" << endl;

    // // cubo.print();

    // // Cube shuffledCube = cubo.shuffle(10);

    cout << "Movimento 1:" <<endl;
    Cube shuffledCube = cubo.cloneMatrix();
    shuffledCube = Move::L_BW(shuffledCube);
    shuffledCube.print();
    print(shuffledCube);

    cout << "UBW" << endl;
    print(Move::L_FW(cubo));
    // cout << endl;
    // shuffledCube = Move::L_BW(shuffledCube);
    // shuffledCube.print();
    // cout << endl;
    // shuffledCube = Move::U_FW(shuffledCube);
    // shuffledCube.print();
    // cout << endl;
    // shuffledCube = Move::F_BW(shuffledCube);
    // shuffledCube.print();
    // cout << endl;
    // shuffledCube = Move::L_FW(shuffledCube);
    // shuffledCube.print();
    // cout << endl;
    // shuffledCube = Move::U_FW(shuffledCube);
    // shuffledCube.print();
    // cout << endl;

    // Solver solver;
    // // solver.final_state.print();

    // solver.bfs(shuffledCube);
    // // solver.dfs(shuffledCube);

    return 0;
}
