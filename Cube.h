#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>
#include "MiniCube.h"

class Cube {
protected:
    std::vector<std::vector<std::vector<MiniCube> > > matriz;

public:
    Cube();           
    void preencher();
    void imprimir();
};

#endif
