#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>
#include "MiniCube.h"

class Cube {
protected:
    // std::vector<std::vector<std::vector<MiniCube> > > matriz;
    MiniCube matrix[2][2][2];

public:
    Cube();           
    void init();
    void print() const;
    Cube cloneMatrix() const;

    Cube U_FW() const;
    Cube L_FW() const;
    Cube F_FW() const;
    Cube U_BW() const;
    Cube L_BW() const;
    Cube F_BW() const;
    MiniCube position(int x, int y, int z);

    Cube shuffle(int movements) const;
    
};

#endif