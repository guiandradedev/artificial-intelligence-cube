#include "Cube.h"

// Construtor: cria uma matriz 2x2x2 de MiniCubes com valores zerados
Cube::Cube() {
    matriz = std::vector<std::vector<std::vector<MiniCube>>>(
        2, std::vector<std::vector<MiniCube>>(
            2, std::vector<MiniCube>(2)
        )
    );
}
void Cube::preencher() {
    for (int z = 0; z < 2; ++z) {
        for (int y = 0; y < 2; ++y) {
            for (int x = 0; x < 2; ++x) {
                char name[4];
                sprintf(name, "%d%d%d", z, y, x); // nome da posição

                int base = z * 4 + y * 2 + x * 1; // base para valores

                matriz[z][y][x] = MiniCube(name, base + 1, base + 2, base + 3);
            }
        }
    }
}

// Imprime o conteúdo de cada MiniCube na matriz
void Cube::imprimir() {
    for (int i = 0; i < 2; ++i) {
        std::cout << "Camada " << i << ":\n";
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                MiniCube& cube = matriz[i][j][k];
                std::cout << "[" << cube.left << "," << cube.right << "," << cube.top << "] ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}
