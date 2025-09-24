#pragma once

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

    short int moviments[6] = {0, 1, 2, 3, 4, 5};
    /* 
       UFW = 0, UBW = 1,
       LFW = 2, LBW = 3,
       FFW = 4, FBW = 5
    */


    Cube shuffle(int moviments, bool print) const;
    Cube applyMove(short int mov) const;

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

namespace std {
    template<>
    struct hash<Cube> {
        size_t operator()(const Cube& c) const {
            size_t h = 0;
            for (int x = 0; x < 2; ++x) {
                for (int y = 0; y < 2; ++y) {
                    for (int z = 0; z < 2; ++z) {
                        const MiniCube& m = c.matrix[x][y][z];
                        // Usando o índice da peça para um hash mais estável
                        h ^= std::hash<int>{}(m.index) + 0x9e3779b9 + (h << 6) + (h >> 2);
                        h ^= std::hash<short>{}(m.orientation) + 0x9e3779b9 + (h << 6) + (h >> 2);
                    }
                }
            }
            return h;
        }
    };
}