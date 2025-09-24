#include "Node/DFSNode.h"

DFSNode::DFSNode() : Node() {}

DFSNode::DFSNode(const Cube& cube, Node* root, short int mov)
    : Node(cube, root, mov) {}