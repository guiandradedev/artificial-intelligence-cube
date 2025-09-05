#include "Cube.h"
#include <iostream>
#include <random>
#include "Move.h"
#include "Solver.h"
#include "MiniCube.h"

using namespace std;

enum PositionFace {
    LEFT = 0,
    RIGHT = 1,
    MID = 2
};


// faceIndex: 0 = left, 1 = right, 2 = mid
int getFaceColor(const MiniCube& c, PositionFace face) {
    // converte o enum para int para calcular o índice rotacionado
    int faceIndex = static_cast<int>(face);

    // if(c.orientation )

    int rotatedIndex = (faceIndex + c.orientation) % 3;

    switch (rotatedIndex) {
        case 0: return c.left;
        case 1: return c.right;
        case 2: return c.mid;
    }
    return -1; // fallback
}


void print(Cube cube) {
int planner[8][6];
        // int x=0,y=0,z=0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            planner[i][j] = -1;
        }
    }

    // back
    planner[0][2] = getFaceColor(cube.matrix[0][0][1], PositionFace::LEFT);
    planner[0][3] = getFaceColor(cube.matrix[0][1][1], PositionFace::RIGHT);
    planner[1][2] = getFaceColor(cube.matrix[0][0][0], PositionFace::LEFT);
    planner[1][3] = getFaceColor(cube.matrix[0][1][0], PositionFace::RIGHT);
    
    // Top
    planner[2][2] = getFaceColor(cube.matrix[0][0][0], PositionFace::MID);
    planner[2][3] = getFaceColor(cube.matrix[0][1][0], PositionFace::MID);
    planner[3][2] = getFaceColor(cube.matrix[1][0][0], PositionFace::MID);
    planner[3][3] = getFaceColor(cube.matrix[1][1][0], PositionFace::MID);

    // FRONT
    planner[4][2] = getFaceColor(cube.matrix[1][0][0], PositionFace::RIGHT);
    planner[4][3] = getFaceColor(cube.matrix[1][1][0], PositionFace::LEFT);
    planner[5][2] = getFaceColor(cube.matrix[1][0][1], PositionFace::RIGHT);
    planner[5][3] = getFaceColor(cube.matrix[1][1][1], PositionFace::LEFT);
    
    // DOWN
    planner[6][2] = getFaceColor(cube.matrix[1][0][1], PositionFace::MID);
    planner[6][3] = getFaceColor(cube.matrix[1][1][1], PositionFace::MID);
    planner[7][2] = getFaceColor(cube.matrix[0][0][1], PositionFace::MID);
    planner[7][3] = getFaceColor(cube.matrix[0][1][1], PositionFace::MID);
    
    // Left
    planner[2][0] = getFaceColor(cube.matrix[0][0][1], PositionFace::RIGHT);
    planner[2][1] = getFaceColor(cube.matrix[0][0][0], PositionFace::RIGHT);
    planner[3][0] = getFaceColor(cube.matrix[1][0][1], PositionFace::LEFT);
    planner[3][1] = getFaceColor(cube.matrix[1][0][0], PositionFace::LEFT);
    
    planner[2][4] = getFaceColor(cube.matrix[0][1][0], PositionFace::LEFT);
    planner[2][5] = getFaceColor(cube.matrix[0][1][1], PositionFace::LEFT);
    planner[3][4] = getFaceColor(cube.matrix[1][1][0], PositionFace::RIGHT);
    planner[3][5] = getFaceColor(cube.matrix[1][1][1], PositionFace::RIGHT);

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

    // print(cubo);
    

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
    // Cube shuffledCube = cubo.cloneMatrix();
    // shuffledCube = Move::L_BW(shuffledCube);
    // shuffledCube.print();
    // print(shuffledCube);

    cout << "LFW" << endl;

    Cube LFW = Move::L_BW(cubo);
    // print(LFW);
    LFW.print();

    cout << "FFW" << endl;
    Cube FFW = Move::F_FW(LFW);
    // print(FFW);
    FFW.print();

    // cout << "UFW" << endl;
    // Cube UFW = Move::U_BW(FFW);
    // print(UFW);
    // UFW.print();


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
    // shuffledCube = Move::BshuffledCube);
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
