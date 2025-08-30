#include "Cube.h"
#include <map>
#include <array>
#include <string>
#include <vector>
#include "Move.h"
#include <cstring>
using namespace std;

Cube::Cube() {}

void Cube::init()
{

    int colors[8][3] = {
        {4, 2, 0},
        {4, 2, 1},
        {3, 4, 0},
        {3, 4, 1},
        {2, 5, 0},
        {2, 5, 1},
        {5, 3, 0},
        {5, 3, 1}
    };

    // Loop que insere as cores na matriz
    for (int x = 0; x < 2; ++x)
    {
        for (int y = 0; y < 2; ++y)
        {
            for (int z = 0; z < 2; ++z)
            {
                int index = x * 4 + y * 2 + z;
                matrix[x][y][z] = MiniCube(colors[index][0], colors[index][1], colors[index][2], 0);

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
                std::cout << x << " " << y << " " << z << " "
                        //   << cube.name << " "
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

const char moviments[6][4] = { "UFW", "UBW", "LFW", "LBW", "FBW", "FFW" };

Cube Cube::applyMove(const char mov[4]) const {
    cout << mov << endl;
    if (strcmp(mov, "UFW") == 0) return Move::U_FW(*this);
    if (strcmp(mov, "UBW") == 0) return Move::U_BW(*this);
    if (strcmp(mov, "LFW") == 0) return Move::L_FW(*this);
    if (strcmp(mov, "LBW") == 0) return Move::L_BW(*this);
    if (strcmp(mov, "FBW") == 0) return Move::F_BW(*this);
    if (strcmp(mov, "FFW") == 0) return Move::F_FW(*this);

    return *this;
}

Cube Cube::shuffle(int moves) const {
    Cube newCube = *this;
    int functions_possible = 6;

    for (int i = 0; i < moves; i++) {
        int functionIndex = rand() % functions_possible;
        newCube = newCube.applyMove(moviments[functionIndex]);
    }

    return newCube;
}

MiniCube Cube::position(int x, int y, int z) {
    return matrix[x][y][z];
}