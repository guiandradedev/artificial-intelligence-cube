#pragma once

#include "Cube.h"
#include "Solver.h"

class DataStructure {
protected:
    // void algorithm(Cube cube, function<Cube()> getNext, );

public:
    virtual ~DataStructure() = default;

    virtual void insert(Solver::Node* node) = 0; 
    virtual Solver::Node* remove() = 0; 
    virtual bool isEmpty() const = 0;

};