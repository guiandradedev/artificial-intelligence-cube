// Node.h
#include "DataStructure.h"
#ifndef NODE_H
#define NODE_H

class Node {
public:
    Node();
    virtual ~Node() = default;
    Node(Cube cube, Node *root, short int mov); 
    Node *root;
    Cube cube;
    short int mov; // Movimento que gerou esse estado

};
#endif
