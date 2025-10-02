#pragma once

#include "Cube/Cube.h"
#include "Node/Node.h"

class DataStructure
{
// Classe Abstrata
public:
    virtual ~DataStructure() = default;

    virtual void insert(Node *node) = 0;
    virtual Node *remove() = 0;
    virtual bool isEmpty() const = 0;
};
