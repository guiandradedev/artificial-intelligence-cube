#include "Cube.h"
#include <map>
#include <array>
#include <string>
#include <vector>

using namespace std;

Cube::Cube() {}

void Cube::init()
{
    // Mapa de cores, a posição real do cubo mágico contem 3 cores, left right e mid
    map<string, array<int, 3>> colors = {
        {"000", {4, 2, 0}},
        {"001", {4, 2, 1}},
        {"010", {3, 4, 0}},
        {"011", {3, 4, 1}},
        {"100", {2, 5, 0}},
        {"101", {2, 5, 1}},
        {"110", {5, 3, 0}},
        {"111", {5, 3, 1}}};

    // Loop que insere as cores na matriz
    for (int x = 0; x < 2; ++x)
    {
        for (int y = 0; y < 2; ++y)
        {
            for (int z = 0; z < 2; ++z)
            {
                // Cria o nome da posição para identificação
                char key[4];
                snprintf(key, sizeof(key), "%d%d%d", x, y, z);

                // Realiza a busca no mapa das cores
                // Compilador utiliza o auto para deduzir qual a tipagem correta
                auto it = colors.find(key);
                if (it != colors.end())
                {
                    // Realiza a operação destructure, criando uma refêrencia dos dados left, right e mid recebidos da iteração do loop
                    const auto &[left, right, mid] = it->second;
                    // Cria uma instância de MiniCube e insere na matriz
                    matrix[x][y][z] = MiniCube(key, left, right, mid, 0);
                }
                else
                {
                    cerr << "Chave não encontrada: " << key << endl;
                }
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
                          << cube.name << " "
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
Cube Cube::U() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[0][0][0];
    newCube.matrix[0][0][0] = newCube.matrix[1][0][0];
    newCube.matrix[1][0][0] = newCube.matrix[1][1][0];
    newCube.matrix[1][1][0] = newCube.matrix[0][1][0];
    newCube.matrix[0][1][0] = temp;

    return newCube;
}

Cube Cube::D() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[0][1][0];
    newCube.matrix[0][1][0] = newCube.matrix[0][0][0];
    newCube.matrix[0][0][0] = newCube.matrix[1][0][0];
    newCube.matrix[1][0][0] = newCube.matrix[1][1][0];
    newCube.matrix[1][1][0] = temp;

    return newCube;
}

Cube Cube::R() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[0][0][0];
    newCube.matrix[0][0][0] = newCube.matrix[0][0][1];
    newCube.matrix[0][0][1] = newCube.matrix[0][1][1];
    newCube.matrix[0][1][1] = newCube.matrix[0][1][0];
    newCube.matrix[0][1][0] = temp;

    newCube.matrix[0][0][0].orientation = (newCube.matrix[0][0][0].orientation + 1) % 3;
    newCube.matrix[0][0][1].orientation = (newCube.matrix[0][0][1].orientation + 2) % 3;
    newCube.matrix[0][1][1].orientation = (newCube.matrix[0][1][1].orientation + 1) % 3;
    newCube.matrix[0][1][0].orientation = (newCube.matrix[0][1][0].orientation + 2) % 3;

    return newCube;
}

Cube Cube::L() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[0][0][0];
    newCube.matrix[0][0][0] = newCube.matrix[0][1][0];
    newCube.matrix[0][1][0] = newCube.matrix[0][1][1];
    newCube.matrix[0][1][1] = newCube.matrix[0][0][1];
    newCube.matrix[0][0][1] = temp;

    newCube.matrix[0][0][0].orientation = (newCube.matrix[0][0][0].orientation + 1) % 3;
    newCube.matrix[0][1][0].orientation = (newCube.matrix[0][1][0].orientation + 2) % 3;
    newCube.matrix[0][1][1].orientation = (newCube.matrix[0][1][1].orientation + 1) % 3;
    newCube.matrix[0][0][1].orientation = (newCube.matrix[0][0][1].orientation + 2) % 3;

    return newCube;
}


Cube Cube::F() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[0][0][0];
    newCube.matrix[0][0][0] = newCube.matrix[0][0][1];
    newCube.matrix[0][0][1] = newCube.matrix[0][1][1];
    newCube.matrix[0][1][1] = newCube.matrix[0][1][0];
    newCube.matrix[0][1][0] = temp;

    return newCube;
}

Cube Cube::B() const {
    Cube newCube = this->cloneMatrix();

    MiniCube temp = newCube.matrix[0][0][1];
    newCube.matrix[0][0][1] = newCube.matrix[1][0][1];
    newCube.matrix[1][0][1] = newCube.matrix[1][1][1];
    newCube.matrix[1][1][1] = newCube.matrix[0][1][1];
    newCube.matrix[0][1][1] = temp;

    return newCube;
}

// Cube Cube::shuffle(int movements) const {
//     vector<function<void()>> functions = {
//         [this]() { U(); },
//         [this]() { D(); },
//         [this]() { R(); },
//         [this]() { L(); },
//         [this]() { F(); },
//         [this]() { B(); },
//     };

//     int functionIndex = 0;
//     Cube newCube;
//     for(int i=0; i<movements; i++) {
//         functionIndex = rand() % functions.size();
//         newCube = functions[functionIndex]()
//     }
// }

Cube Cube::shuffle(int movements) const {
    Cube newCube = *this;  // começa com uma cópia do cubo atual
    int functions_possible = 6;

    for (int i = 0; i < movements; i++) {
        int functionIndex = rand() % functions_possible;
        switch(functionIndex){
            case 0:
                newCube = newCube.U(); 
                cout << "Up" << endl;
                break;
            case 1:
                newCube = newCube.D(); 
                cout << "Down" << endl;
                break;
            case 2:
                newCube = newCube.R(); 
                cout << "Right" << endl;
                break;
            case 3:
                newCube = newCube.L(); 
                cout << "Left" << endl;
                break;
            case 4:
                newCube = newCube.F(); 
                cout << "Front" << endl;
                break;
            case 5:
                newCube = newCube.B(); 
                cout << "Back" << endl;
                break;
        }
    }

    return newCube;
}
