#pragma once

#include "Cube.h"

namespace Move {

    // enum class Move_values {
    //     UFW = 0, UBW = 1,
    //     LFW = 2, LBW = 3,
    //     FFW = 4, FBW = 5
    // };

    // Movimentações possíveis (que geram novos estado//novas instâncias do cubo)

    // Observações
    // Foward (FW): sentido horario
    // Backward (BW): sentido anti horario

    // x - tras | frente
    // y - esquerda | direita
    // z - cima | baixo


    Cube U_FW(const Cube& cube);  // U (Up) sentido horário
    Cube L_FW(const Cube& cube);  // L (Left) sentido horário
    Cube F_FW(const Cube& cube);  // F (Front) sentido horário

    Cube U_BW(const Cube& cube);  // U (Up) sentido anti-horário
    Cube L_BW(const Cube& cube);  // L (Left) sentido anti-horário
    Cube F_BW(const Cube& cube);  // F (Front) sentido anti-horário

    Cube applyMove(Cube cube, short int mov);

    // const char* reverse_moves(const char* key);

    const bool isInverse(short int move1, short int move2);
}
