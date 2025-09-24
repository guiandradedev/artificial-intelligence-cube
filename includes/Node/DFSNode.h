#pragma once

#include "Node/Node.h"

class DFSNode : public Node
{
public:
    int short depth;

    DFSNode();
    DFSNode(const Cube &cube, Node *root, short int mov, int depth);

};