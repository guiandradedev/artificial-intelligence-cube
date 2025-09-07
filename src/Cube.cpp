#include "Cube.h"
#include <map>
#include <array>
#include <string>
#include <vector>
#include <functional>
#include "Move.h"
#include <cstring>
#include <Solver.h>
using namespace std;

Cube::Cube() {}

void Cube::init()
{

    int colors[8][3] = {
        {4, 2, 0}, // manteu
        {4, 2, 1}, // manteu
        {3, 4, 0}, // manteu
        {3, 4, 1}, // manteu
        {2, 5, 0},
        {2, 5, 1},
        {5, 3, 0},
        {5, 3, 1}
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

                // char name[4];
                // snprintf(name, sizeof(name), "%d%d%d", x, y, z);
                
                // matrix[x][y][z] = MiniCube(name, colors[index][0], colors[index][1], colors[index][2], 0);
            
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

// Cube Cube::applyMove(const char mov[4]) const {
//     // TODO Adicionar hash
//     if (strcmp(mov, "UFW") == 0) return Move::U_FW(*this);
//     if (strcmp(mov, "UBW") == 0) return Move::U_BW(*this);
//     if (strcmp(mov, "LFW") == 0) return Move::L_FW(*this);
//     if (strcmp(mov, "LBW") == 0) return Move::L_BW(*this);
//     if (strcmp(mov, "FBW") == 0) return Move::F_BW(*this);
//     if (strcmp(mov, "FFW") == 0) return Move::F_FW(*this);

//     return *this;
// }

//     UFW = 0, UBW = 1,
//     LFW = 2, LBW = 3,
//     FFW = 4, FBW = 5

static const std::vector<std::function<Cube(const Cube&)>> movefunctios = {
    Move::U_FW, // 0
    Move::U_BW, // 1
    Move::L_FW, // 2
    Move::L_BW, // 3
    Move::F_FW, // 4
    Move::F_BW  // 5
}; 

Cube Cube::applyMove(short int mov) const {
    // // TODO Adicionar hash
    // if (mov == 0) return Move::U_FW(*this);
    // if (mov == 1) return Move::U_BW(*this);
    // if (mov == 2) return Move::L_FW(*this);
    // if (mov == 3) return Move::L_BW(*this);
    // if (mov == 4) return Move::F_FW(*this);
    // if (mov == 5) return Move::F_BW(*this);

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
            std::cout << "pulei" << std::endl;
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

MiniCube Cube::position(int x, int y, int z) {
    return matrix[x][y][z];
}