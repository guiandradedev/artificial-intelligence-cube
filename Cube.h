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

    Cube U() const;
    Cube D() const;
    Cube F() const;
    Cube B() const;
    Cube L() const;
    Cube R() const;

    Cube shuffle(int movements) const;
    
};

#endif
