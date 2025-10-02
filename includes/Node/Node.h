#pragma once

#include "Cube/Cube.h"

class Node
{
public:
    Node();
    virtual ~Node() = default;
    Node(Cube cube, Node *root, short int mov);

    Node *root;
    Cube cube;
    short int mov;
};