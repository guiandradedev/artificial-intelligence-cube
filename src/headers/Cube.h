#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>
#include "MiniCube.h"

class Cube {
protected:

public:
    Cube();       
    void init();
    void print() const;
    Cube cloneMatrix() const;
    MiniCube matrix[2][2][2];

    bool is_final_state(Cube original);

    MiniCube position(int x, int y, int z);

    Cube shuffle(int moviments) const;
    Cube applyMove(const char mov[4]) const;
};

#endif