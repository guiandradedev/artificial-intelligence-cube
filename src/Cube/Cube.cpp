#include <map>
#include <array>
#include <string>
#include <vector>
#include <functional>
#include <cstring>
#include "Solver.h"
#include "Cube/Move.h"
#include "Cube/Cube.h"
using namespace std;

Cube::Cube() {}

void Cube::init()
{

    int colors[8][3] = {
        {4, 2, 0}, // manteu
        {2, 4, 1}, // manteu
        {3, 4, 0}, // manteu
        {4, 3, 1}, // manteu
        {2, 5, 0},
        {5, 2, 1},
        {5, 3, 0},
        {3, 5, 1}
    };
    // 0 amarelo
    // 1 branco
    // 2 azul
    // 3 verde
    // 4 laranja
    // 5 vermelho

    // Loop que insere as cores na matriz
    int index = 1;
    for (int x = 0; x < 2; ++x)
    {
        for (int y = 0; y < 2; ++y)
        {
            for (int z = 0; z < 2; ++z)
            {
                int index = x * 4 + y * 2 + z;
                matrix[x][y][z] = MiniCube(colors[index][0], colors[index][1], colors[index][2], 0, index);
            }
        }
    }
}

void Cube::print() const
{
    for (int x = 0; x < 2; ++x)
    {
        for (int y = 0; y < 2; ++y)
        {
            for (int z = 0; z < 2; ++z)
            {
                const MiniCube &cube = matrix[x][y][z];
                std::cout 
                        //   << cube.name << " "
                          << "Cubinho" << cube.index << " (" 
                          << x << " " << y << " " << z << ") "
                          << cube.left << " "
                          << cube.right << " "
                          << cube.mid << " "
                          << cube.orientation << std::endl;
            }
        }
    }
}

Cube Cube::cloneMatrix() const {
    Cube newCube;

    // Para cada posição da matriz realiza a funcão clone do cubinho, que é basicamente a criação de uma nova instância dele
    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
            for (int z = 0; z < 2; ++z) {
                newCube.matrix[x][y][z] = this->matrix[x][y][z].clone();
            }
        }
    }

    return newCube;
}


static const std::vector<std::function<Cube(const Cube&)>> movefunctios = {
    Move::U_FW, // 0
    Move::U_BW, // 1
    Move::L_FW, // 2
    Move::L_BW, // 3
    Move::F_FW, // 4
    Move::F_BW  // 5
}; 

Cube Cube::applyMove(short int mov) const {
    return movefunctios[mov](*this);
}

Cube Cube::shuffle(int moves, bool print) const {
    Cube newCube = *this;
    int functions_possible = 6;

    if(print) {
        cout << "Movimentos: " << endl;
    }
    short int last_move = -1;

    for (int i = 0; i < moves; i++) {
        int functionIndex = rand() % functions_possible;

        if(Move::isInverse(functionIndex, last_move)){
            i--;
            continue;
        }
        last_move = functionIndex;

        newCube = newCube.applyMove(moviments[functionIndex]);

        if(print) {
            cout << Solver::moviments_name[functionIndex] << " - ";
        }
    }
    cout << endl;

    return newCube;
}