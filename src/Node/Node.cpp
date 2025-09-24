#include "Node/Node.h"

Node::Node() : cube(), root(nullptr), mov(0) {}

Node::Node(Cube c, Node *n, short int mv) : cube(c), root(n), mov(mv) {}