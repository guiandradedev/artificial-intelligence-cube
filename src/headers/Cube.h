#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>
#include "MiniCube.h"

class Cube {
// protected:
//     // std::vector<std::vector<std::vector<MiniCube> > > matriz;

public:
    Cube();       
    MiniCube matrix[2][2][2];
    void init();
    void print() const;
    Cube cloneMatrix() const;

    MiniCube position(int x, int y, int z);

    Cube shuffle(int moviments) const;
    Cube applyMove(const char mov[4]) const;
};

#endif