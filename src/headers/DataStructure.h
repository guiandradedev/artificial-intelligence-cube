#pragma once

#include "Cube.h"
#include "Solver.h"
#include "Node.h"

class DataStructure {
protected:
    // void algorithm(Cube cube, function<Cube()> getNext, );

public:
    virtual ~DataStructure() = default;

    virtual void insert(Node* node) = 0; 
    virtual Node* remove() = 0; 
    virtual bool isEmpty() const = 0;

};