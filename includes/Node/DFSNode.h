#pragma once

#include "Node/Node.h"

class DFSNode : public Node
{
public:
    
    DFSNode();
    DFSNode(const Cube &cube, Node *root, short int mov);

};