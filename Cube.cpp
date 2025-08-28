#include "Cube.h"
#include <map>
#include <array>
#include <string>
#include <vector>

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

// Movimentações possíveis (que geram novos estado//novas instâncias do cubo)

// Observações
// Foward (FW): sentido horario
// Backward (BW): sentido anti horario

// x - tras | frente
// y - esquerda | direita
// z - cima | baixo


// rotate the upper face Fowards
Cube Cube::U_FW() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[0][0][0];
    newCube.matrix[0][0][0] = newCube.matrix[1][0][0];
    newCube.matrix[1][0][0] = newCube.matrix[1][1][0];
    newCube.matrix[1][1][0] = newCube.matrix[0][1][0];
    newCube.matrix[0][1][0] = temp;

    return newCube;
}

// rotate the upper face backwards
Cube Cube::U_BW() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[1][0][0];
    newCube.matrix[1][0][0] = newCube.matrix[0][0][0];
    newCube.matrix[0][0][0] = newCube.matrix[0][1][0];
    newCube.matrix[0][1][0] = newCube.matrix[0][1][1];
    newCube.matrix[0][1][1] = temp;

    return newCube;
}

// rotate the left face forwards
Cube Cube::L_FW() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[0][0][0];
    newCube.matrix[0][0][0] = newCube.matrix[0][0][1];
    newCube.matrix[0][0][1] = newCube.matrix[1][0][1];
    newCube.matrix[1][0][1] = newCube.matrix[1][0][0];
    newCube.matrix[1][0][0] = temp;

    newCube.matrix[0][0][0].orientation = (newCube.matrix[0][0][0].orientation + 1) % 3;
    newCube.matrix[0][0][1].orientation = (newCube.matrix[0][0][1].orientation + 2) % 3;
    newCube.matrix[1][0][1].orientation = (newCube.matrix[1][0][1].orientation + 1) % 3;
    newCube.matrix[1][0][0].orientation = (newCube.matrix[1][0][0].orientation + 2) % 3;

    return newCube;
}

// rotate the left face backwards
Cube Cube::L_BW() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[0][0][0];
    newCube.matrix[0][0][0] = newCube.matrix[1][0][0];
    newCube.matrix[1][0][0] = newCube.matrix[1][0][1];
    newCube.matrix[1][0][1] = newCube.matrix[0][0][1];
    newCube.matrix[0][0][1] = temp;

    newCube.matrix[0][0][0].orientation = (newCube.matrix[0][0][0].orientation + 2) % 3;
    newCube.matrix[1][0][0].orientation = (newCube.matrix[1][0][0].orientation + 1) % 3;
    newCube.matrix[1][0][1].orientation = (newCube.matrix[1][0][1].orientation + 2) % 3;
    newCube.matrix[0][0][1].orientation = (newCube.matrix[0][0][1].orientation + 1) % 3;    

    return newCube;
}

// x - tras | frente
// y - esquerda | direita
// z - cima | baixo

//frente
Cube Cube::F_FW() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[1][0][0];
    newCube.matrix[1][0][0] = newCube.matrix[1][0][1];
    newCube.matrix[1][0][1] = newCube.matrix[1][1][1];
    newCube.matrix[1][1][1] = newCube.matrix[1][1][0];
    newCube.matrix[1][1][0] = temp;

    newCube.matrix[1][0][0].orientation = (newCube.matrix[1][0][0].orientation + 2) % 3;
    newCube.matrix[1][0][1].orientation = (newCube.matrix[1][0][1].orientation + 1) % 3;
    newCube.matrix[1][1][1].orientation = (newCube.matrix[1][1][1].orientation + 2) % 3;
    newCube.matrix[1][1][0].orientation = (newCube.matrix[1][1][0].orientation + 1) % 3;

    return newCube;
}


//frente
Cube Cube::F_BW() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[1][0][0];
    newCube.matrix[1][0][0] = newCube.matrix[1][1][0];
    newCube.matrix[1][1][0] = newCube.matrix[1][1][1];
    newCube.matrix[1][1][1] = newCube.matrix[1][0][1];
    newCube.matrix[1][0][1] = temp;

    newCube.matrix[1][0][0].orientation = (newCube.matrix[1][0][0].orientation + 1) % 3;
    newCube.matrix[1][1][0].orientation = (newCube.matrix[1][1][0].orientation + 2) % 3;
    newCube.matrix[1][1][1].orientation = (newCube.matrix[1][1][1].orientation + 1) % 3;
    newCube.matrix[1][0][1].orientation = (newCube.matrix[1][0][1].orientation + 2) % 3;


    return newCube;
}

Cube Cube::shuffle(int moviments) const {
    Cube newCube = *this;  // começa com uma cópia do cubo atual
    int functions_possible = 6;

    for (int i = 0; i < moviments; i++) {
        int functionIndex = rand() % functions_possible;
        switch(functionIndex){
            case 0:
                newCube = newCube.U_FW(); 
                cout << "Up" << endl;
                break;
            case 1:
                newCube = newCube.U_BW(); 
                cout << "Up'" << endl;
                break;
            case 2:
                newCube = newCube.L_FW(); 
                cout << "L" << endl;
                break;
            case 3:
                newCube = newCube.L_BW(); 
                cout << "L'" << endl;
                break;
            case 4:
                newCube = newCube.F_FW(); 
                cout << "F" << endl;
                break;
            case 5:
                newCube = newCube.F_BW(); 
                cout << "F'" << endl;
                break;
        }
    }

    return newCube;
}

MiniCube Cube::position(int x, int y, int z) {
    return matrix[x][y][z];
}

// // Move this implementation to Cube.h as a member function, or implement as a non-member function here:
// bool Cube::operator==(const Cube& other) const {
//     for (int x = 0; x < 2; ++x)
//         for (int y = 0; y < 2; ++y)
//             for (int z = 0; z < 2; ++z)
//                 if (matrix[x][y][z] != other.matrix[x][y][z])
//                     return false;
//     return true;
// }
