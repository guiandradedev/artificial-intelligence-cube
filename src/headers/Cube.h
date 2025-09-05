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

    MiniCube position(int x, int y, int z);

    char moviments[6][4] = { "UFW", "UBW", "LFW", "LBW", "FBW", "FFW" };

    Cube shuffle(int moviments, bool print) const;
    Cube applyMove(const char mov[4]) const;

    bool operator==(const Cube& other) const {
        for (int x = 0; x < 2; ++x) {
            for (int y = 0; y < 2; ++y) {
                for (int z = 0; z < 2; ++z) {
                    if (matrix[x][y][z] != other.matrix[x][y][z]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

};

#endif