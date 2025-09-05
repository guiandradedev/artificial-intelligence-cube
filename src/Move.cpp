#include "Move.h"

namespace Move {

    Cube U_FW(const Cube& cube) {
        Cube newCube = cube.cloneMatrix();

        
        MiniCube temp = newCube.matrix[0][0][0];
        newCube.matrix[0][0][0] = newCube.matrix[1][0][0];
        newCube.matrix[1][0][0] = newCube.matrix[1][1][0]; 
        newCube.matrix[1][1][0] = newCube.matrix[0][1][0];
        newCube.matrix[0][1][0] = temp;

        return newCube;
    }

    Cube U_BW(const Cube& cube) {
        Cube newCube = cube.cloneMatrix();
        MiniCube temp = newCube.matrix[0][0][0];
        newCube.matrix[0][0][0] = newCube.matrix[0][1][0];
        newCube.matrix[0][1][0] = newCube.matrix[1][1][0];
        newCube.matrix[1][1][0] = newCube.matrix[1][0][0];
        newCube.matrix[1][0][0] = temp;
        return newCube;
    }


    // L_FW estava correto.
    Cube L_FW(const Cube& cube) {
        Cube newCube = cube.cloneMatrix();
        MiniCube temp = newCube.matrix[0][0][0];
        newCube.matrix[0][0][0] = newCube.matrix[0][0][1];
        newCube.matrix[0][0][1] = newCube.matrix[1][0][1];
        newCube.matrix[1][0][1] = newCube.matrix[1][0][0];
        newCube.matrix[1][0][0] = temp;
        
        newCube.matrix[0][0][0].orientation = (newCube.matrix[0][0][0].orientation + 2) % 3;
        newCube.matrix[0][0][1].orientation = (newCube.matrix[0][0][1].orientation + 1) % 3;
        newCube.matrix[1][0][1].orientation = (newCube.matrix[1][0][1].orientation + 2) % 3;
        newCube.matrix[1][0][0].orientation = (newCube.matrix[1][0][0].orientation + 1) % 3;

        return newCube;
    }

    Cube L_BW(const Cube& cube) {
        Cube newCube = cube.cloneMatrix();
        MiniCube temp = newCube.matrix[0][0][0];
        newCube.matrix[0][0][0] = newCube.matrix[1][0][0];
        newCube.matrix[1][0][0] = newCube.matrix[1][0][1];
        newCube.matrix[1][0][1] = newCube.matrix[0][0][1];
        newCube.matrix[0][0][1] = temp;
        
        newCube.matrix[0][0][0].orientation = (newCube.matrix[0][0][0].orientation + 2) % 3; // Invertido
        newCube.matrix[1][0][0].orientation = (newCube.matrix[1][0][0].orientation + 1) % 3; // Invertido
        newCube.matrix[1][0][1].orientation = (newCube.matrix[1][0][1].orientation + 2) % 3; // Invertido
        newCube.matrix[0][0][1].orientation = (newCube.matrix[0][0][1].orientation + 1) % 3; // Invertido

        return newCube;
    }

    Cube F_FW(const Cube& cube) {
        Cube newCube = cube.cloneMatrix();
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

    // x - tras | frente
    // y - esquerda | direita
    // z - cima | baixo

    // F_BW CORRIGIDO
    Cube F_BW(const Cube& cube) {
        Cube newCube = cube.cloneMatrix();
        MiniCube temp = newCube.matrix[1][0][0];
        newCube.matrix[1][0][0] = newCube.matrix[1][1][0];
        newCube.matrix[1][1][0] = newCube.matrix[1][1][1];
        newCube.matrix[1][1][1] = newCube.matrix[1][0][1];
        newCube.matrix[1][0][1] = temp;
        
        newCube.matrix[1][0][0].orientation = (newCube.matrix[1][0][0].orientation + 2) % 3;
        newCube.matrix[1][1][0].orientation = (newCube.matrix[1][1][0].orientation + 1) % 3; 
        newCube.matrix[1][1][1].orientation = (newCube.matrix[1][1][1].orientation + 2) % 3; 
        newCube.matrix[1][0][1].orientation = (newCube.matrix[1][0][1].orientation + 1) % 3; 

        return newCube;
    }
}